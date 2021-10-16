/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

/*
 * Example taken from https://rodolfotech.blogspot.com/2017/01/qtest-google-mock.html
 */

#ifndef KSNIP_TESTRUNNER_H
#define KSNIP_TESTRUNNER_H

#include <gmock/gmock.h>

class GoogleTestEventListener : public ::testing::EmptyTestEventListener {

	void OnTestStart(const ::testing::TestInfo&) override {
	}

	void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override {
		if (test_part_result.failed()) {
			QFAIL(
					QString("mock objects failed with '%1' at %2:%3")
							.arg(QString(test_part_result.summary()))
							.arg(test_part_result.file_name())
							.arg(test_part_result.line_number())
							.toLatin1().constData()
			);
		}
	}

	void OnTestEnd(const ::testing::TestInfo&) override {
	}
};


#define INIT_GOOGLE_MOCKS(argc, argv) { \
      ::testing::InitGoogleTest (&(argc), (argv)); \
      ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();  \
      delete listeners.Release(listeners.default_result_printer());\
      listeners.Append(new GoogleTestEventListener); }

/*
 * Taken from QTEST_MAIN macro and added additional INIT_GOOGLE_MOCKS in the calls.
 */

#if defined(QT_WIDGETS_LIB)

#include <QtTest/qtest_widgets.h>

#ifdef QT_KEYPAD_NAVIGATION
#  define QTEST_DISABLE_KEYPAD_NAVIGATION QApplication::setNavigationMode(Qt::NavigationModeNone);
#else
#  define QTEST_DISABLE_KEYPAD_NAVIGATION
#endif

#define TEST_MAIN(TestObject) \
QT_BEGIN_NAMESPACE \
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS \
QT_END_NAMESPACE \
int main(int argc, char *argv[]) \
{   \
    INIT_GOOGLE_MOCKS (argc, argv); \
	\
    QApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \
    QTEST_DISABLE_KEYPAD_NAVIGATION \
    QTEST_ADD_GPU_BLACKLIST_SUPPORT \
    TestObject tc; \
    QTEST_SET_MAIN_SOURCE_PATH \
    return QTest::qExec(&tc, argc, argv); \
}

#elif defined(QT_GUI_LIB)

#include <QtTest/qtest_gui.h>

#define TEST_MAIN(TestObject) \
QT_BEGIN_NAMESPACE \
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS \
QT_END_NAMESPACE \
int main(int argc, char *argv[]) \
{   \
    INIT_GOOGLE_MOCKS (argc, argv); \
    \
    QGuiApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \
    QTEST_ADD_GPU_BLACKLIST_SUPPORT \
    TestObject tc; \
    QTEST_SET_MAIN_SOURCE_PATH \
    return QTest::qExec(&tc, argc, argv); \
}

#else

#define TEST_MAIN(TestObject) \
int main(int argc, char *argv[]) \
{   \
    INIT_GOOGLE_MOCKS (argc, argv); \
    \
    QCoreApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true); \
    TestObject tc; \
    QTEST_SET_MAIN_SOURCE_PATH \
    return QTest::qExec(&tc, argc, argv); \
}

#endif // QT_GUI_LIB

#endif //KSNIP_TESTRUNNER_H
