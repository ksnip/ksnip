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

#ifndef KSNIP_ABSTRACTSNIPPINGAREAINFOTEXT_H
#define KSNIP_ABSTRACTSNIPPINGAREAINFOTEXT_H

#include <QPainter>

class AbstractSnippingAreaInfoText : public QObject
{
Q_OBJECT
public:
	explicit AbstractSnippingAreaInfoText(QObject *parent);
	~AbstractSnippingAreaInfoText() override;
	virtual void paint(QPainter *painter);
	virtual void handleMouseMove(const QPoint &pos);
	virtual void activate(const QRectF &snippingAreaGeometry);
	virtual void deactivate();

protected:
	virtual void updateInfoText() = 0;
	void setInfoText(const QStringList &infoTextLines);

private:
	QPen *mRectPen;
	QBrush *mRectBrush;
	QString mInfoText;
	QRect *mBaseInfoTextRect;
	QPoint mCurrentMousePos;
	bool mIsActive;
	QRectF mSnippingAreaGeometry;
};


#endif //KSNIP_ABSTRACTSNIPPINGAREAINFOTEXT_H
