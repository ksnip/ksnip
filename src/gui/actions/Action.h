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

#ifndef KSNIP_ACTION_H
#define KSNIP_ACTION_H

#include <QString>
#include <QKeySequence>

#include "src/common/enum/CaptureModes.h"

class Action
{
public:
	Action();
	~Action() = default;

	QString name() const;
	void setName(const QString &name);

	QKeySequence shortcut() const;
	void setShortcut(const QKeySequence &keySequence);

	bool isCaptureEnabled() const;
	void setIsCaptureEnabled(bool enabled);

	int captureDelay() const;
	void setCaptureDelay(int delayInMs);

	bool isPinImageEnabled() const;
	void setIsPinScreenshotEnabled(bool enabled);

	CaptureModes captureMode() const;
	void setCaptureMode(CaptureModes mode);

	bool includeCursor() const;
	void setIncludeCursor(bool enabled);

	bool isUploadEnabled() const;
	void setIsUploadEnabled(bool enabled);

	bool isSaveEnabled() const;
	void setIsSaveEnabled(bool enabled);

	bool isCopyToClipboardEnabled() const;
	void setIsCopyToClipboardEnabled(bool enabled);

	bool isOpenDirectoryEnabled() const;
	void setIsOpenDirectoryEnabled(bool enabled);

	bool isHideMainWindowEnabled() const;
	void setIsHideMainWindowEnabled(bool enabled);

	friend bool operator==(const Action& left, const Action& right);

private:
	QString mName;
	bool mIsCaptureEnabled;
	int mCaptureDelay;
	bool mIncludeCursor;
	CaptureModes mCaptureMode;
	bool mIsPinImageEnabled;
	bool mIsUploadEnabled;
	bool mIsSaveEnabled;
	bool mIsCopyToClipboardEnabled;
	bool mIsOpenDirectoryEnabled;
	bool mIsHideMainWindowEnabled;
	QKeySequence mShortcut;
};

bool operator==(const Action& left, const Action& right);

#endif //KSNIP_ACTION_H
