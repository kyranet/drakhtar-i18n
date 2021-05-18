// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#include "Parser/Strings/StringParser.h"

#include <sstream>

#include "Parser/Strings/StringContent.h"
#include "Parser/Tokenizer.h"
#include "Utils/Util.h"

// TODO: Test this
StringContent StringParser::run() {
  StringContent sc{};
  std::stringstream ss{};
  auto& t = tokenizer();

  while (!t.finished()) {
    const auto c = t.next();

    if (c == '\\') {
      ss << parseEscape();
    } else if (c == '{') {
      if (ss.rdbuf()->in_avail()) {
        sc.add(ss.str());
        ss.str("");
      }

      sc.add(parseVariable());
    } else {
      ss << c;
    }
  }

  return sc;
}

std::string StringParser::parseEscape() {
  auto& t = tokenizer();
  if (t.finished()) throw std::runtime_error("Unexpected end of input.");

  const auto c = t.next();
  switch (c) {
    case '\'':
    case '"':
    case '?':
    case '\\':
    case '{':
      return std::to_string(c);

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

  while (!t.finished()) {
    const auto c = t.next();
    if (!Util::isOctal(c)) {
      t.undo();
      break;
    }

    n *= 8;
    n += Util::getOctal(c);
  }

  return Util::fromCodePoint(n);
}

// TODO: \xn is invalid, this requires at least 2 characters.
std::string StringParser::parseHexadecimal() {
  bool defined{false};

  auto& t = tokenizer();
  size_t n{0};

  while (!t.finished()) {
    const auto c = t.next();
    if (!Util::isHexadecimal(c)) {
      t.undo();
      break;
    }

    n *= 16;
    n += Util::getHexadecimal(c);
  }

  if (defined) return Util::fromCodePoint(n);
  throw std::runtime_error("Unexpected end of input.");
}

std::string StringParser::parseUnicode() {
  auto& t = tokenizer();
  size_t n{0};

  for (int32_t i = 0; i < 4; ++i) {
    if (t.finished()) {
      throw std::runtime_error("Unexpected end of input.");
    }

    const auto c = t.next();
    if (!Util::isHexadecimal(c)) {
      t.undo();
      throw std::runtime_error("Invalid Unicode escape sequence.");
    }

    n *= 16;
    n += Util::getHexadecimal(c);
  }

  return Util::fromCodePoint(n);
}

size_t StringParser::parseVariable() {
  auto& t = tokenizer();

  bool defined{false};
  size_t n{0};
  while (!t.finished()) {
    const auto c = t.next();

    if (c == '}') {
      if (defined) return n;
      throw std::runtime_error("Received empty variable place-holder.");
    }

    if (Util::isNumber(c)) {
      defined = true;
      n *= 10;
      n += Util::getNumber(c);
    }

    const auto message = "Unexpected character '" + std::to_string(c) + "'.";
    throw std::runtime_error(message);
  }

  throw std::runtime_error("Unexpected end of input.");
}
