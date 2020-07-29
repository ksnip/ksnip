/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_ABSTRACTSNIPPINGAREA_H
#define KSNIP_ABSTRACTSNIPPINGAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

#include "SnippingAreaAdorner.h"
#include "src/widgets/CursorFactory.h"
#include "src/common/helper/MathHelper.h"
#include "src/backend/config/KsnipConfigProvider.h"

class AbstractSnippingArea : public QWidget
{
    Q_OBJECT
public:
	explicit AbstractSnippingArea();
    ~AbstractSnippingArea() override;
    void showWithoutBackground();
    void showWithBackground(const QPixmap& background);
    virtual QRect selectedRectArea() const = 0;
	virtual QPixmap background() const;
    bool closeSnippingArea();

signals:
    void finished();
    void canceled();

protected:
    QRect mCaptureArea;
	QRegion mClippingRegion;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
	virtual bool isBackgroundTransparent() const;
    virtual void setFullScreen() = 0;
	virtual QPoint getMousePosition() const = 0;
	virtual QRect getSnippingAreaGeometry() const = 0;

private:
	QPoint mMouseDownPosition;
	bool mMouseIsDown;
    CursorFactory *mCursorFactory;
	KsnipConfig *mConfig;
	QPixmap *mBackground;
	SnippingAreaAdorner mAdorner;

    void setBackgroundImage(const QPixmap &background);
    void clearBackgroundImage();
    void init();
	void updateCapturedArea();
    virtual void showSnippingArea();
	void setMouseIsDown(bool isDown);
	void updateAdorner();
	void finishSelection();
};

#endif // KSNIP_ABSTRACTSNIPPINGAREA_H
