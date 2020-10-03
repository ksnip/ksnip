/*
 * Copyright (C) 2017 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_ABSTRACTRECTAREAIMAGEGRABBER_H
#define KSNIP_ABSTRACTRECTAREAIMAGEGRABBER_H

#include <QPainter>
#include <QScreen>

#include "AbstractImageGrabber.h"
#include "src/gui/snippingArea/AbstractSnippingArea.h"

class AbstractRectAreaImageGrabber : public AbstractImageGrabber
{
    Q_OBJECT
public:
    explicit AbstractRectAreaImageGrabber(AbstractSnippingArea *snippingArea);
    ~AbstractRectAreaImageGrabber() override;
    void grabImage(CaptureModes captureMode, bool captureCursor, int delay) override;
	virtual QRect currentScreenRect() const;
	virtual QRect fullScreenRect() const = 0;
	virtual QRect activeWindowRect() const = 0;
	virtual QRect lastRectArea() const;

protected:
	QRect mCaptureRect;
	CursorDto mStoredCursorImageWithPosition;

	void openSnippingAreaWithoutBackground();
    void openSnippingAreaWithBackground(const QPixmap &background);
    QRect selectedSnippingAreaRect() const;
	QPixmap snippingAreaBackground() const;
	QPixmap getScreenshotFromRect(const QRect &rect) const;
	QPixmap getScreenshot() const;
	void setCaptureRectFromCorrectSource();
	virtual bool isSnippingAreaBackgroundTransparent() const;
	virtual CursorDto getCursorWithPosition() const = 0;

protected slots:
	void prepareGrab();
	void grab() override;

private:
    AbstractSnippingArea* mSnippingArea;
	bool mFreezeImageWhileSnipping;

	void openSnippingArea();
	void connectSnippingAreaCancel();
	void connectSnippingAreaFinish();
	void disconnectSnippingAreaFinish();
	bool shouldCaptureCursor() const;
	CursorDto getCursorImageWithPositionFromCorrectSource() const;
	bool isRectAreaCaptureWithBackground() const;
	bool isRectAreaCaptureWithoutBackground() const;
	CursorDto getCursorRelativeToScreenshot() const;
};

#endif // KSNIP_ABSTRACTRECTAREAIMAGEGRABBER_H
