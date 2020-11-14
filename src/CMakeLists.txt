set(KSNIP_SRCS
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/backend/config/KsnipConfig.cpp
	${CMAKE_SOURCE_DIR}/src/backend/config/KsnipConfigOptions.cpp
	${CMAKE_SOURCE_DIR}/src/backend/config/KsnipConfigProvider.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractImageGrabber.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractRectAreaImageGrabber.cpp
	${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/ImageGrabberFactory.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/imgur/ImgurWrapper.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/imgur/ImgurResponse.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/imgur/ImgurUploader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/imgur/ImgurResponseLogger.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/script/ScriptUploader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/uploader/UploaderProvider.cpp
	${CMAKE_SOURCE_DIR}/src/backend/saver/SavePathProvider.cpp
	${CMAKE_SOURCE_DIR}/src/backend/saver/ImageSaver.cpp
	${CMAKE_SOURCE_DIR}/src/backend/saver/WildcardResolver.cpp
	${CMAKE_SOURCE_DIR}/src/backend/saver/UniqueNameProvider.cpp
	${CMAKE_SOURCE_DIR}/src/backend/CapturePrinter.cpp
	${CMAKE_SOURCE_DIR}/src/backend/TranslationLoader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/KsnipCommandLine.cpp
	${CMAKE_SOURCE_DIR}/src/backend/WatermarkImageLoader.cpp
	${CMAKE_SOURCE_DIR}/src/backend/ipc/IpcServer.cpp
	${CMAKE_SOURCE_DIR}/src/backend/ipc/IpcClient.cpp
	${CMAKE_SOURCE_DIR}/src/common/adapter/fileDialog/FileDialogAdapter.cpp
	${CMAKE_SOURCE_DIR}/src/common/adapter/fileDialog/SnapFileDialogAdapter.cpp
	${CMAKE_SOURCE_DIR}/src/common/adapter/fileDialog/FileDialogAdapterFactory.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/MathHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/PathHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/FileUrlHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/helper/RectHelper.cpp
	${CMAKE_SOURCE_DIR}/src/common/loader/IconLoader.cpp
	${CMAKE_SOURCE_DIR}/src/common/handler/DelayHandler.cpp
	${CMAKE_SOURCE_DIR}/src/common/handler/DragAndDropHandler.cpp
	${CMAKE_SOURCE_DIR}/src/common/provider/ApplicationTitleProvider.cpp
	${CMAKE_SOURCE_DIR}/src/common/provider/NewCaptureNameProvider.cpp
	${CMAKE_SOURCE_DIR}/src/common/provider/PathFromCaptureProvider.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomToolButton.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomCursor.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CursorFactory.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/NumericComboBox.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomSpinBox.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CaptureModePicker.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/ColorButton.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/MainToolBar.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/KeySequenceLineEdit.cpp
	${CMAKE_SOURCE_DIR}/src/widgets/CustomLineEdit.cpp
	${CMAKE_SOURCE_DIR}/src/gui/MainWindow.cpp
	${CMAKE_SOURCE_DIR}/src/gui/ImgurHistoryDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/TrayIcon.cpp
	${CMAKE_SOURCE_DIR}/src/gui/clipboard/ClipboardAdapter.cpp
	${CMAKE_SOURCE_DIR}/src/gui/clipboard/IClipboard.h
	${CMAKE_SOURCE_DIR}/src/gui/imageAnnotator/KImageAnnotatorAdapter.cpp
	${CMAKE_SOURCE_DIR}/src/gui/imageAnnotator/IImageAnnotator.h
	${CMAKE_SOURCE_DIR}/src/gui/desktopService/DesktopServiceAdapter.cpp
	${CMAKE_SOURCE_DIR}/src/gui/fileService/FileService.cpp
	${CMAKE_SOURCE_DIR}/src/gui/widgetVisibilityHandler/WidgetVisibilityHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/widgetVisibilityHandler/GnomeWaylandWidgetVisibilityHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/widgetVisibilityHandler/WidgetVisibilityHandlerFactory.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AbstractSnippingArea.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/SnippingAreaAdorner.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerMagnifyingGlass.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerRulers.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerPositionInfo.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/AdornerSizeInfo.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/SnippingAreaResizer.cpp
	${CMAKE_SOURCE_DIR}/src/gui/snippingArea/SnippingAreaSelector.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/AnnotationSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/ApplicationSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/ImageGrabberSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/ImgurUploaderSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/ScriptUploaderSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/HotKeySettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/UploaderSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/SaverSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/StickerSettings.cpp
	${CMAKE_SOURCE_DIR}/src/gui/settingsDialog/SettingsDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/aboutDialog/AboutDialog.cpp
	${CMAKE_SOURCE_DIR}/src/gui/aboutDialog/AboutTab.cpp
	${CMAKE_SOURCE_DIR}/src/gui/aboutDialog/VersionTab.cpp
	${CMAKE_SOURCE_DIR}/src/gui/aboutDialog/AuthorTab.cpp
	${CMAKE_SOURCE_DIR}/src/gui/aboutDialog/DonateTab.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/GlobalHotKey.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/NativeKeyEventFilter.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/AbstractKeyHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/KeyHandlerFactory.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/GlobalHotKeyHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/HotKeyMap.cpp
	${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/DummyKeyHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/SaveOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/RenameOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/AddWatermarkOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/UpdateWatermarkOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/WatermarkImagePreparer.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/CanDiscardOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/UploadOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/HandleUploadResultOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/NotifyOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/operations/DeleteImageOperation.cpp
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/CaptureTabStateHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/ICaptureTabStateHandler.h
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/CaptureHandlerFactory.cpp
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/SingleCaptureHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/MultiCaptureHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/captureHandler/TabContextMenuAction.cpp
	${CMAKE_SOURCE_DIR}/src/gui/pinWindow/PinWindow.cpp
	${CMAKE_SOURCE_DIR}/src/gui/pinWindow/PinWindowHandler.cpp
	${CMAKE_SOURCE_DIR}/src/gui/messageBoxService/MessageBoxService.cpp
	${CMAKE_SOURCE_DIR}/src/gui/serviceLocator/ServiceLocator.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/BootstrapperFactory.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/StandAloneBootstrapper.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/singleInstance/InstanceLock.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/singleInstance/SingleInstanceClientBootstrapper.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/singleInstance/SingleInstanceServerBootstrapper.cpp
	${CMAKE_SOURCE_DIR}/src/bootstrapper/singleInstance/SingleInstanceParameterTranslator.cpp
	)

if (APPLE)
	set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/MacImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/MacWrapper.cpp
		${CMAKE_SOURCE_DIR}/src/backend/config/KsnipMacConfig.cpp
		${CMAKE_SOURCE_DIR}/src/gui/snippingArea/MacSnippingArea.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/DummyKeyHandler.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/MacKeyHandler.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/KeySequenceToMacKeyCodeTranslator.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/HdpiScaler.mm
		)
elseif (UNIX)
    set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11ImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11Wrapper.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WaylandImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/config/KsnipWaylandConfig.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/PlatformChecker.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/CommandRunner.cpp
		${CMAKE_SOURCE_DIR}/src/gui/snippingArea/LinuxSnippingArea.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/X11KeyHandler.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/KeySequenceToX11KeyCodeTranslator.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/X11ErrorLogger.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/HdpiScaler.cpp
		)
