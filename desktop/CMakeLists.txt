# Add desktop file and desktop icon to target machine
# Add metadata file

if(UNIX AND NOT APPLE)
    install(PROGRAMS org.ksnip.ksnip.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
    install(FILES ksnip.svg DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps)
    install(FILES org.ksnip.ksnip.appdata.xml DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)
endif()
