set(UNITTEST_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/common/helper/PathHelperTests.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/gui/captureHandler/MultiCaptureHandlerTests.cpp
	)

set(TESTUTILS_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/utils/CallCounter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mocks/CaptureTabStateHandlerMock.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mocks/ImageAnnotatorMock.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mocks/ClipboardMock.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/mocks/DesktopServiceMock.cpp
	)

add_library(KSNIP_STATIC STATIC ${KSNIP_SRCS})

target_link_libraries(KSNIP_STATIC
					  Qt5::Widgets
					  Qt5::Network
					  Qt5::Xml
					  Qt5::PrintSupport
					  Qt5::DBus
					  kImageAnnotator
					  kColorPicker
					  Qt5::Svg)

if (APPLE)
	target_link_libraries(KSNIP_STATIC "-framework CoreGraphics")
elseif (UNIX)
	target_link_libraries(KSNIP_STATIC
						  Qt5::X11Extras
						  XCB::XFIXES
						  X11
						  )
elseif(WIN32)
	target_link_libraries(KSNIP_STATIC
						  Qt5::WinExtras
						  Dwmapi
						  )
endif ()

foreach (UnitTest ${UNITTEST_SRC})
	get_filename_component(UnitTestName ${UnitTest} NAME_WE)
	add_executable(${UnitTestName} ${UnitTest} ${TESTUTILS_SRC})
	target_link_libraries(${UnitTestName} KSNIP_STATIC Qt5::Test)
	add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)