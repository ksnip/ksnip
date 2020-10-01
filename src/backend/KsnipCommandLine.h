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

#ifndef KSNIP_KSNIPCOMMANDLINE_H
#define KSNIP_KSNIPCOMMANDLINE_H

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QCoreApplication>
#include <QHash>

#include "src/common/enum/CaptureModes.h"

class KsnipCommandLine : public QCommandLineParser
{
public:
    KsnipCommandLine(const QCoreApplication &app, const QList<CaptureModes> &captureModes);
    ~KsnipCommandLine();
    bool isRectAreaSet() const;
    bool isLastRectAreaSet() const;
    bool isFullScreenSet() const;
    bool isCurrentScreenSet() const;
    bool isActiveWindowSet() const;
    bool isWindowsUnderCursorSet() const;
    bool isPortalSet() const;
    bool isDelaySet() const;
    bool isCursorSet() const;
    bool isEditSet() const;
    bool isSaveSet() const;
    bool isVersionSet() const;
    bool isCaptureModeSet() const;
    int delay() const;
    QString imagePath() const;
    CaptureModes captureMode() const;

private:
    QCommandLineOption *mRectAreaOption = nullptr;
    QCommandLineOption *mLastRectAreaOption = nullptr;
    QCommandLineOption *mFullScreenOption = nullptr;
    QCommandLineOption *mCurrentScreenOption = nullptr;
    QCommandLineOption *mActiveWindowOption = nullptr;
    QCommandLineOption *mWindowUnderCursorOption = nullptr;
    QCommandLineOption *mPortalOption = nullptr;
    QCommandLineOption *mDelayOption = nullptr;
    QCommandLineOption *mCursorOption = nullptr;
    QCommandLineOption *mEditOption = nullptr;
    QCommandLineOption *mSaveOption = nullptr;
    QCommandLineOption *mVersionOption = nullptr;

    void addImageGrabberOptions(const QList<CaptureModes> &captureModes);
    void addDefaultOptions();
    void addVersionOptions();
    QString translateText(const QString &text);
    QCommandLineOption* addOption(const QString &shortName, const QString &longName, const QString &description);
    QCommandLineOption* addParameterOption(const QString &shortName, const QString &longName, const QString &description, const QString &parameter);
	void addPositionalArguments();
};

#endif //KSNIP_KSNIPCOMMANDLINE_H
