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

#include "src/common/dtos/CaptureDto.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/handler/DelayHandler.h"
#include "src/backend/config/KsnipConfigProvider.h"

class AbstractImageGrabber : public QObject
{
Q_OBJECT
public:
    explicit AbstractImageGrabber();
    ~AbstractImageGrabber() override = default;
    bool isCaptureModeSupported(CaptureModes captureMode) const;
    QList<CaptureModes> supportedCaptureModes() const;
    virtual void grabImage(CaptureModes captureMode, bool captureCursor, int delay);

signals:
    void finished(const CaptureDto &capture) const;
    void canceled() const;

protected:
    KsnipConfig* mConfig;

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
    DelayHandler mDelayHandler;
};


#endif //KSNIP_ABSTRACTIMAGEGRABBER_H
