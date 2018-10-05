find_package(Qt5LinguistTools)

set(ksnip_LANG_TS
	ksnip_de.ts
	ksnip_es.ts
	ksnip_nl.ts
	ksnip_no.ts
	ksnip_pl.ts
	ksnip_ru.ts)

#if(DEFINED UPDATE_TS_FILES)
    qt5_create_translation(ksnip_LANG_QM ${CMAKE_SOURCE_DIR}/translations ${ksnip_SRCS} ${ksnip_LANG_TS})
#else()
#    qt5_add_translation(ksnip_LANG_QM ${ksnip_LANG_TS})
#endif()

add_custom_target(translations ALL DEPENDS ${ksnip_LANG_QM})

install(FILES ${ksnip_LANG_QM} DESTINATION ${KSNIP_LANG_INSTAL_DIR})
