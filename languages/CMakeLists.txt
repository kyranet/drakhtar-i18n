option(I18N_LANGUAGE_ALL "Include all language data" OFF)

macro(I18N_REGISTER key directory)
	option(I18N_LANGUAGE_${key} "Include languages/${directory}" OFF)

	if (I18N_LANGUAGE_ALL OR I18N_LANGUAGE_${key})
		list(APPEND ASSET_FILES "${directory}/.meta.txt")
	endif()
endmacro(I18N_REGISTER)

set(ASSET_FILES)

I18N_REGISTER(EN "en")
I18N_REGISTER(EN_US "en-US")
I18N_REGISTER(ES "es")
I18N_REGISTER(ES_ES "es-ES")

foreach(resource ${ASSET_FILES})
	configure_file(${resource} languages/${resource} COPYONLY)
endforeach()

add_executable(i18n_languages IMPORTED GLOBAL)
set_target_properties(i18n_languages PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/languages/DO_NOT_USE)
