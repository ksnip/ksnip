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

#ifndef KSNIP_OCRWINDOWCREATOR_H
#define KSNIP_OCRWINDOWCREATOR_H

#include "OcrWindow.h"
#include "IOcrWindowCreator.h"
#include "src/plugins/IPluginManager.h"
#include "src/plugins/interfaces/IPluginOcr.h"

class OcrWindowCreator : public IOcrWindowCreator, public QObject
{
public:
	explicit OcrWindowCreator(const QSharedPointer<IPluginManager> &pluginManager);
	~OcrWindowCreator() override = default;
	QSharedPointer<IModelessWindow> create(const QPixmap &pixmap, int windowId) const override;

private:
	QSharedPointer<IPluginManager> mPluginManager;
};

#endif //KSNIP_OCRWINDOWCREATOR_H
