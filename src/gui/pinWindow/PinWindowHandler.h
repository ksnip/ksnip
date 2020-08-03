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

#ifndef KSNIP_PINWINDOWHANDLER_H
#define KSNIP_PINWINDOWHANDLER_H

#include <QObject>
#include <QSharedPointer>
#include <QList>

#include "PinWindow.h"

class PinWindowHandler : public QObject
{
Q_OBJECT
public:
	explicit PinWindowHandler(QWidget *parent);
	~PinWindowHandler() override;
	void add(const QPixmap &pixmap);

public slots:
	void closeRequested();
	void closeAllRequested();
	void closeOtherRequested();

private:
	QWidget *mParent;
	QList<QSharedPointer<PinWindow>> mPinWindows;
	QSharedPointer<PinWindow> CreatePinWindow(const QPixmap &pixmap) const;
};

#endif //KSNIP_PINWINDOWHANDLER_H
