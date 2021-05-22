include(GoogleTest)

set(SOURCES
  "Format/Numbers/Systems/Latin.cpp"
  "Parser/Strings/StringContent.cpp"
  "Parser/Strings/StringParser.cpp"
  "Parser/FileParser.cpp"
  "Parser/LineParser.cpp"
  "Parser/Tokenizer.cpp"
  "Utils/Util.cpp"
  "main.cpp")

add_executable(internationalization_tests ${SOURCES})
target_link_libraries(internationalization_tests
  PUBLIC
    internationalization
    gtest)

add_custom_command(
  TARGET internationalization_tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:internationalization>
    $<TARGET_FILE_DIR:internationalization_tests>
)

gtest_discover_tests(internationalization_tests)