elseif (WIN32)
	set(KSNIP_SRCS
		${KSNIP_SRCS}
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinImageGrabber.cpp
		${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/WinWrapper.cpp
		${CMAKE_SOURCE_DIR}/src/gui/snippingArea/WinSnippingArea.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/WinKeyHandler.cpp
		${CMAKE_SOURCE_DIR}/src/gui/globalHotKeys/KeySequenceToWinKeyCodeTranslator.cpp
		${CMAKE_SOURCE_DIR}/src/common/platform/HdpiScaler.cpp
		)
endif ()

set(KSNIP_SRCS ${KSNIP_SRCS} PARENT_SCOPE)

if (WIN32)
	add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${CMAKE_SOURCE_DIR}/icons/ksnip_windows_icon.rc)
elseif (APPLE)
	set(MACOSX_BUNDLE_EXECUTABLE_NAME "ksnip")
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ksnip.ksnip")
	set(MACOSX_BUNDLE_ICON_FILE "ksnip.icns")
	set(MACOSX_BUNDLE_INFO_STRING "Cross-Platform Screenshot and Annotation Tool")
	set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION})
	set(MACOSX_BUNDLE_LONG_VERSION_STRING ${KSNIP_VERSION})

	set(MACOSX_ICON ${CMAKE_SOURCE_DIR}/icons/ksnip.icns backend/imageGrabber/AbstractImageGrabber.cpp backend/imageGrabber/AbstractImageGrabber.h)
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
					  Qt5::Svg
					  )

if (APPLE)
	target_link_libraries(ksnip "-framework CoreGraphics -framework AppKit")
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
	install(TARGETS ksnip RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    # uninstall target
    if(NOT TARGET uninstall)
        configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

        add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
    endif ()
endif ()
