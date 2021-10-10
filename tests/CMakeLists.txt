find_package(GTest CONFIG REQUIRED)

enable_testing()

set(UNITTEST_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/backend/recentImages/RecentImagesPathStoreTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/backend/commandLine/CommandLineCaptureHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/helper/PathHelperTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/actions/ActionTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/actions/ActionProcessorTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/captureHandler/MultiCaptureHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/captureHandler/SingleCaptureHandlerTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/operations/DeleteImageOperationTests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/gui/operations/LoadImageFromFileOperationTests.cpp
	)

set(TESTUTILS_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/backend/uploader/UploadHandlerMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/backend/imageGrabber/ImageGrabberMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/backend/recentImages/ImagePathStorageMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/backend/recentImages/RecentImageServiceMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/backend/config/ConfigMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/fileService/FileServiceMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/messageBoxService/MessageBoxServiceMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/NotificationServiceMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/ImageProcessorMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/desktopService/DesktopServiceMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/clipboard/ClipboardMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/mocks/gui/captureHandler/CaptureTabStateHandlerMock.h)

add_library(KSNIP_STATIC ${KSNIP_SRCS})

target_link_libraries(KSNIP_STATIC
	Qt5::Widgets
	Qt5::Network
	Qt5::Xml
	Qt5::PrintSupport
	Qt5::DBus
	kImageAnnotator::kImageAnnotator
	kColorPicker::kColorPicker
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

	target_compile_definitions(KSNIP_STATIC PUBLIC UNIX_X11)
elseif(WIN32)
	target_link_libraries(KSNIP_STATIC
		Qt5::WinExtras
		Dwmapi
		)
endif ()

foreach (UnitTest ${UNITTEST_SRC})
	get_filename_component(UnitTestName ${UnitTest} NAME_WE)
	add_executable(${UnitTestName} ${UnitTest} ${TESTUTILS_SRC} )
	target_link_libraries(${UnitTestName} KSNIP_STATIC GTest::gmock Qt5::Test )
	add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
