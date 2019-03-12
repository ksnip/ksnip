# Add desktop file and desktop icon to target machine
# Add metadata file

install(PROGRAMS ksnip.desktop DESTINATION /usr/share/applications)
install(FILES ksnip.svg DESTINATION /usr/share/pixmaps)
install(FILES ksnip.appdata.xml DESTINATION /usr/share/metainfo)
