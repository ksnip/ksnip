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

#include "GlobalHotKeyHandler.h"

GlobalHotKeyHandler::GlobalHotKeyHandler(const QList<CaptureModes> &supportedCaptureModes)
{
	mSupportedCaptureModes = supportedCaptureModes;
	mConfig = KsnipConfigProvider::instance();

	connect(mConfig, &KsnipConfig::hotKeysChanged, this, &GlobalHotKeyHandler::setupHotKeys);

	setupHotKeys();
}

GlobalHotKeyHandler::~GlobalHotKeyHandler()
{
	removeHotKeys();
}

void GlobalHotKeyHandler::removeHotKeys()
{
	mGlobalHotKeys.clear();
}

void GlobalHotKeyHandler::setupHotKeys()
{
	removeHotKeys();
	if(mConfig->globalHotKeysEnabled()) {
		createHotKey(mConfig->rectAreaHotKey(), CaptureModes::RectArea);
		createHotKey(mConfig->lastRectAreaHotKey(), CaptureModes::LastRectArea);
		createHotKey(mConfig->fullScreenHotKey(), CaptureModes::FullScreen);
		createHotKey(mConfig->currentScreenHotKey(), CaptureModes::CurrentScreen);
		createHotKey(mConfig->activeWindowHotKey(), CaptureModes::ActiveWindow);
		createHotKey(mConfig->windowUnderCursorHotKey(), CaptureModes::WindowUnderCursor);
        createHotKey(mConfig->windowUnderCursorHotKey(), CaptureModes::Portal);
	}
}

void GlobalHotKeyHandler::createHotKey(const QKeySequence &keySequence, CaptureModes captureMode)
{
	if(mSupportedCaptureModes.contains(captureMode) && !keySequence.isEmpty()) {
		auto hotKey = QSharedPointer<GlobalHotKey>(new GlobalHotKey(QApplication::instance(), keySequence));
		connect(hotKey.data(), &GlobalHotKey::pressed, [this, captureMode](){ emit newCaptureTriggered(captureMode); });
		mGlobalHotKeys.append(hotKey);
	}
}

void GlobalHotKeyHandler::setEnabled(bool enabled)
{
	if(enabled) {
		setupHotKeys();
	} else {
		removeHotKeys();
	}
}
