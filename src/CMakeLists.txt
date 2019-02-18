set(KSNIP_SRCS
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/backend/ImgurUploader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/UploadResponse.cpp
	${CMAKE_SOURCE_DIR}/src/backend/KsnipConfig.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractImageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/ImageGrabberFactory.cpp
	${CMAKE_SOURCE_DIR}/src/backend/CapturePrinter.cpp
	${CMAKE_SOURCE_DIR}/src/backend/CaptureUploader.cpp
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
	${CMAKE_SOURCE_DIR}/src/gui/AbstractSnippingArea.cpp
	${CMAKE_SOURCE_DIR}/src/gui/SettingsDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/AboutDialog.cpp
    )

if (UNIX)
    set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/PlatformChecker.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11ImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11Wrapper.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/common/runner/CommandRunner.cpp
		${CMAKE_SOURCE_DIR}/src/gui/LinuxSnippingArea.cpp
		)
elseif (WIN32)
	set(KSNIP_SRCS
			${KSNIP_SRCS}
            ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinImageGrabber.cpp
			${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinWrapper.cpp
            ${CMAKE_SOURCE_DIR}/src/gui/WinSnippingArea.cpp
			)
endif ()

set(KSNIP_SRCS ${KSNIP_SRCS} PARENT_SCOPE)

if (WIN32)
	add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${CMAKE_SOURCE_DIR}/icons/ksnip_windows_icon.rc)
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

if (UNIX)
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

install(TARGETS ksnip RUNTIME DESTINATION /bin)