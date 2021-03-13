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

#include "Action.h"

Action::Action() :
	mIsCaptureEnabled(false),
	mCaptureDelay(0),
	mCaptureMode(CaptureModes::RectArea),
	mIsPinImageEnabled(false),
	mIsUploadEnabled(false),
	mIsSaveEnabled(false),
	mIsCopyToClipboardEnabled(false),
	mIsOpenDirectoryEnabled(false),
	mIncludeCursor(false)
{

}

QString Action::Name() const
{
	return mName;
}

void Action::setName(const QString &name)
{
	mName = name;
}

bool Action::isCaptureEnabled() const
{
	return mIsCaptureEnabled;
}

void Action::setIsCaptureEnabled(bool enabled)
{
	mIsCaptureEnabled = enabled;
}

int Action::captureDelay() const
{
	return mCaptureDelay;
}

void Action::setCaptureDelay(int delayInMs)
{
	mCaptureDelay = delayInMs;
}

bool Action::includeCursor() const
{
	return mIncludeCursor;
}

void Action::setIncludeCursor(bool enabled)
{
	mIncludeCursor = enabled;
}

CaptureModes Action::captureMode() const
{
	return mCaptureMode;
}

void Action::setCaptureModel(CaptureModes mode)
{
	mCaptureMode = mode;
}

bool Action::isPinImageEnabled() const
{
	return mIsPinImageEnabled;
}

void Action::setIsPinScreenshotEnabled(bool enabled)
{
	mIsPinImageEnabled = enabled;
}

bool Action::isUploadEnabled() const
{
	return mIsUploadEnabled;
}

void Action::setIsUploadEnabled(bool enabled)
{
	mIsUploadEnabled = enabled;
}

bool Action::isSaveEnabled() const
{
	return mIsSaveEnabled;
}

void Action::setIsSaveEnabled(bool enabled)
{
	mIsSaveEnabled = enabled;
}

bool Action::isCopyToClipboardEnabled() const
{
	return mIsCopyToClipboardEnabled;
}

void Action::setIsCopyToClipboardEnabled(bool enabled)
{
	mIsCopyToClipboardEnabled = enabled;
}

bool Action::isOpenDirectoryEnabled() const
{
	return mIsOpenDirectoryEnabled;
}

void Action::setIsOpenDirectoryEnabled(bool enabled)
{
	mIsOpenDirectoryEnabled = enabled;
}
