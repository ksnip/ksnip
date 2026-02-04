cmake_minimum_required(VERSION 3.5)
project(ksnip LANGUAGES CXX VERSION 1.11.0)

if (DEFINED VERSION_SUFIX AND NOT "${VERSION_SUFIX}" STREQUAL "")
	set(KSNIP_VERSION_SUFIX "-${VERSION_SUFIX}")
endif()

set(KSNIP_VERSION "${PROJECT_VERSION}${KSNIP_VERSION_SUFIX}")

include(GNUInstallDirs)

if (WIN32)
	set(KSNIP_LANG_INSTALL_DIR "translations")
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "translations")
elseif (APPLE)
	set(KSNIP_LANG_INSTALL_DIR "../Resources")
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "../Resources")
elseif (UNIX)
	set(KSNIP_LANG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/ksnip/translations")
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/kImageAnnotator/translations")
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build Unit Tests" OFF)
option(USE_SUBMODULE_KCOLORPICKER "Build kColorPicker from submodule" OFF)
option(USE_SUBMODULE_KIMAGEANNOTATOR "Build kImageAnnotator from submodule" OFF)

if (UNIX AND NOT APPLE)
	# Without ECM we're unable to load XCB
	find_package(ECM REQUIRED NO_MODULE)
	set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

	find_package(X11 REQUIRED)
	find_package(XCB COMPONENTS XFIXES)
endif ()

set(QT_COMPONENTS Core Widgets Network Xml PrintSupport DBus Svg)
set(QT_MIN_VERSION 5.15.2)

option(BUILD_WITH_QT6 "Build against Qt6" OFF)

set(KSNIP_QT6 ${BUILD_WITH_QT6})
configure_file(src/BuildConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/BuildConfig.h)

if (BUILD_WITH_QT6)
	set(QT_MAJOR_VERSION 6)
else()
	set(QT_MAJOR_VERSION 5)
endif()

if (UNIX AND NOT APPLE)
	list(APPEND QT_COMPONENTS Concurrent)
endif()

if (X11_FOUND AND NOT BUILD_WITH_QT6)
	list(APPEND QT_COMPONENTS X11Extras)
elseif (WIN32)
	list(APPEND QT_COMPONENTS WinExtras)
endif()

if (BUILD_TESTS)
	list(APPEND QT_COMPONENTS Test)
endif()

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED ${QT_COMPONENTS})

if (APPLE AND BUILD_WITH_QT6)
	get_target_property(_qt_gui_libs Qt6::Gui INTERFACE_LINK_LIBRARIES)
	if (_qt_gui_libs)
		list(REMOVE_ITEM _qt_gui_libs WrapOpenGL::WrapOpenGL)
		set_target_properties(Qt6::Gui PROPERTIES INTERFACE_LINK_LIBRARIES "${_qt_gui_libs}")
	endif()
endif()

set(KIMAGEANNOTATOR_MIN_VERSION 0.7.1)
set(KIMAGEANNOTATOR_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries/kImageAnnotator")
set(KCOLORPICKER_MIN_VERSION 0.3.0)
set(KCOLORPICKER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/libraries/kColorPicker")
if (USE_SUBMODULE_KCOLORPICKER AND EXISTS "${KCOLORPICKER_SOURCE_DIR}/CMakeLists.txt")
	set(BUILD_EXAMPLE OFF CACHE BOOL "Build kColorPicker example application" FORCE)
	add_subdirectory("${KCOLORPICKER_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/kColorPicker")
	if (TARGET kColorPicker AND NOT TARGET kColorPicker::kColorPicker)
		add_library(kColorPicker::kColorPicker ALIAS kColorPicker)
	endif()
	set("kColorPicker-Qt${QT_MAJOR_VERSION}_DIR"
		"${CMAKE_BINARY_DIR}/kColorPicker/cmake"
		CACHE PATH "Path to kColorPicker-Qt${QT_MAJOR_VERSION}Config.cmake" FORCE)
else()
	find_package(kColorPicker-Qt${QT_MAJOR_VERSION} ${KCOLORPICKER_MIN_VERSION} REQUIRED)
endif()

if (USE_SUBMODULE_KIMAGEANNOTATOR AND EXISTS "${KIMAGEANNOTATOR_SOURCE_DIR}/CMakeLists.txt")
	set(BUILD_EXAMPLE OFF CACHE BOOL "Build kImageAnnotator example application" FORCE)
	add_subdirectory("${KIMAGEANNOTATOR_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/kImageAnnotator")
else()
	find_package(kImageAnnotator-Qt${QT_MAJOR_VERSION} ${KIMAGEANNOTATOR_MIN_VERSION} REQUIRED)
endif()

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

add_subdirectory(src)
add_subdirectory(translations)
add_subdirectory(desktop)

if (BUILD_TESTS)
	configure_file(src/BuildConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/tests/BuildConfig.h)

	add_subdirectory(tests)
endif (BUILD_TESTS)
