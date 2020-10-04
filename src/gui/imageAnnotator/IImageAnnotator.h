/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_IIMAGEANNOTATOR_H
#define KSNIP_IIMAGEANNOTATOR_H

#include <QObject>

class QAction;

class IImageAnnotator : public QObject
{
Q_OBJECT
public:
	explicit IImageAnnotator() = default;
	~IImageAnnotator() override = default;
	virtual QImage image() const = 0;
	virtual QImage imageAt(int index) const = 0;
	virtual QAction *undoAction() = 0;
	virtual QAction *redoAction() = 0;
	virtual QSize sizeHint() const = 0;
	virtual void showAnnotator() = 0;
	virtual void showCropper() = 0;
	virtual void showScaler() = 0;
	virtual void hide() = 0;
	virtual void close() = 0;
	virtual bool isVisible() const = 0;
	virtual QWidget* widget() const = 0;


public slots:
	virtual void loadImage(const QPixmap &pixmap) = 0;
	virtual int addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip) = 0;
	virtual void updateTabInfo(int index, const QString &title, const QString &toolTip) = 0;
	virtual void insertImageItem(const QPointF &position, const QPixmap &pixmap) = 0;
	virtual void setTextFont(const QFont &font) = 0;
	virtual void setNumberFont(const QFont &font) = 0;
	virtual void setItemShadowEnabled(bool enabled) = 0;
	virtual void setSmoothPathEnabled(bool enabled) = 0;
	virtual void setSaveToolSelection(bool enabled) = 0;
	virtual void setSmoothFactor(int factor) = 0;
	virtual void setTabBarAutoHide(bool enabled) = 0;
	virtual void removeTab(int index) = 0;
	virtual void setStickers(const QStringList &stickerPaths, bool keepDefault) = 0;
	virtual void addTabContextMenuActions(const QList<QAction*> & actions) = 0;

signals:
	void imageChanged() const;
	void currentTabChanged(int index) const;
	void tabCloseRequested(int index) const;
	void tabMoved(int fromIndex, int toIndex);
	void tabContextMenuOpened(int index) const;
};


#endif //KSNIP_IIMAGEANNOTATOR_H
