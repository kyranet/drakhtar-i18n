// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <string>
#include <variant>
#include <vector>

class StringContent final {
  enum class PartType { Content, Variable };

  struct ContentPart {
   private:
    std::variant<size_t, std::string> value;

   public:
    PartType type;
    std::vector<std::string> modifiers;

    explicit ContentPart(std::tuple<size_t, std::vector<std::string>> var)
        : value(std::get<0>(var)),
          type(PartType::Variable),
          modifiers(std::get<1>(var)) {}
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

  std::vector<ContentPart> parts_{};
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
   * @param mods The modifiers to be applied to the variable.
   */
  inline void add(std::tuple<size_t, std::vector<std::string>> var) {
    add(ContentPart{var});
    dynamic_ = true;
  };

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
};
