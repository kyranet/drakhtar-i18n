// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <cassert>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

enum class Type {
  String,
  Boolean,
  Int8,
  Int16,
  Int32,
  Int64,
  UInt8,
  UInt16,
  UInt32,
  UInt64,
  Float32,
  Float64
};

using variable_modifiers_t = std::vector<std::string>;
using modifiers_t = std::vector<variable_modifiers_t>;

struct VariableInfo {
  size_t index;
  Type type;
  variable_modifiers_t modifiers;
};

class StringContent final {
  enum class PartType { Content, Variable };

  struct ContentPart {
   private:
    std::variant<size_t, std::string> value;

   public:
    PartType type;

    explicit ContentPart(size_t value)
        : value(value), type(PartType::Variable) {}
    explicit ContentPart(const std::string& content)
        : value(content), type(PartType::Content) {}

    [[nodiscard]] inline bool isVariable() const noexcept {
      return type == PartType::Variable;
    };

    [[nodiscard]] inline size_t variable() const noexcept {
      return std::get<0>(value);
    }

    [[nodiscard]] inline size_t& variable() noexcept {
      return std::get<0>(value);
    }

    [[nodiscard]] inline bool isContent() const noexcept {
      return type == PartType::Content;
    };

    [[nodiscard]] inline const std::string& content() const noexcept {
      return std::get<1>(value);
    }

    [[nodiscard]] inline std::string& content() noexcept {
      return std::get<1>(value);
    }
  };

  std::vector<Type> types_{};
  std::vector<ContentPart> parts_{};
  modifiers_t modifiers_{};
  bool dynamic_{false};

  /**
   * Adds a part to the string content.
   * @param part The part to add.
   */
  inline void add(ContentPart part) { parts_.push_back(part); }

 public:
  /**
   * Adds a new string content part into the content.
   * @param content The content to add.
   */
  inline void add(const std::string& content) {
    // If there are parts, and the last one is a content one, concatenate
    // strings for performance gains:
    if (!parts_.empty()) {
      auto& last = parts_.back();
      if (last.isContent()) {
        last.content() += content;
        return;
      }
    }

    add(ContentPart{content});
  };

  /**
   * Adds a new variable part into the content.
   * @param index The index of the variable to read from when running.
   * @param type The type of the variable to read from when running.
   * @param mods The modifiers to be applied to the variable.
   */
  inline void add(size_t index, Type type,
                  const std::vector<std::string>& mods) {
    add(ContentPart{index});
    if (index >= types_.size()) {
      types_.resize(index + 1);
      modifiers_.resize(index + 1);
    }
    types_[index] = type;
    modifiers_[index] = mods;
    dynamic_ = true;
  };

  /**
   * Adds a new variable part into the content.
   * @param info info which contains both index and type of the variable to read
   * from when running.
   */
  inline void add(const VariableInfo& info) {
    add(info.index, info.type, info.modifiers);
  }

  /**
   * Processes the string with a set of variables.
   * @param variables The vector of variables to interpolate.
   * @remarks This function uses `assert` to check that the vector's size is big
   * enough for the variables.
   */
  [[nodiscard]] std::string run(std::vector<std::string> variables) const;

  /**
   * Checks whether or not the content has variables.
   */
  [[nodiscard]] inline bool dynamic() const noexcept { return dynamic_; }

  /**
   * Checks whether or not the string content is empty.
   */
  [[nodiscard]] inline bool empty() const noexcept { return parts_.empty(); }

  /**
   * Checks the size of the stored parts.
   */
  [[nodiscard]] inline size_t size() const noexcept { return parts_.size(); }

  /**
   * Get the argument types of the content.
   */
  [[nodiscard]] inline const std::vector<Type>& types() const noexcept {
    return types_;
  }

  /**
   * Get the argument modifiers of the content.
   */
  [[nodiscard]] inline const modifiers_t& modifiers() const noexcept {
    return modifiers_;
  }
};
