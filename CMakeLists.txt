cmake_minimum_required(VERSION 2.6)
project(ksnip)

find_package(KDE4 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

set(ksnip_SRCS src/AboutDialog.cpp 
               src/NumericComboBox.cpp 
               src/ColorComboBox.cpp 
               src/SettingsDialog.cpp 
               src/ImageGrabber.cpp 
               src/PaintStroke.cpp 
               src/CustomToolButton.cpp 
               src/PaintArea.cpp 
               src/MainWindow.cpp 
               src/SnippingArea.cpp 
               src/main.cpp)
               
SET(ksnip_RES resources.qrc)
qt4_add_resources(ksnip_RES_RCC ${ksnip_RES})

qt4_automoc(${ksnip_SRCS})
 
add_executable(ksnip ${ksnip_SRCS} ${ksnip_RES_RCC})

target_link_libraries(ksnip ${KDE4_KDEUI_LIBS} ${X11_LIBRARIES})

install(TARGETS ksnip RUNTIME DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS ksnip.desktop DESTINATION /usr/share/applications)

add_subdirectory(icons)