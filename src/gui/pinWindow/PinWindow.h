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

#ifndef KSNIP_PINWINDOW_H
#define KSNIP_PINWINDOW_H

#include <QDialog>
#include <QImage>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QContextMenuEvent>
#include <QWheelEvent>

class PinWindow : public QDialog
{
Q_OBJECT
public:
	explicit PinWindow(const QPixmap &pixmap, const QString &title);
	~PinWindow() override;

signals:
	void closeRequest();
	void closeOtherRequest();
	void closeAllRequest();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void contextMenuEvent(QContextMenuEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	QLabel *mCentralWidget;
	QVBoxLayout *mLayout;
	QGraphicsDropShadowEffect *mDropShadowEffect;
	int mMargin;
	int mMinSize;
	QPixmap mImage;
	QPoint mMoveOffset;
	bool mIsMoving{};

	void addDropShadow();
};

#endif //KSNIP_PINWINDOW_H
