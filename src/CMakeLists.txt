set(INTERNATIONALIZATION_SOURCES
	Format/Numbers/INumber.cpp
	Utils/Util.cpp)

add_library(internationalization SHARED ${INTERNATIONALIZATION_SOURCES})
target_compile_features(internationalization PUBLIC cxx_std_17)

# If Linux, we need to make sure we include and link to libuuid.
if (NOT WIN32)
	target_include_directories(internationalization
		PUBLIC
		$<BUILD_INTERFACE:${internationalization_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
		${UUID_INCLUDE_DIRS})
	target_link_libraries(internationalization ${UUID_LIBRARIES})
else ()
	target_include_directories(internationalization
			PUBLIC
			$<BUILD_INTERFACE:${internationalization_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>)
endif ()

if (MSVC)
	target_compile_options(internationalization
		PRIVATE
		/W4
	)
	get_target_property(opts internationalization COMPILE_OPTIONS)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(internationalization
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
	target_compile_options(internationalization
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
