/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_ABSTRACTIMAGEGRABBER_H
#define KSNIP_ABSTRACTIMAGEGRABBER_H

#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QScreen>

#include "CaptureDto.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/handler/DelayHandler.h"
#include "gui/snippingArea/AbstractSnippingArea.h"

class AbstractImageGrabber : public QObject
{
    Q_OBJECT
public:
    explicit AbstractImageGrabber(AbstractSnippingArea *snippingArea);
    ~AbstractImageGrabber() override;
	bool isCaptureModeSupported(CaptureModes captureMode) const;
	QList<CaptureModes> supportedCaptureModes() const;
	virtual void grabImage(CaptureModes captureMode, bool captureCursor, int delay, bool freezeImageWhileSnipping);
	virtual QRect currentScreenRect() const;
	virtual QRect fullScreenRect() const = 0;
	virtual QRect activeWindowRect() const = 0;

signals:
    void finished(const CaptureDto &capture) const;
    void canceled() const;

protected:
	QRect mCaptureRect;
	bool mCaptureCursor;
	int mCaptureDelay;
	CaptureModes mCaptureMode;
	CursorDto mStoredCursorImageWithPosition;
	DelayHandler mDelayHandler;

	void addSupportedCaptureMode(CaptureModes captureMode);
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
	virtual void prepareGrab();
	virtual void grab();

private:
    AbstractSnippingArea *mSnippingArea;
	bool mFreezeImageWhileSnipping;
	QList<CaptureModes> mSupportedCaptureModes;

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

#endif // KSNIP_ABSTRACTIMAGEGRABBER_H
