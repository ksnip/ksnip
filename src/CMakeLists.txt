set(KSNIP_SRCS
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/backend/config/KsnipConfig.cpp
	${CMAKE_SOURCE_DIR}/src/backend/config/KsnipConfigOptions.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractImageGrabber.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/ImageGrabberFactory.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/ImgurUploader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/UploadResponse.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/CaptureUploader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/ImgurResponseLogger.cpp
	${CMAKE_SOURCE_DIR}/src/backend/CapturePrinter.cpp
	${CMAKE_SOURCE_DIR}/src/backend/TranslationLoader.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/MathHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/CommandLineParserHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/MessageBoxHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/loader/IconLoader.cpp
	${CMAKE_SOURCE_DIR}/src/common/handler/DelayHandler.cpp
	${CMAKE_SOURCE_DIR}/src/common/formatter/FilenameFormatter.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomToolButton.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomCursor.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CursorFactory.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/NumericComboBox.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomSpinBox.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CaptureModePicker.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/ColorButton.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/MainToolBar.cpp
	${CMAKE_SOURCE_DIR}/src/gui/MainWindow.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AbstractSnippingArea.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/SnippingAreaAdorner.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerMagnifyingGlass.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerRulers.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerPositionInfo.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerSizeInfo.cpp
	${CMAKE_SOURCE_DIR}/src/gui/SettingsDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/AboutDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/ImgurHistoryDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/GlobalKeyboardShortcut.cpp
	${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/NativeKeyEventFilter.cpp
	${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/AbstractKeyHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/KeyHandlerFactory.cpp
	)

if (APPLE)
	set(KSNIP_SRCS
			${KSNIP_SRCS}
			${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/MacImageGrabber.cpp
			${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/MacWrapper.cpp
			${CMAKE_SOURCE_DIR}/src/gui/snippingArea/MacSnippingArea.cpp
			${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/DummyKeyHandler.cpp
			)
elseif (UNIX)
    set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11ImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11Wrapper.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/PlatformChecker.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/CommandRunner.cpp
		${CMAKE_SOURCE_DIR}/src/gui/snippingArea/LinuxSnippingArea.cpp
		${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/DummyKeyHandler.cpp
		)
elseif (WIN32)
	set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinWrapper.cpp
		${CMAKE_SOURCE_DIR}/src/gui/snippingArea/WinSnippingArea.cpp
		${CMAKE_SOURCE_DIR}/src/gui/keyboardShortcuts/WinKeyHandler.cpp
		)
endif ()

set(KSNIP_SRCS ${KSNIP_SRCS} PARENT_SCOPE)

if (WIN32)
	add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${CMAKE_SOURCE_DIR}/icons/ksnip_windows_icon.rc)
elseif (APPLE)
	set(MACOSX_BUNDLE_EXECUTABLE_NAME "ksnip")
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ksnip")
	set(MACOSX_BUNDLE_ICON_FILE "ksnip.icns")
	set(MACOSX_BUNDLE_INFO_STRING "Cross-Platform Screenshot and Annotation Tool")
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${KSNIP_VERSION})

	set(MACOSX_ICON ${CMAKE_SOURCE_DIR}/icons/ksnip.icns)
	set_source_files_properties(${MACOSX_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	add_executable(ksnip MACOSX_BUNDLE ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${MACOSX_ICON})
else()
	add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc)
endif ()

target_link_libraries(ksnip
					  Qt5::Widgets
					  Qt5::Network
					  Qt5::Xml
					  Qt5::PrintSupport
					  Qt5::DBus
					  kImageAnnotator
					  kColorPicker
					  )

if (APPLE)
	target_link_libraries(ksnip "-framework CoreGraphics")
elseif (UNIX)
	target_link_libraries(ksnip
            Qt5::X11Extras
			XCB::XFIXES
            X11
            )
elseif(WIN32)
	target_link_libraries(ksnip
            Qt5::WinExtras
            Dwmapi
			)
endif ()

if (UNIX AND NOT APPLE)
	install(TARGETS ksnip RUNTIME DESTINATION /usr/bin)
endif ()
