/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "KsnipCommandLine.h"

KsnipCommandLine::KsnipCommandLine(const QCoreApplication &app, const QList<CaptureModes> &captureModes)
{
    setApplicationDescription(translateText(QLatin1Literal("Ksnip Screenshot Tool")));
    addHelpOption();
    addVersionOptions();
    addImageGrabberOptions(captureModes);
    addDefaultOptions();
	addPositionalArguments();
	process(app);
}

KsnipCommandLine::~KsnipCommandLine()
{
    delete mRectAreaOption;
    delete mLastRectAreaOption;
    delete mFullScreenOption;
    delete mCurrentScreenOption;
    delete mActiveWindowOption;
    delete mWindowUnderCursorOption;
    delete mPortalOption;
    delete mDelayOption;
    delete mCursorOption;
    delete mEditOption;
    delete mSaveOption;
    delete mVersionOption;
}

void KsnipCommandLine::addImageGrabberOptions(const QList<CaptureModes> &captureModes)
{
    if (captureModes.contains(CaptureModes::RectArea)) {
        mRectAreaOption = addOption(QLatin1Literal("r"), QLatin1Literal("rectarea"), QLatin1Literal("Select a rectangular area from where to take a screenshot."));
    }
	if (captureModes.contains(CaptureModes::LastRectArea)) {
		mLastRectAreaOption = addOption(QLatin1Literal("l"), QLatin1Literal("lastrectarea"), QLatin1Literal("Take a screenshot using last selected rectangular area."));
	}
    if (captureModes.contains(CaptureModes::FullScreen)) {
        mFullScreenOption = addOption(QLatin1Literal("f"), QLatin1Literal("fullscreen"), QLatin1Literal("Capture the fullscreen including all monitors."));
    }
    if (captureModes.contains(CaptureModes::CurrentScreen)) {
        mCurrentScreenOption = addOption(QLatin1Literal("m"), QLatin1Literal("current"), QLatin1Literal("Capture the screen (monitor) where the mouse cursor is currently located."));
    }
    if (captureModes.contains(CaptureModes::ActiveWindow)) {
        mActiveWindowOption = addOption(QLatin1Literal("a"), QLatin1Literal("active"), QLatin1Literal("Capture the window that currently has input focus."));
    }
    if (captureModes.contains(CaptureModes::WindowUnderCursor)) {
        mWindowUnderCursorOption = addOption(QLatin1Literal("u"), QLatin1Literal("windowundercursor"), QLatin1Literal("Capture the window that is currently under the mouse cursor."));
    }
    if (captureModes.contains(CaptureModes::Portal)) {
        mWindowUnderCursorOption = addOption(QLatin1Literal("t"), QLatin1Literal("portal"), QLatin1Literal("Uses the screenshot Portal for taking screenshot."));
    }
}

void KsnipCommandLine::addDefaultOptions()
{
    mDelayOption = addParameterOption(QLatin1Literal("d"), QLatin1Literal("delay"), QLatin1Literal("Delay before taking the screenshot."), QLatin1Literal("seconds"));
    mCursorOption = addOption(QLatin1Literal("c"), QLatin1Literal("cursor"), QLatin1Literal("Capture mouse cursor on screenshot."));
    mEditOption = addParameterOption(QLatin1Literal("e"), QLatin1Literal("edit"), QLatin1Literal("Edit existing image in ksnip"), QLatin1Literal("image"));
    mSaveOption = addOption(QLatin1Literal("s"), QLatin1Literal("save"), QLatin1Literal("Save screenshot to default location without opening in editor."));
}

void KsnipCommandLine::addVersionOptions()
{
    mVersionOption = addOption(QLatin1Literal("v"), QLatin1Literal("version"), QLatin1Literal("Displays version information."));
}

QString KsnipCommandLine::translateText(const QString &text)
{
    return QCoreApplication::translate("main", text.toLatin1());
}

QCommandLineOption* KsnipCommandLine::addOption(const QString &shortName, const QString &longName, const QString &description)
{
    auto newOption = new QCommandLineOption({shortName, longName}, translateText(description));
    QCommandLineParser::addOption(*newOption);
    return newOption;
}

QCommandLineOption* KsnipCommandLine::addParameterOption(const QString &shortName, const QString &longName, const QString &description, const QString &parameter)
{
    auto newOption = new QCommandLineOption({shortName, longName}, translateText(description), translateText(parameter));
    QCommandLineParser::addOption(*newOption);
    return newOption;
}

bool KsnipCommandLine::isRectAreaSet() const
{
    return mRectAreaOption != nullptr && isSet(*mRectAreaOption);
}

bool KsnipCommandLine::isLastRectAreaSet() const
{
	return mLastRectAreaOption != nullptr && isSet(*mLastRectAreaOption);
}

bool KsnipCommandLine::isFullScreenSet() const
{
    return mFullScreenOption != nullptr && isSet(*mFullScreenOption);
}

bool KsnipCommandLine::isCurrentScreenSet() const
{
    return mCurrentScreenOption != nullptr && isSet(*mCurrentScreenOption);
}

bool KsnipCommandLine::isActiveWindowSet() const
{
    return mActiveWindowOption != nullptr && isSet(*mActiveWindowOption);
}

bool KsnipCommandLine::isWindowsUnderCursorSet() const
{
    return mWindowUnderCursorOption != nullptr && isSet(*mWindowUnderCursorOption);
}

bool KsnipCommandLine::isPortalSet() const
{
    return mPortalOption != nullptr && isSet(*mPortalOption);
}

bool KsnipCommandLine::isDelaySet() const
{
    return mDelayOption != nullptr && isSet(*mDelayOption);
}

bool KsnipCommandLine::isCursorSet() const
{
    return mCursorOption != nullptr && isSet(*mCursorOption);
}

bool KsnipCommandLine::isEditSet() const
{
    return (mEditOption != nullptr && isSet(*mEditOption)) || positionalArguments().count() == 1;
}

bool KsnipCommandLine::isSaveSet() const
{
    return mSaveOption != nullptr && isSet(*mSaveOption);
}

bool KsnipCommandLine::isVersionSet() const
{
    return mVersionOption != nullptr && isSet(*mVersionOption);
}

int KsnipCommandLine::delay() const
{
    auto valid = true;
    auto delay = value(*mDelayOption).toInt(&valid);
    return valid && delay >= 0 ? delay : -1;
}

QString KsnipCommandLine::imagePath() const
{
	return positionalArguments().count() == 1 ? positionalArguments().first() : value(*mEditOption);
}

bool KsnipCommandLine::isCaptureModeSet() const
{
    return isRectAreaSet() || isLastRectAreaSet() || isFullScreenSet() || isCurrentScreenSet() || isActiveWindowSet() || isWindowsUnderCursorSet();
}

CaptureModes KsnipCommandLine::captureMode() const
{
    if (isFullScreenSet()) {
        return CaptureModes::FullScreen;
    } else if (isCurrentScreenSet()) {
        return CaptureModes::CurrentScreen;
    } else if (isActiveWindowSet()) {
        return CaptureModes::ActiveWindow;
    } else if (isWindowsUnderCursorSet()) {
        return CaptureModes::WindowUnderCursor;
    } else if (isLastRectAreaSet()) {
	    return CaptureModes::LastRectArea;
    } else if (isPortalSet()) {
        return CaptureModes::Portal;
    } else {
        return CaptureModes::RectArea;
    }
}

void KsnipCommandLine::addPositionalArguments()
{
	addPositionalArgument(QLatin1Literal("image"), QLatin1Literal("Edit existing image in ksnip"), QLatin1Literal("[image]"));
}
