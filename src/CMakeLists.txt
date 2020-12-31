set(KSNIP_SRCS
    main.cpp
    backend/config/KsnipConfig.cpp
    backend/config/KsnipConfigOptions.cpp
    backend/config/KsnipConfigProvider.cpp
    backend/imageGrabber/AbstractImageGrabber.cpp
    backend/imageGrabber/AbstractRectAreaImageGrabber.cpp
    backend/imageGrabber/ImageGrabberFactory.cpp
    backend/uploader/imgur/ImgurWrapper.cpp
    backend/uploader/imgur/ImgurResponse.cpp
    backend/uploader/imgur/ImgurUploader.cpp
    backend/uploader/imgur/ImgurResponseLogger.cpp
    backend/uploader/script/ScriptUploader.cpp
    backend/uploader/UploaderProvider.cpp
    backend/saver/SavePathProvider.cpp
    backend/saver/ImageSaver.cpp
    backend/saver/WildcardResolver.cpp
    backend/saver/UniqueNameProvider.cpp
    backend/CapturePrinter.cpp
    backend/TranslationLoader.cpp
    backend/KsnipCommandLine.cpp
    backend/WatermarkImageLoader.cpp
    backend/ipc/IpcServer.cpp
    backend/ipc/IpcClient.cpp
    common/adapter/fileDialog/FileDialogAdapter.cpp
    common/adapter/fileDialog/SnapFileDialogAdapter.cpp
    common/adapter/fileDialog/FileDialogAdapterFactory.cpp
    common/helper/MathHelper.cpp
    common/helper/PathHelper.cpp
    common/helper/FileUrlHelper.cpp
    common/helper/RectHelper.cpp
    common/loader/IconLoader.cpp
    common/handler/DelayHandler.cpp
    common/handler/DragAndDropHandler.cpp
    common/provider/ApplicationTitleProvider.cpp
    common/provider/NewCaptureNameProvider.cpp
    common/provider/PathFromCaptureProvider.cpp
    widgets/CustomToolButton.cpp
    widgets/CustomCursor.cpp
    widgets/CursorFactory.cpp
    widgets/NumericComboBox.cpp
    widgets/CustomSpinBox.cpp
    widgets/CaptureModePicker.cpp
    widgets/ColorButton.cpp
    widgets/MainToolBar.cpp
    widgets/KeySequenceLineEdit.cpp
    widgets/CustomLineEdit.cpp
    gui/MainWindow.cpp
    gui/ImgurHistoryDialog.cpp
    gui/TrayIcon.cpp
    gui/clipboard/ClipboardAdapter.cpp
    gui/clipboard/IClipboard.h
    gui/imageAnnotator/KImageAnnotatorAdapter.cpp
    gui/imageAnnotator/IImageAnnotator.h
    gui/desktopService/DesktopServiceAdapter.cpp
    gui/fileService/FileService.cpp
    gui/widgetVisibilityHandler/WidgetVisibilityHandler.cpp
    gui/widgetVisibilityHandler/GnomeWaylandWidgetVisibilityHandler.cpp
    gui/widgetVisibilityHandler/WidgetVisibilityHandlerFactory.cpp
    gui/snippingArea/AbstractSnippingArea.cpp
    gui/snippingArea/SnippingAreaAdorner.cpp
    gui/snippingArea/AdornerMagnifyingGlass.cpp
    gui/snippingArea/AdornerRulers.cpp
    gui/snippingArea/AdornerPositionInfo.cpp
    gui/snippingArea/AdornerSizeInfo.cpp
    gui/snippingArea/SnippingAreaResizer.cpp
    gui/snippingArea/SnippingAreaSelector.cpp
    gui/snippingArea/SnippingAreaInfoText.cpp
    gui/settingsDialog/AnnotationSettings.cpp
    gui/settingsDialog/ApplicationSettings.cpp
    gui/settingsDialog/ImageGrabberSettings.cpp
    gui/settingsDialog/ImgurUploaderSettings.cpp
    gui/settingsDialog/ScriptUploaderSettings.cpp
    gui/settingsDialog/HotKeySettings.cpp
    gui/settingsDialog/UploaderSettings.cpp
    gui/settingsDialog/SaverSettings.cpp
    gui/settingsDialog/StickerSettings.cpp
    gui/settingsDialog/SnippingAreaSettings.cpp
    gui/settingsDialog/SettingsDialog.cpp
    gui/aboutDialog/AboutDialog.cpp
    gui/aboutDialog/AboutTab.cpp
    gui/aboutDialog/VersionTab.cpp
    gui/aboutDialog/AuthorTab.cpp
    gui/aboutDialog/DonateTab.cpp
    gui/globalHotKeys/GlobalHotKey.cpp
    gui/globalHotKeys/NativeKeyEventFilter.cpp
    gui/globalHotKeys/AbstractKeyHandler.cpp
    gui/globalHotKeys/KeyHandlerFactory.cpp
    gui/globalHotKeys/GlobalHotKeyHandler.cpp
    gui/globalHotKeys/HotKeyMap.cpp
    gui/globalHotKeys/DummyKeyHandler.cpp
    gui/operations/SaveOperation.cpp
    gui/operations/RenameOperation.cpp
    gui/operations/AddWatermarkOperation.cpp
    gui/operations/UpdateWatermarkOperation.cpp
    gui/operations/WatermarkImagePreparer.cpp
    gui/operations/CanDiscardOperation.cpp
    gui/operations/UploadOperation.cpp
    gui/operations/HandleUploadResultOperation.cpp
    gui/operations/NotifyOperation.cpp
    gui/operations/DeleteImageOperation.cpp
    gui/captureHandler/CaptureTabStateHandler.cpp
    gui/captureHandler/ICaptureTabStateHandler.h
    gui/captureHandler/CaptureHandlerFactory.cpp
    gui/captureHandler/SingleCaptureHandler.cpp
    gui/captureHandler/MultiCaptureHandler.cpp
    gui/captureHandler/TabContextMenuAction.cpp
    gui/pinWindow/PinWindow.cpp
    gui/pinWindow/PinWindowHandler.cpp
    gui/messageBoxService/MessageBoxService.cpp
    gui/serviceLocator/ServiceLocator.cpp
    bootstrapper/BootstrapperFactory.cpp
    bootstrapper/StandAloneBootstrapper.cpp
	bootstrapper/singleInstance/InstanceLock.cpp
    bootstrapper/singleInstance/SingleInstanceClientBootstrapper.cpp
    bootstrapper/singleInstance/SingleInstanceServerBootstrapper.cpp
    bootstrapper/singleInstance/SingleInstanceParameterTranslator.cpp
    )

