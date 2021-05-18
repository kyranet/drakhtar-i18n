// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Parser/Strings/StringParser.h"

#include <sstream>

#include "Parser/Tokenizer.h"
#include "Utils/Util.h"

StringContent StringParser::run() {
  StringContent sc{};
  std::stringstream ss{};
  auto& t = tokenizer();

  char c;
  while (t.next(c)) {
    if (c == '\\') {
      ss << parseEscape();
      if (t.finished()) break;
    } else if (c == '{') {
      if (ss.rdbuf()->in_avail()) {
        sc.add(ss.str());
        ss.str("");
      }

      sc.add(parseVariable());
      if (t.finished()) break;
    } else if (c == '"') {
      break;
    } else {
      ss << c;
    }
  }

  // Add content if there was something in the string stream:
  if (ss.rdbuf()->in_avail()) {
    sc.add(ss.str());
  }

  return sc;
}

std::string StringParser::parseEscape() {
  auto& t = tokenizer();

  const auto c = t.next();
  if (t.finished()) unexpectedEndOfInput();

  switch (c) {
    case '\n':
      return "";

    case '\'':
    case '"':
    case '?':
    case '\\':
    case '{':
    case '}':
      return std::string(1, c);

    case 'a':
      return "\a";
    case 'b':
      return "\b";
    case 'f':
      return "\f";
    case 'n':
      return "\n";
    case 'r':
      return "\r";
    case 't':
      return "\t";
    case 'v':
      return "\v";

    case 'u':
      return parseUnicode();

    case 'x':
      return parseHexadecimal();

    default:
      return parseOctal(c);
  }
}

std::string StringParser::parseOctal(char first) {
  if (!Util::isOctal(first)) {
    throw std::runtime_error("The character '" + std::to_string(first) +
                             "' is not a valid octal character.");
  }

  auto& t = tokenizer();
  size_t n{Util::getOctal(first)};

  char c;
  while (t.next(c)) {
    if (!Util::isOctal(c)) {
      t.undo();
      break;
    }

    n *= 8;
    n += Util::getOctal(c);
  }

  return Util::fromCodePoint(n);
}

std::string StringParser::parseHexadecimal(size_t size) {
  auto& t = tokenizer();
  size_t n{0};

  for (size_t i = 0; i < size; ++i) {
    const auto c = t.next();
    if (t.finished()) {
      unexpectedEndOfInput();
    }

    if (!Util::isHexadecimal(c)) {
      t.undo();
      throw std::runtime_error("Invalid escape sequence.");
    }

    n *= 16;
    n += Util::getHexadecimal(c);
  }

  return Util::fromCodePoint(n);
}

std::string StringParser::parseHexadecimal() { return parseHexadecimal(2); }

std::string StringParser::parseUnicode() { return parseHexadecimal(4); }

variable_t StringParser::parseVariable() {
VariableInfo StringParser::parseVariable() {
  auto& t = tokenizer();

  bool defined{false};
  size_t n{0};
  std::vector<std::string> mods;

  char c;
  while (t.next(c)) {
    if (c == '}') {
      if (defined) return {n, Type::String};
      if (defined) return variable_t{n, mods};

      throw std::runtime_error("Received empty variable place-holder.");
    }

    if (Util::isNumber(c)) {
      defined = true;
      n *= 10;
      n += Util::getNumber(c);
      continue;
    }

    if (c == ':') {
      mods = parseModifiers();
      continue;
    }

    if (Util::isLetter(c)) {
      if (!defined)
        unexpectedCharacter(c, "an index before reading a type");
      return {n, parseType(c)};
    }

    unexpectedCharacter(c, "a variable");
  }

  unexpectedEndOfInput();
}

std::vector<std::string> StringParser::parseModifiers() {
  auto& t = tokenizer();
  std::vector<std::string> mods = std::vector<std::string>();
  std::stringstream mod;
  char c;

  while (t.next(c)) {
    if (c == '}') {
      mods.push_back(mod.str());
      t.undo();
      return mods;
    }

    if (c == ':') {
      mods.push_back(mod.str());
      mod.str(std::string());
      continue;
    }

    mod << c;
  }
  return mods;
}

Type StringParser::parseType(char c) {
  auto& t = tokenizer();

  bool defined{false};
  size_t n{0};

  switch (c) {
    case 's':
    case 'b':
      defined = true;
    case 'i':
    case 'u':
    case 'f':
      break;
    default:
      unexpectedCharacter(c, "a type");
  }

  char type = c;

  while (t.next(c)) {
    if (c == '}') {
      if (defined) break;
      throw std::runtime_error("Cannot identify type: size not defined.");
    }

    if (Util::isNumber(c)) {
      defined = true;
      n *= 10;
      n += Util::getNumber(c);
      continue;
    }

    unexpectedCharacter(c, "a size");
  }

  if (c != '}') unexpectedEndOfInput();

  switch (type) {
    case 's':
      return Type::String;
    case 'b':
      return Type::Boolean;
    case 'i':
      switch (n) {
        case 8:
          return Type::Int8;
        case 16:
          return Type::Int16;
        case 32:
          return Type::Int32;
        case 64:
          return Type::Int64;
        default:
          throw std::runtime_error(
              "Cannot identify type: int size not supported.");
      }
    case 'u':
      switch (n) {
        case 8:
          return Type::UInt8;
        case 16:
          return Type::UInt16;
        case 32:
          return Type::UInt32;
        case 64:
          return Type::UInt64;
        default:
          throw std::runtime_error(
              "Cannot identify type: usigned size not supported.");
      }
    case 'f':
      switch (n) {
        case 32:
          return Type::Float32;
        case 64:
          return Type::Float64;
        default:
          throw std::runtime_error(
              "Cannot identify type: float size not supported.");
      }
    default:
      unexpectedCharacter(type, "a numeric type");
  }
}
