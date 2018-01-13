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

#ifndef ABSTRACTIMAGEGRABBER_H
#define ABSTRACTIMAGEGRABBER_H

#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QScreen>

#include "CaptureModes.h"
#include "src/gui/SnippingArea.h"

class AbstractImageGrabber : public QObject
{
    Q_OBJECT
public:
    AbstractImageGrabber(QObject *parent = nullptr);
    virtual ~AbstractImageGrabber();
    virtual void grabImage(CaptureModes captureMode, bool capureCursor = true, int delay = 0) = 0;
    QRect currectScreenRect() const;

signals:
    void finished(const QPixmap &) const;
    void canceled() const;

protected:
    QRect        mCaptureRect;
    bool         mCaptureCursor;
    int          mCaptureDelay;
    CaptureModes mCaptureMode;

    void openSnippingArea();
    void openSnippingAreaWithBackground(const QPixmap &background);
    QRect selectedSnippingAreaRect() const;

protected slots:
    virtual void grabRect() = 0;

private:
    SnippingArea *mSnippingArea;

    void initSnippingAreaIfRequired();
};

#endif // ABSTRACTIMAGEGRABBER_H
