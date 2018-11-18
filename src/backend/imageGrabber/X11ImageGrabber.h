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

#ifndef X11IMAGEGRABBER_H
#define X11IMAGEGRABBER_H

#include "AbstractImageGrabber.h"
#include "X11Wrapper.h"
#include "src/gui/X11SnippingArea.h"

class X11ImageGrabber : public AbstractImageGrabber
{
public:
    explicit X11ImageGrabber();
    virtual ~X11ImageGrabber();
    virtual void grabImage(CaptureModes captureMode, bool captureCursor = true, int delay = 0) override;

protected:
    virtual void grab() override;

private:
    X11Wrapper *mX11Wrapper;

    void getRectArea();
    void setRectFromCorrectSource();
    QPixmap createPixmap(const QRect &rect) const;
};

#endif // X11IMAGEGRABBER_H
