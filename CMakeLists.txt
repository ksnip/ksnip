cmake_minimum_required(VERSION 2.6)
project(ksnip)
find_package(Qt4 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ksnip_SRCS src/SizeComboBox.cpp src/ColorComboBox.cpp src/SettingsDialog.cpp src/ImageGrabber.cpp src/PaintStroke.cpp src/CustomToolButton.cpp src/PaintArea.cpp src/MainWindow.cpp src/SnippingArea.cpp src/main.cpp)

qt4_automoc(${ksnip_SRCS})
add_executable(ksnip ${ksnip_SRCS})
target_link_libraries(ksnip ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} X11 )

install(TARGETS ksnip RUNTIME DESTINATION bin)
