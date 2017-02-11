cmake_minimum_required(VERSION 2.6)
project(ksnip)

find_package(Qt4 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ksnip_SRCS src/main.cpp
               src/widgets/CropPanel.cpp
               src/backend/ImgurUploader.cpp
               src/backend/StringManip.cpp
               src/backend/KsnipConfig.cpp
               src/backend/ImageGrabber.cpp
               src/backend/CmdParser.cpp
               src/backend/CmdOption.cpp
               src/painter/PaintStroke.cpp
               src/painter/PaintArea.cpp
               src/widgets/CaptureView.cpp
               src/widgets/CustomToolButton.cpp
               src/widgets/CustomCursor.cpp
               src/widgets/NumericComboBox.cpp
               src/widgets/ColorComboBox.cpp
               src/gui/MainWindow.cpp
               src/gui/SnippingArea.cpp
               src/gui/SettingsDialog.cpp
               src/gui/AboutDialog.cpp
               )

SET(ksnip_RES icons/resources.qrc)
qt4_add_resources(ksnip_RES_RCC ${ksnip_RES})

qt4_automoc(${ksnip_SRCS})

add_executable(ksnip ${ksnip_SRCS} ${ksnip_RES_RCC})

target_link_libraries(ksnip ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTXML_LIBRARY} X11 Xfixes )

install(TARGETS ksnip RUNTIME DESTINATION /bin)

add_subdirectory(desktop)
