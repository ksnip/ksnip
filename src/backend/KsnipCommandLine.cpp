/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "KsnipCommandLine.h"

KsnipCommandLine::KsnipCommandLine(const QCoreApplication &app, const QList<CaptureModes> &captureModes)
{
    setApplicationDescription(translateText(QStringLiteral("Ksnip Screenshot Tool")));
    addHelpOption();
    addVersionOptions();
    addImageGrabberOptions(captureModes);
    addDefaultOptions();
    process(app);
}

KsnipCommandLine::~KsnipCommandLine()
{
    delete mRectAreaOption;
    delete mFullScreenOption;
    delete mCurrentScreenOption;
    delete mActiveWindowOption;
    delete mWindowUnderCursorOption;
    delete mDelayOption;
    delete mCursorOption;
    delete mEditOption;
    delete mSaveOption;
    delete mVersionOption;
}

void KsnipCommandLine::addImageGrabberOptions(const QList<CaptureModes> &captureModes)
{
    if (captureModes.contains(CaptureModes::RectArea)) {
        mRectAreaOption = addOption(QStringLiteral("r"), QStringLiteral("rectarea"), QStringLiteral("Select a rectangular area from where to take a screenshot."));
    }
    if (captureModes.contains(CaptureModes::FullScreen)) {
        mFullScreenOption = addOption(QStringLiteral("f"), QStringLiteral("fullscreen"), QStringLiteral("\"Capture the fullscreen including all monitors."));
    }
    if (captureModes.contains(CaptureModes::CurrentScreen)) {
        mCurrentScreenOption = addOption(QStringLiteral("m"), QStringLiteral("current"), QStringLiteral("Capture the screen (monitor) where the mouse cursor is currently located."));
    }
    if (captureModes.contains(CaptureModes::ActiveWindow)) {
        mActiveWindowOption = addOption(QStringLiteral("a"), QStringLiteral("active"), QStringLiteral("Capture the window that currently has input focus."));
    }
    if (captureModes.contains(CaptureModes::WindowUnderCursor)) {
        mWindowUnderCursorOption = addOption(QStringLiteral("u"), QStringLiteral("windowundercursor"), QStringLiteral("Capture the window that is currently under the mouse cursor."));
    }
}

void KsnipCommandLine::addDefaultOptions()
{
    mDelayOption = addParameterOption(QStringLiteral("d"), QStringLiteral("delay"), QStringLiteral("Delay before taking the screenshot."), QStringLiteral("seconds"));
    mCursorOption = addOption(QStringLiteral("c"), QStringLiteral("cursor"), QStringLiteral("Capture mouse cursor on screenshot."));
    mEditOption = addParameterOption(QStringLiteral("e"), QStringLiteral("edit"), QStringLiteral("Edit existing image in ksnip"), QStringLiteral("image"));
    mSaveOption = addOption(QStringLiteral("s"), QStringLiteral("save"), QStringLiteral("Save screenshot to default location without opening in editor."));
}

void KsnipCommandLine::addVersionOptions()
{
    mVersionOption = addOption(QStringLiteral("v"), QStringLiteral("version"), QStringLiteral("Displays version information."));
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
    return mEditOption != nullptr && isSet(*mEditOption);
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
    if (!valid || delay < 0) {
        return -1;
    } else {
        return delay;
    }
}

QString KsnipCommandLine::image() const
{
    return value(*mEditOption);
}

bool KsnipCommandLine::isCaptureModeSet() const
{
    return isRectAreaSet() || isFullScreenSet() || isCurrentScreenSet() || isActiveWindowSet() || isWindowsUnderCursorSet();
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
    } else {
        return CaptureModes::RectArea;
    }
}
