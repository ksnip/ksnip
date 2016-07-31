cmake_minimum_required(VERSION 2.6)
project(ksnip)
find_package(Qt4 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ksnip_SRCS paintwindow.cpp snippingframe.cpp capturewindow.cpp main.cpp)

qt4_automoc(${ksnip_SRCS})
add_executable(ksnip ${ksnip_SRCS})
target_link_libraries(ksnip ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS ksnip RUNTIME DESTINATION bin)