if (APPLE)
    list(APPEND KSNIP_SRCS
        backend/imageGrabber/MacImageGrabber.cpp
        backend/imageGrabber/MacWrapper.cpp
        backend/config/KsnipMacConfig.cpp
        gui/snippingArea/MacSnippingArea.cpp
        gui/globalHotKeys/DummyKeyHandler.cpp
        gui/globalHotKeys/MacKeyHandler.cpp
        gui/globalHotKeys/KeySequenceToMacKeyCodeTranslator.cpp
        common/platform/HdpiScaler.mm
        )
elseif (UNIX)
    list(APPEND KSNIP_SRCS
        backend/imageGrabber/X11ImageGrabber.cpp
        backend/imageGrabber/KdeWaylandImageGrabber.cpp
        backend/imageGrabber/X11Wrapper.cpp
        backend/imageGrabber/GnomeWaylandImageGrabber.cpp
        backend/imageGrabber/WaylandImageGrabber.cpp
        backend/config/KsnipWaylandConfig.cpp
        common/platform/PlatformChecker.cpp
        common/platform/CommandRunner.cpp
        gui/snippingArea/LinuxSnippingArea.cpp
        gui/globalHotKeys/X11KeyHandler.cpp
        gui/globalHotKeys/KeySequenceToX11KeyCodeTranslator.cpp
        gui/globalHotKeys/X11ErrorLogger.cpp
        common/platform/HdpiScaler.cpp
        )
elseif (WIN32)
    list(APPEND KSNIP_SRCS
        backend/imageGrabber/WinImageGrabber.cpp
        backend/imageGrabber/WinWrapper.cpp
        gui/snippingArea/WinSnippingArea.cpp
        gui/globalHotKeys/WinKeyHandler.cpp
        gui/globalHotKeys/KeySequenceToWinKeyCodeTranslator.cpp
        common/platform/HdpiScaler.cpp
        )
endif ()

# Set the sources variable in the top-level as well, since the tests/
# directory wants to (re)build as well.
set(KSNIP_SRCS ${KSNIP_SRCS} PARENT_SCOPE)

if (WIN32)
    add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${CMAKE_SOURCE_DIR}/icons/ksnip_windows_icon.rc)
elseif (APPLE)
    set(MACOSX_BUNDLE_EXECUTABLE_NAME "ksnip")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ksnip.ksnip")
    set(MACOSX_BUNDLE_ICON_FILE "ksnip.icns")
    set(MACOSX_BUNDLE_INFO_STRING "Cross-Platform Screenshot and Annotation Tool")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${KSNIP_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})

    set(MACOSX_ICON ${CMAKE_SOURCE_DIR}/icons/ksnip.icns backend/imageGrabber/AbstractImageGrabber.cpp backend/imageGrabber/AbstractImageGrabber.h)
    set_source_files_properties(${MACOSX_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(ksnip MACOSX_BUNDLE ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc ${MACOSX_ICON})
else()
    add_executable(ksnip ${KSNIP_SRCS} ${CMAKE_SOURCE_DIR}/icons/ksnip_icons.qrc)
endif ()

set(DEPENDENCY_LIBRARIES
    Qt5::Widgets
    Qt5::Network
    Qt5::Xml
    Qt5::PrintSupport
    Qt5::DBus
    Qt5::Svg
    )

if (APPLE)
    list(APPEND DEPENDENCY_LIBRARIES
            kImageAnnotator::kImageAnnotator
            kColorPicker::kColorPicker
            "-framework CoreGraphics -framework AppKit"
            )
elseif (UNIX)
    list(APPEND DEPENDENCY_LIBRARIES
            Qt5::X11Extras
            kImageAnnotator
            kColorPicker
            XCB::XFIXES
            X11
            )
    # This is the "UNIX AND NOT APPLE" case, which is the Free Desktop
    # world: Linux and the BSDs and Illumos. To simplify #ifdefs in
    # the source, add a UNIX_X11 defined to be used instead of __linux__ etc.
    # While the "X11" part of the define isn't necessarily accurate,
    # it is easy to spot.
    target_compile_definitions(ksnip PRIVATE UNIX_X11)
elseif(WIN32)
    list(APPEND DEPENDENCY_LIBRARIES
            Qt5::WinExtras
            kImageAnnotator
            kColorPicker
            Dwmapi
            )
endif ()

target_link_libraries(ksnip ${DEPENDENCY_LIBRARIES})

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
