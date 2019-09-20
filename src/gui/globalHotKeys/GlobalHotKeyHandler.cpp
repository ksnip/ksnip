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

#include "GlobalHotKeyHandler.h"

GlobalHotKeyHandler::GlobalHotKeyHandler()
{
	mConfig = KsnipConfig::instance();

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
		auto hotKey = QSharedPointer<GlobalHotKey>(new GlobalHotKey(QApplication::instance(), QKeySequence(Qt::ALT + Qt::CTRL + Qt::Key_B)));
		connect(hotKey.data(), &GlobalHotKey::pressed, this, &GlobalHotKeyHandler::newCaptureTriggered);
		mGlobalHotKeys.append(hotKey);
	}
}
