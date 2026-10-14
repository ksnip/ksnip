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

#ifndef KSNIP_MACKEYHANDLER_H
#define KSNIP_MACKEYHANDLER_H

#include "IKeyHandler.h"
#include "src/gui/globalHotKeys/KeySequenceToMacKeyCodeTranslator.h"

class MacKeyHandler : public IKeyHandler
{
public:
	MacKeyHandler() = default;
	~MacKeyHandler() override;

	bool registerKey(const QKeySequence &keySequence) override;
	bool isKeyPressed(void* message) override;
	void setPressedCallback(std::function<void()> callback) override;

	// Called by the macOS hot key event handler when the registered key is pressed
	void notifyKeyPressed() const;

private:
	static quint32 mNextId;

	KeySequenceToMacKeyCodeTranslator mKeyCodeMapper;
	std::function<void()> mPressedCallback;
	void *mHotKeyRef = nullptr; // EventHotKeyRef, kept opaque to not expose Carbon in this header
	quint32 mId = 0;

	void unregisterKey();
};

#endif //KSNIP_MACKEYHANDLER_H
