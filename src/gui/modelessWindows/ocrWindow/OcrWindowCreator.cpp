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

#include "OcrWindowCreator.h"

OcrWindowCreator::OcrWindowCreator(const QSharedPointer<IPluginManager> &pluginManager) :
		mPluginManager(pluginManager)
{

}

QSharedPointer<IModelessWindow> OcrWindowCreator::create(const QPixmap &pixmap, int windowId) const
{
	QString text = getText(pixmap);
	auto title = tr("OCR Window %1").arg(windowId);
	return QSharedPointer<OcrWindow>(new OcrWindow(text, title), &QObject::deleteLater);
}

QString OcrWindowCreator::getText(const QPixmap &pixmap) const 
{
	auto ocrPlugin = mPluginManager->get(PluginType::Ocr).objectCast<IPluginOcr>();

#if defined(_WIN32)
	auto path = mPluginManager->getPath(PluginType::Ocr);
	auto parentDir = QFileInfo(path).path();
	return ocrPlugin->recognize(pixmap, parentDir.append("\\tessdata\\"));
#else
	return ocrPlugin->recognize(pixmap);
#endif
}
