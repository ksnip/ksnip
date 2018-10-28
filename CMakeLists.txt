cmake_minimum_required(VERSION 3.5)
project(ksnip LANGUAGES CXX VERSION 1.5.0)

if (DEFINED VERSION_SUFIX)
    set(KSNIP_VERSION_SUFIX "-${VERSION_SUFIX}")
endif()

set(KSNIP_VERSION "${PROJECT_VERSION}${KSNIP_VERSION_SUFIX}")
set(KSNIP_LANG_INSTAL_DIR "/usr/share/ksnip/translations")

configure_file(src/BuildConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/BuildConfig.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(QT_MIN_VERSION "5.6.1")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Network Xml PrintSupport DBus X11Extras)

# Without ECM we're unable to load XCB
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(X11 REQUIRED)
find_package(XCB COMPONENTS XFIXES)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

add_subdirectory(external/kImageAnnotator EXCLUDE_FROM_ALL)
add_subdirectory(src)
add_subdirectory(translations)
add_subdirectory(desktop)
