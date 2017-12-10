/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>
#include <QPainter>
#include <QTimer>

class MainWindow;
class SnippingArea;

class ImageGrabber : public QObject
{
    Q_OBJECT
public:
    enum CaptureMode {
        RectArea,
        FullScreen,
        CurrentScreen,
        ActiveWindow
    };

public:
    ImageGrabber(MainWindow *parent);
    ~ImageGrabber();
    void grabImage(CaptureMode captureMode, bool capureCursor = true, int delay = 0);
    QRect currectScreenRect() const;

signals:
    void finished(const QPixmap &) const;
    void canceled() const;

private:
    MainWindow   *mParent;
    SnippingArea *mSnippingArea;
    QRect         mCaptureRect;
    bool          mCaptureCursor;
    int           mCaptureDelay;
    const int     mMinCaptureDelay = 200;
    CaptureMode   mCaptureMode;

    void openSnippingArea();
    int getDelay() const;
    void setRectFromCorrectSource();
    QPixmap createPixmap(const QRect& rect) const;
    void initSnippingAreaIfRequired();

private slots:
    void grabRect();
};

#endif // IMAGEGRABBER_H
