include(GoogleTest)

set(SOURCES
  "Format/Strings/TransformerManager.cpp"
  "Format/Strings/UppercaseTransformer.cpp"
  "Format/Strings/LowercaseTransformer.cpp"
  "Format/Numbers/Systems/Latin.cpp"
  "Information/Locale.cpp"
  "Parser/Strings/StringContent.cpp"
  "Parser/Strings/StringParser.cpp"
  "Parser/CommentParser.cpp"
  "Parser/FileParser.cpp"
  "Parser/LineParser.cpp"
  "Parser/Tokenizer.cpp"
  "Utils/Util.cpp"
  "LocaleManager.cpp"
  "main.cpp")

add_executable(i18n_tests ${SOURCES})
target_link_libraries(i18n_tests
  PUBLIC
    i18n
    gtest)

add_custom_command(
  TARGET i18n_tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:i18n>
    $<TARGET_FILE_DIR:i18n_tests>
)

add_custom_command(
  TARGET i18n_tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:i18n_languages>
    $<TARGET_FILE_DIR:i18n_tests>/languages
)

gtest_discover_tests(i18n_tests
  WORKING_DIRECTORY $<TARGET_FILE_DIR:i18n_tests>)
