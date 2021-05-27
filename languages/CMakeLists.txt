set(ASSET_FILES)
set(LANGUAGES
	"en"
	"en-US"
	"es"
	"es-ES")

option(I18N_LANGUAGE_ALL "Include all language data" OFF)

foreach(language ${LANGUAGES})
	# If all languages are to be included, append the entry nevertheless:
	if (I18N_LANGUAGE_ALL)
		list(APPEND ASSET_FILES "${language}/.meta.txt")
	else()
		# Convert the string to uppercase (en-US -> EN-US, es-ES -> ES-ES):
		string(TOUPPER ${language} __DIRECTORY__)

		# Replace "-" with "_" (EN-US -> EN_US, ES-ES -> ES_ES):
		string(REPLACE "-" "_" __DIRECTORY__ ${__DIRECTORY__})

		# Define the option:
		option(I18N_LANGUAGE_${__DIRECTORY__} "Include languages/${language}" OFF)

		# If the option was given, append the entry:
		if (I18N_LANGUAGE_${__DIRECTORY__})
			list(APPEND ASSET_FILES "${language}/.meta.txt")
		endif()
	endif()
endforeach()

foreach(resource ${ASSET_FILES})
	configure_file(${resource} languages/${resource} COPYONLY)
endforeach()

add_executable(i18n_languages IMPORTED GLOBAL)
set_target_properties(i18n_languages PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/languages/DO_NOT_USE)
