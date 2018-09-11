set(ksnip_SRCS
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/ImgurUploader.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/KsnipConfig.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/PlatformChecker.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11ImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/ImageGrabberFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11Wrapper.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/CapturePrinter.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/CaptureUploader.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PaintArea.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/AbstractPainterItem.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterPen.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterMarker.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterRect.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterEllipse.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterLine.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterArrow.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterText.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterNumber.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/PainterItemFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/NumberSequencer.cpp
        ${CMAKE_SOURCE_DIR}/src/painter/UndoCommands.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/MathHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/CommandLineParserHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/MessageBoxHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/runner/CommandRunner.cpp
        ${CMAKE_SOURCE_DIR}/src/common/loader/IconLoader.cpp
        ${CMAKE_SOURCE_DIR}/src/common/handler/DelayHandler.cpp
        ${CMAKE_SOURCE_DIR}/src/common/formatter/FilenameFormatter.cpp
        ${CMAKE_SOURCE_DIR}/src/common/formatter/ConfigNameFormatter.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CropPanel.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CaptureView.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CustomToolButton.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CustomCursor.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CursorFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/NumericComboBox.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ContextMenu.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ColorButton.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CustomSpinBox.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/settingsPicker/SettingsPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/settingsPicker/SettingsPickerPopup.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/settingsPicker/SettingsPickerButton.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/settingsPicker/SettingsPickerColorItem.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/settingsPicker/SettingsPickerConfigurator.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ToolPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/CaptureModePicker.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/MainWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/SnippingArea.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/SettingsDialog.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/AboutDialog.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/ScaleDialog.cpp)

set(ksnip_SRCS ${ksnip_SRCS} PARENT_SCOPE)

add_executable(ksnip ${ksnip_SRCS} ${CMAKE_SOURCE_DIR}/icons/resources.qrc)

target_link_libraries(ksnip
        Qt5::Widgets
        Qt5::Network
        Qt5::Xml
        Qt5::PrintSupport
        Qt5::X11Extras
        Qt5::DBus
        XCB::XFIXES
        X11
        kImageAnnotator
        )

install(TARGETS ksnip RUNTIME DESTINATION /bin)