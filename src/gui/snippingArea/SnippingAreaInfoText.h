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

#ifndef KSNIP_SNIPPINGAREAINFOTEXT_H
#define KSNIP_SNIPPINGAREAINFOTEXT_H

#include <QFontMetricsF>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPainter>

class SnippingAreaInfoText : public QObject
{
Q_OBJECT
public:
	explicit SnippingAreaInfoText(QObject *parent);
	~SnippingAreaInfoText() override;
	void paint(QPainter *painter);
	void handleMouseMove(const QPoint &pos);
	void activate(const QRectF &snippingAreaGeometry, bool isResizingDefault);
	void deactivate();

private:
	QPen *mRectPen;
	QBrush *mRectBrush;
	QString mInfoText;
	QRect *mBaseInfoTextRect;
	QPoint mCurrentMousePos;
	bool mIsActive;
	bool mIsResizingDefault;
	QRectF mSnippingAreaGeometry;

	void updateInfoText();
};


#endif //KSNIP_SNIPPINGAREAINFOTEXT_H
