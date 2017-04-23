cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(ksnip)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(QT_MIN_VERSION "5.4.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets Network Xml PrintSupport)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ksnip_SRCS src/main.cpp
               src/widgets/CropPanel.cpp
               src/backend/ImgurUploader.cpp
               src/backend/StringManip.cpp
               src/backend/KsnipConfig.cpp
               src/backend/ImageGrabber.cpp
               src/backend/CmdParser.cpp
               src/backend/CmdOption.cpp
               src/painter/PaintArea.cpp
               src/painter/PainterBaseItem.cpp
               src/painter/PainterPath.cpp
               src/painter/PainterRect.cpp
               src/painter/PainterEllipse.cpp
               src/painter/PainterText.cpp
               src/widgets/CaptureView.cpp
               src/widgets/CustomToolButton.cpp
               src/widgets/CustomCursor.cpp
               src/widgets/NumericComboBox.cpp
               src/widgets/PainterSettingsPicker.cpp
               src/widgets/UndoCommands.cpp
               src/gui/MainWindow.cpp
               src/gui/SnippingArea.cpp
               src/gui/SettingsDialog.cpp
               src/gui/AboutDialog.cpp
               )

SET(ksnip_RES icons/resources.qrc)
qt5_add_resources(ksnip_RES_RCC ${ksnip_RES})

add_executable(ksnip ${ksnip_SRCS} ${ksnip_RES_RCC})

target_link_libraries(ksnip Qt5::Widgets
                            Qt5::Network
                            Qt5::Xml
                            Qt5::PrintSupport
                            )

install(TARGETS ksnip RUNTIME DESTINATION /bin)

add_subdirectory(desktop)
