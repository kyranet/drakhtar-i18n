set(I18N_SOURCES
	"Format/Numbers/INumber.cpp"
	"Format/Strings/TransformerManager.cpp"
	"Information/Locale.cpp"
	"Parser/Strings/StringContent.cpp"
	"Parser/Strings/StringParser.cpp"
	"Parser/LineParser.cpp"
	"Parser/FileParser.cpp"
	"Parser/CommentParser.cpp"
	"Utils/Util.cpp"
	"LocaleManager.cpp")

add_library(i18n SHARED ${I18N_SOURCES})
target_compile_features(i18n PUBLIC cxx_std_17)

# If Linux, we need to make sure we include and link to libuuid.
if (NOT WIN32)
	target_include_directories(i18n
		PUBLIC
		$<BUILD_INTERFACE:${i18n_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		${UUID_INCLUDE_DIRS})
	target_link_libraries(i18n ${UUID_LIBRARIES})
else ()
	target_include_directories(i18n
			PUBLIC
			$<BUILD_INTERFACE:${i18n_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>)
endif ()

if (MSVC)
	target_compile_options(i18n
		PRIVATE
		/W4
	)
	get_target_property(opts i18n COMPILE_OPTIONS)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(i18n
		PRIVATE
		-pedantic
		-pedantic-errors
		-Wall
		-Wextra
		-Wno-float-equal
		-Wno-padded
		-luuid
	)
else ()
	target_compile_options(i18n
		PRIVATE
		-pedantic
		-pedantic-errors
		-Wall
		-Wextra
		-Wconversion
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-float-equal
		-Wno-padded
		-Wno-reserved-id-macro
	)
endif ()
