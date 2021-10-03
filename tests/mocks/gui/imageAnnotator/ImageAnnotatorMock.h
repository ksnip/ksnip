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

#ifndef KSNIP_IMAGEANNOTATORMOCK_H
#define KSNIP_IMAGEANNOTATORMOCK_H

#include <gmock/gmock.h>

#include "src/gui/imageAnnotator/IImageAnnotator.h"

class ImageAnnotatorMock : public IImageAnnotator
{
public:
	MOCK_METHOD(QImage, image, (), (const, override));
	MOCK_METHOD(QImage, imageAt, (int index), (const, override));
	MOCK_METHOD(QAction*, undoAction, (), (override));
	MOCK_METHOD(QAction*, redoAction, (), (override));
	MOCK_METHOD(QSize, sizeHint, (), (const, override));
	MOCK_METHOD(void, showAnnotator, (), (override));
	MOCK_METHOD(void, showCropper, (), (override));
	MOCK_METHOD(void, showScaler, (), (override));
	MOCK_METHOD(void, showCanvasModifier, (), (override));
	MOCK_METHOD(void, showRotator, (), (override));
	MOCK_METHOD(void, setSettingsCollapsed, (bool isCollapsed), (override));
	MOCK_METHOD(void, hide, (), (override));
	MOCK_METHOD(void, close, (), (override));
	MOCK_METHOD(bool, isVisible, (), (const, override));
	MOCK_METHOD(QWidget*, widget, (), (const, override));

	MOCK_METHOD(void, loadImage, (const QPixmap &pixmap), (override));
	MOCK_METHOD(int, addTab, (const QPixmap &pixmap, const QString &title, const QString &toolTip), (override));
	MOCK_METHOD(void, updateTabInfo, (int index, const QString &title, const QString &toolTip), (override));
	MOCK_METHOD(void, insertImageItem, (const QPointF &position, const QPixmap &pixmap), (override));
	MOCK_METHOD(void, setSmoothPathEnabled, (bool enabled), (override));
	MOCK_METHOD(void, setSaveToolSelection, (bool enabled), (override));
	MOCK_METHOD(void, setSmoothFactor, (int factor), (override));
	MOCK_METHOD(void, setSwitchToSelectToolAfterDrawingItem, (bool enabled), (override));
	MOCK_METHOD(void, setSelectItemAfterDrawing, (bool enabled), (override));
	MOCK_METHOD(void, setNumberToolSeedChangeUpdatesAllItems, (bool enabled), (override));
	MOCK_METHOD(void, setTabBarAutoHide, (bool enabled), (override));
	MOCK_METHOD(void, removeTab, (int index), (override));
	MOCK_METHOD(void, setStickers, (const QStringList &stickerPaths, bool keepDefault), (override));
	MOCK_METHOD(void, addTabContextMenuActions, (const QList<QAction*> & actions), (override));
	MOCK_METHOD(void, setCanvasColor, (const QColor &color), (override));
};

#endif //KSNIP_IMAGEANNOTATORMOCK_H
