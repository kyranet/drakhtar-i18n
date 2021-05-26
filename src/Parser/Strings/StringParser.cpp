// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Parser/Strings/StringParser.h"

#include <sstream>

#include "Parser/Strings/StringContent.h"
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

      sc.add(parseVariable(), parseModifiers());
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

size_t StringParser::parseVariable() {
  auto& t = tokenizer();

  bool defined{false};
  size_t n{0};

  char c;
  while (t.next(c)) {
    if (c == '}' || c == ':') {
      if (defined) return n;
      throw std::runtime_error("Received empty variable place-holder.");
    }

    if (Util::isNumber(c)) {
      defined = true;
      n *= 10;
      n += Util::getNumber(c);
      continue;
    }

    unexpectedCharacter(c, "a variable");
  }

  unexpectedEndOfInput();
}

std::vector<std::string> StringParser::parseModifiers() {
  auto& t = tokenizer();
  std::vector<std::string> mods = std::vector<std::string>();
  std::string mod;
  char c;

  while (t.next(c)) {
    if (c == '}') {
      if (true) {
        mods.push_back(mod);
        break;
      }
      throw std::runtime_error("Invalid variable modifier.");
    }

    if (c == ':') {
      if (true) {
        mods.push_back(mod);
        mod.clear();
        continue;
      }
      throw std::runtime_error("Received empty variable place-holder.");
    }

    mod.push_back(c);
  }
  return mods;
}