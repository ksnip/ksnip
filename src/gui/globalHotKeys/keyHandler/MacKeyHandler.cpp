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

#include "MacKeyHandler.h"

#include <QHash>
#include <QDebug>

#include <Carbon/Carbon.h>

namespace {

const OSType HotKeySignature = 0x6B736E70; // 'ksnp'

QHash<quint32, MacKeyHandler *> &registeredHandlers()
{
	static QHash<quint32, MacKeyHandler *> handlers;
	return handlers;
}

OSStatus hotKeyPressed(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
	Q_UNUSED(nextHandler)
	Q_UNUSED(userData)

	EventHotKeyID hotKeyId;
	auto status = GetEventParameter(event, kEventParamDirectObject, typeEventHotKeyID, nullptr, sizeof(hotKeyId), nullptr, &hotKeyId);
	if (status != noErr || hotKeyId.signature != HotKeySignature) {
		return eventNotHandledErr;
	}

	auto handler = registeredHandlers().value(hotKeyId.id, nullptr);
	if (handler == nullptr) {
		return eventNotHandledErr;
	}

	handler->notifyKeyPressed();
	return noErr;
}

void installEventHandlerOnce()
{
	static bool isInstalled = false;
	if (isInstalled) {
		return;
	}

	EventTypeSpec eventType;
	eventType.eventClass = kEventClassKeyboard;
	eventType.eventKind = kEventHotKeyPressed;
	isInstalled = InstallApplicationEventHandler(&hotKeyPressed, 1, &eventType, nullptr, nullptr) == noErr;
}

} // namespace

quint32 MacKeyHandler::mNextId = 1;

MacKeyHandler::~MacKeyHandler()
{
	unregisterKey();
}

bool MacKeyHandler::registerKey(const QKeySequence &keySequence)
{
	unregisterKey();

	if (keySequence.count() != 1) {
		return false;
	}

	auto keyCodeCombo = mKeyCodeMapper.map(keySequence);
	if (keyCodeCombo.key == KeySequenceToMacKeyCodeTranslator::InvalidKey) {
		qWarning("Unable to register global hot key %s, key is not supported on macOS.", qPrintable(keySequence.toString()));
		return false;
	}

	installEventHandlerOnce();

	EventHotKeyID hotKeyId;
	hotKeyId.signature = HotKeySignature;
	hotKeyId.id = mNextId;

	EventHotKeyRef hotKeyRef = nullptr;
	auto status = RegisterEventHotKey(keyCodeCombo.key, keyCodeCombo.modifier, hotKeyId, GetApplicationEventTarget(), 0, &hotKeyRef);
	if (status != noErr) {
		qWarning("Unable to register global hot key %s, error %d.", qPrintable(keySequence.toString()), static_cast<int>(status));
		return false;
	}

	mId = mNextId++;
	mHotKeyRef = hotKeyRef;
	registeredHandlers().insert(mId, this);
	return true;
}

bool MacKeyHandler::isKeyPressed(void *message)
{
	// Hot keys on macOS are delivered through a Carbon event handler and not
	// as native Qt events, see setPressedCallback and notifyKeyPressed.
	Q_UNUSED(message)
	return false;
}

void MacKeyHandler::setPressedCallback(std::function<void()> callback)
{
	mPressedCallback = std::move(callback);
}

void MacKeyHandler::notifyKeyPressed() const
{
	if (mPressedCallback) {
		mPressedCallback();
	}
}

void MacKeyHandler::unregisterKey()
{
	if (mHotKeyRef == nullptr) {
		return;
	}

	UnregisterEventHotKey(static_cast<EventHotKeyRef>(mHotKeyRef));
	registeredHandlers().remove(mId);
	mHotKeyRef = nullptr;
}
