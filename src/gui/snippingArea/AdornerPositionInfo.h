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

#ifndef KSNIP_ADORNERPOSITIONINFO_H
#define KSNIP_ADORNERPOSITIONINFO_H

#include <QPainter>

class AdornerPositionInfo
{
public:
	explicit AdornerPositionInfo();
	~AdornerPositionInfo();
	void update(const QPoint &mousePosition);
	void draw(QPainter &painter);

private:
	QFont mFont;
	QFontMetrics *mFontMetric;
	QPen *mPen;
	QRect mBox;
	QRect mTextRect;
	QString mText;
};

#endif //KSNIP_ADORNERPOSITIONINFO_H
