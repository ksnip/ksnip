set(UNITTEST_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/backend/recentImages/RecentImagesPathStoreTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/helper/PathHelperTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/captureHandler/MultiCaptureHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/captureHandler/SingleCaptureHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/operations/DeleteImageOperationTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/operations/LoadImageFromFileOperationTests.cpp
	)

set(TESTUTILS_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/utils/CallCounter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/CaptureTabStateHandlerMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ImageAnnotatorMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ClipboardMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/DesktopServiceMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/MessageBoxServiceMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/FileServiceMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ServiceLocatorMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ImagePathStorageMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ToastServiceMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/RecentImageServiceMock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/ImageProcessorMock.cpp
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
	Qt5::Svg
	)

if (APPLE)
	target_link_libraries(KSNIP_STATIC "-framework CoreGraphics")
elseif (UNIX)
	target_link_libraries(KSNIP_STATIC
		Qt5::X11Extras
		XCB::XFIXES
		)

	# X11::X11 imported target only available with sufficiently new CMake
	if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.14.0)
		target_link_libraries(KSNIP_STATIC X11::X11)
	else()
		target_link_libraries(KSNIP_STATIC X11)
	endif()

	target_compile_definitions(KSNIP_STATIC PRIVATE UNIX_X11)
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
