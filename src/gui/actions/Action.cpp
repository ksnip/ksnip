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
	mIncludeCursor(false),
	mIsHideMainWindowEnabled(false),
	mIsGlobalShortcut(false)
{

}

QString Action::name() const
{
	return mName;
}

void Action::setName(const QString &name)
{
	mName = name;
}

QKeySequence Action::shortcut() const
{
	return mShortcut;
}

void Action::setShortcut(const QKeySequence &keySequence)
{
	mShortcut = keySequence;
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

void Action::setCaptureMode(CaptureModes mode)
{
	mCaptureMode = mode;
}

bool Action::isPinImageEnabled() const
{
	return mIsPinImageEnabled;
}

void Action::setIsPinImageEnabled(bool enabled)
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

bool Action::isHideMainWindowEnabled() const
{
	return mIsHideMainWindowEnabled;
}

void Action::setIsHideMainWindowEnabled(bool enabled)
{
	mIsHideMainWindowEnabled = enabled;
}

bool Action::isGlobalShortcut() const
{
	return mIsGlobalShortcut;
}

void Action::setIsGlobalShortcut(bool isGlobal)
{
	mIsGlobalShortcut = isGlobal;
}

bool operator==(const Action &left, const Action &right)
{
	return left.name() == right.name()
		   && left.shortcut() == right.shortcut()
		   && left.isGlobalShortcut() == right.isGlobalShortcut()
		   && left.isCaptureEnabled() == right.isCaptureEnabled()
		   && left.includeCursor() == right.includeCursor()
		   && left.captureDelay() == right.captureDelay()
		   && left.captureMode() == right.captureMode()
		   && left.isSaveEnabled() == right.isSaveEnabled()
		   && left.isCopyToClipboardEnabled() == right.isCopyToClipboardEnabled()
		   && left.isPinImageEnabled() == right.isPinImageEnabled()
		   && left.isOpenDirectoryEnabled() == right.isOpenDirectoryEnabled()
		   && left.isUploadEnabled() == right.isUploadEnabled()
		   && left.isHideMainWindowEnabled() == right.isHideMainWindowEnabled();
}
