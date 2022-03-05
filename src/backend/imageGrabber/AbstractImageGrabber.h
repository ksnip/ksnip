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

#ifndef KSNIP_ABSTRACTIMAGEGRABBER_H
#define KSNIP_ABSTRACTIMAGEGRABBER_H

#include <QObject>
#include <QTimer>

#include "IImageGrabber.h"
#include "src/common/handler/DelayHandler.h"
#include "src/backend/config/IConfig.h"

class AbstractImageGrabber : public IImageGrabber
{
Q_OBJECT
public:
    explicit AbstractImageGrabber(const QSharedPointer<IConfig> &config);
    ~AbstractImageGrabber() override = default;
    bool isCaptureModeSupported(CaptureModes captureMode) const override;
    QList<CaptureModes> supportedCaptureModes() const override;
    void grabImage(CaptureModes captureMode, bool captureCursor, int delay) override;

protected:
    QSharedPointer<IConfig> mConfig;

    void addSupportedCaptureMode(CaptureModes captureMode);
    void setCaptureDelay(int delay);
    int captureDelay() const;
    void setCaptureMode(CaptureModes captureMode);
    CaptureModes captureMode() const;
    bool isCaptureDelayBelowMin() const;
    bool isCaptureCursorEnabled() const;
    void setIsCaptureCursorEnabled(bool enabled);

protected slots:
    virtual void grab() = 0;

private:
    QList<CaptureModes> mSupportedCaptureModes;
    int mCaptureDelay;
    CaptureModes mCaptureMode;
    bool mIsCaptureCursorEnabled;
	int mImplicitCaptureDelay;

private slots:
	void delayChanged();
};

#endif //KSNIP_ABSTRACTIMAGEGRABBER_H
