cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(internationalization
	VERSION 0.0.1
	DESCRIPTION "An internationalization engine for the Drakhtar game"
	HOMEPAGE_URL "https://github.com/kyranet/drakhtar-i18n"
	LANGUAGES CXX)

if(MSVC)
    # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WIN32)
  # this is needed, because Windows can be weird, man.
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_subdirectory(src)
