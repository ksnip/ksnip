find_package(Qt5LinguistTools)

set(KSNIP_LANG_TS
	ksnip_de.ts
	ksnip_es.ts
	ksnip_fr.ts
	ksnip_gl.ts
	ksnip_id.ts
	ksnip_nl.ts
	ksnip_no.ts
	ksnip_pl.ts
	ksnip_pt.ts
	ksnip_ru.ts
	ksnip_tr.ts
	ksnip_uk.ts)

if (DEFINED UPDATE_TS_FILES)
	qt5_create_translation(KSNIP_LANG_QM ${CMAKE_SOURCE_DIR}/translations ${KSNIP_SRCS} ${KSNIP_LANG_TS} OPTIONS "-no-obsolete")
else ()
	qt5_add_translation(KSNIP_LANG_QM ${KSNIP_LANG_TS})
endif ()

add_custom_target(translations ALL DEPENDS ${KSNIP_LANG_QM})

install(FILES ${KSNIP_LANG_QM} DESTINATION ${KSNIP_LANG_INSTAL_DIR})

