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

set(ksnip_SRCS src/main.cpp
               src/backend/ImgurUploader.cpp
               src/backend/KsnipConfig.cpp
               src/backend/PlatformChecker.cpp
               src/backend/imageGrabber/AbstractImageGrabber.cpp
               src/backend/imageGrabber/X11ImageGrabber.cpp
               src/backend/imageGrabber/KdeWaylandImageGrabber.cpp
               src/backend/imageGrabber/ImageGrabberFactory.cpp
               src/backend/imageGrabber/X11Wrapper.cpp
               src/backend/imageGrabber/GnomeWaylandImageGrabber.cpp
               src/painter/PaintArea.cpp
               src/painter/AbstractPainterItem.cpp
               src/painter/PainterPen.cpp
               src/painter/PainterMarker.cpp
               src/painter/PainterRect.cpp
               src/painter/PainterEllipse.cpp
               src/painter/PainterLine.cpp
               src/painter/PainterArrow.cpp
               src/painter/PainterText.cpp
               src/painter/PainterNumber.cpp
               src/painter/PainterItemFactory.cpp
               src/painter/NumberSequencer.cpp
               src/painter/UndoCommands.cpp
               src/helper/StringFormattingHelper.cpp
               src/helper/MathHelper.cpp
               src/helper/CommandRunner.cpp
               src/helper/IconLoader.cpp
               src/widgets/CropPanel.cpp
               src/widgets/CaptureView.cpp
               src/widgets/CustomToolButton.cpp
               src/widgets/CustomCursor.cpp
               src/widgets/CursorFactory.cpp
               src/widgets/NumericComboBox.cpp
               src/widgets/ContextMenu.cpp
               src/widgets/ColorButton.cpp
               src/widgets/CustomSpinBox.cpp
               src/widgets/settingsPicker/SettingsPicker.cpp
               src/widgets/settingsPicker/SettingsPickerPopup.cpp
               src/widgets/settingsPicker/SettingsPickerButton.cpp
               src/widgets/settingsPicker/SettingsPickerColorItem.cpp
               src/widgets/settingsPicker/SettingsPickerConfigurator.cpp
               src/gui/MainWindow.cpp
               src/gui/SnippingArea.cpp
               src/gui/SettingsDialog.cpp
               src/gui/AboutDialog.cpp
               src/gui/ScaleDialog.cpp)


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
