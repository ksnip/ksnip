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

#ifndef KSNIP_SNIPPINGAREASELECTOR_H
#define KSNIP_SNIPPINGAREASELECTOR_H

#include <QPainter>
#include <QMouseEvent>

#include "SnippingAreaAdorner.h"
#include "src/backend/config/KsnipConfig.h"
#include "src/widgets/CursorFactory.h"

class SnippingAreaSelector : public QObject
{
	Q_OBJECT
public:
	explicit SnippingAreaSelector(KsnipConfig *config, QObject *parent);
	~SnippingAreaSelector() override;
	void activate(const QRectF &snippingAreaGeometry, const QPointF &pos);
	void deactivate();
	void paint(QPainter *painter);
	bool isActive() const;
	void handleMousePress(QMouseEvent *event);
	void handleMouseRelease(QMouseEvent *event);
	void handleMouseMove(QMouseEvent *event);
	void setBackgroundImage(const QPixmap *background);

signals:
	void rectChanged(const QRectF &rect);
	void cursorChanged(const QCursor &cursor);

private:
	QRectF mCurrentRect;
	bool mIsActive;
	KsnipConfig *mConfig;
	CursorFactory *mCursorFactory;
	SnippingAreaAdorner mAdorner;
	QPointF mMouseDownPos;
	bool mIsMouseDown;
	QRectF mSnippingAreaGeometry;
	QColor mAdornerColor;
	QColor mCursorColor;

	void setupAdorner();
	void setIsMouseDown(bool isMouseDown);
	void updateCurrentRect(const QRectF &rect, const QPointF &pos);
	void updateAdorner(const QPointF &pos);
};


#endif //KSNIP_SNIPPINGAREASELECTOR_H
