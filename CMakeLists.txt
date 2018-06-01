cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(ksnip)

set (KSNIP_VERSION_MAJOR "1")
set (KSNIP_VERSION_MINOR "5")
set (KSNIP_VERSION_MICRO "0-alpha")

if(DEFINED VERSION_SUFIX)
    set(KSNIP_VERSION_SUFIX "-${VERSION_SUFIX}")
endif()

set (KSNIP_VERSION "${KSNIP_VERSION_MAJOR}.${KSNIP_VERSION_MINOR}.${KSNIP_VERSION_MICRO}${KSNIP_VERSION_SUFIX}")
set (KSNIP_LANG_INSTAL_DIR "/usr/share/ksnip/translations")

configure_file(src/BuildConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/BuildConfig.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(QT_MIN_VERSION "5.4.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets Network Xml PrintSupport DBus)

# Without ECM we're unable to load XCB
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(X11 REQUIRED)

# Check for required XCB components
find_package(XCB COMPONENTS XFIXES)

if (XCB_FOUND)
    find_package(Qt5X11Extras ${QT_MIN_VERSION} REQUIRED)
endif()

if(NOT XCB_XFIXES_FOUND)
    message(FATAL_ERROR "Required XCB Components missing: XCB-XFIXES")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ksnip_SRCS ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/ImgurUploader.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/KsnipConfig.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/PlatformChecker.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/AbstractImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11ImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/ImageGrabberFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/X11Wrapper.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
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
        ${CMAKE_SOURCE_DIR}/src/common/runner/CommandRunner.cpp
        ${CMAKE_SOURCE_DIR}/src/common/loader/IconLoader.cpp
        ${CMAKE_SOURCE_DIR}/src/common/handler/DelayHandler.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/formatter/FilenameFormatter.cpp
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

SET(ksnip_RES icons/resources.qrc)
qt5_add_resources(ksnip_RES_RCC ${ksnip_RES})

add_executable(ksnip ${ksnip_SRCS} ${ksnip_RES_RCC})

target_link_libraries(ksnip Qt5::Widgets
                            Qt5::Network
                            Qt5::Xml
                            Qt5::PrintSupport
                            Qt5::X11Extras
                            Qt5::DBus
                            XCB::XFIXES
                            X11)

install(TARGETS ksnip RUNTIME DESTINATION /bin)

add_subdirectory(translations)
add_subdirectory(desktop)
