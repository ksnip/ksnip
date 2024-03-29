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

#ifndef KSNIP_SNIPPINGAREARESIZER_H
#define KSNIP_SNIPPINGAREARESIZER_H

#include <QPainter>
#include <QKeyEvent>
#include <QCursor>
#include <QVector>

#include "src/common/helper/RectHelper.h"
#include "src/backend/config/IConfig.h"

class SnippingAreaResizer : public QObject
{
Q_OBJECT
public:
	explicit SnippingAreaResizer(const QSharedPointer<IConfig> &config, QObject *parent);
	~SnippingAreaResizer() override = default;
	void activate(const QRectF &rect, const QPointF &pos);
	void deactivate();
	void paint(QPainter *painter);
	bool isActive() const;
	void handleMousePress(const QPointF &pos);
	void handleMouseRelease();
	void handleMouseMove(const QPointF &pos);
	void handleKeyPress(QKeyEvent *event);
	void handleKeyRelease(QKeyEvent *event);

signals:
	void rectChanged(const QRectF &rect);
	void cursorChanged(const QCursor &cursor);

private:
	QRectF mCurrentRect;
	bool mIsActive;
	QPointF mGrabOffset;
	bool mIsGrabbed;
	int mGrabbedHandleIndex;
	QVector<QRectF> mHandles;
	QSharedPointer<IConfig> mConfig;
	QColor mColor;
	bool mControlPressed;
	bool mAltPressed;

	void updateHandlePositions();
	void updateCurrentRect(const QPointF &point);
	void updateCursor(const QPointF &pos);
	void notifyRectChanged();
	void arrowUpPressed();
	void arrowDownPressed();
	void arrowLeftPressed();
	void arrowRightPressed();
	void arrowKeyPressed(const QKeyEvent *event);
};

#endif //KSNIP_SNIPPINGAREARESIZER_H
