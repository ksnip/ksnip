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

#ifndef KSNIPCONFIG_H
#define KSNIPCONFIG_H

#include <QObject>
#include <QPoint>
#include <QSettings>

#include "src/widgets/PaintArea.h"
#include "ImageGrabber.h"

class KsnipConfig : public QObject
{
    Q_OBJECT

public:
    KsnipConfig ( QObject *parent = 0 );

    static KsnipConfig *instance();

    bool saveKsnipPosition() const;
    void setSaveKsnipPosition ( bool enabled );

    bool promptSaveBeforeExit() const;
    void setPromptSaveBeforeExit ( bool enabled );

    bool alwaysCopyToClipboard() const;
    void setAlwaysCopyToClipboard ( bool enabled );

    bool saveKsnipToolSelection() const;
    void setSaveKsnipToolSelection ( bool enabled );

    QPoint windowPosition() const;
    void setWindowPosition ( QPoint position );

    PaintArea::PaintMode paintMode() const;
    void setPaintMode ( PaintArea::PaintMode paintMode );

    ImageGrabber::CaptureMode captureMode() const;
    void setCaptureMode ( ImageGrabber::CaptureMode captureMode );

    QPen pen() const;

    QColor penColor() const;
    void setPenColor ( QColor color );

    int penSize() const;
    void setPenSize ( int size );

    QPen marker() const;

    QColor markerColor() const;
    void setMarkerColor ( QColor color );

    int markerSize() const;
    void setMarkerSize ( int size );

    int captureDelay() const;
    void setCaptureDelay ( int delay );

signals:
    void painterUpdated();
    void captureDelayUpdated(int delay);

private:
    QSettings mConfig;
};

#endif // KSNIPCONFIG_H
