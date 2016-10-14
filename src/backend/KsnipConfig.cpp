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

#include "KsnipConfig.h"

KsnipConfig::KsnipConfig( QObject *parent ) : QObject( parent )
{

}

//
// Public Functions
//

KsnipConfig *KsnipConfig::instance()
{
    static KsnipConfig instance;
    return &instance;
}

bool KsnipConfig::saveKsnipPosition() const
{
    return mConfig.value( "Application/SaveKsnipPosition", true ).toBool();
}

void KsnipConfig::setSaveKsnipPosition( bool enabled )
{
    mConfig.setValue( "Application/SaveKsnipPosition", enabled );
    mConfig.sync();
}

bool KsnipConfig::promptSaveBeforeExit() const
{
    return mConfig.value( "Application/PromptSaveBeforeExit", false ).toBool();
}

void KsnipConfig::setPromptSaveBeforeExit( bool enabled )
{
    mConfig.setValue( "Application/PromptSaveBeforeExit", enabled );
    mConfig.sync();
}

bool KsnipConfig::alwaysCopyToClipboard() const
{
    return mConfig.value( "Application/AlwaysCopyToClipboard", false ).toBool();
}

void KsnipConfig::setAlwaysCopyToClipboard( bool enabled )
{
    mConfig.setValue( "Application/AlwaysCopyToClipboard", enabled );
    mConfig.sync();
}

bool KsnipConfig::saveKsnipToolSelection() const
{
    return mConfig.value( "Application/SaveKsnipToolsSelection", true ).toBool();
}

void KsnipConfig::setSaveKsnipToolSelection( bool enabled )
{
    mConfig.setValue( "Application/SaveKsnipToolsSelection", enabled );
    mConfig.sync();
}

QPoint KsnipConfig::windowPosition() const
{
    // If we are not saving the position we return the default and ignore what has been save earlier
    if ( !saveKsnipPosition() ) {
        return QPoint( 200, 200 );
    }

    return mConfig.value( "MainWindow/Position", QPoint( 200, 200 ) ).value<QPoint>();
}

void KsnipConfig::setWindowPosition( QPoint position )
{
    mConfig.setValue( "MainWindow/Position", position );
    mConfig.sync();
}

PaintArea::PaintMode KsnipConfig::paintMode() const
{
    // If we are not storing the tool selection, always return the pen as default
    if ( !saveKsnipToolSelection() ) {
        return PaintArea::Pen;
    }

    if ( mConfig.value( "Painter/PaintMode" ).toInt() == PaintArea::Marker ) {
        return PaintArea::Marker;
    }
    else {
        return PaintArea::Pen;
    }
}

void KsnipConfig::setPaintMode( PaintArea::PaintMode paintMode )
{
    mConfig.setValue( "Painter/PaintMode", paintMode );
    mConfig.sync();
}

ImageGrabber::CaptureMode KsnipConfig::captureMode() const
{
    // If we are not storing the tool selection, always return the rect area as default
    if ( !saveKsnipToolSelection() ) {
        return ImageGrabber::RectArea;
    }

    switch ( mConfig.value( "ImageGrabber/CaptureMode" ).toInt() ) {
    case ImageGrabber::ActiveWindow:
        return ImageGrabber::ActiveWindow;

    case ImageGrabber::CurrentScreen:
        return ImageGrabber::CurrentScreen;

    case ImageGrabber::FullScreen:
        return ImageGrabber::FullScreen;

    default:
        return ImageGrabber::RectArea;
    }
}

void KsnipConfig::setCaptureMode( ImageGrabber::CaptureMode captureMode )
{
    mConfig.setValue( "ImageGrabber/CaptureMode", captureMode );
    mConfig.sync();
}

QPen KsnipConfig::pen() const
{
    QPen pen;
    pen.setColor( penColor() );
    pen.setWidth( penSize() );
    return pen;
}

QColor KsnipConfig::penColor() const
{
    return mConfig.value( "Painter/PenColor", QColor( "Red" ) ).value<QColor>();
}

void KsnipConfig::setPenColor( QColor color )
{
    mConfig.setValue( "Painter/PenColor", color );
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::penSize() const
{
    return mConfig.value( "Painter/PenSize", 3 ).toInt();
}

void KsnipConfig::setPenSize( int size )
{
    mConfig.setValue( "Painter/PenSize", size );
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::marker() const
{
    QPen marker;
    marker.setColor( markerColor() );
    marker.setWidth( markerSize() );
    return marker;
}

QColor KsnipConfig::markerColor() const
{
    return mConfig.value( "Painter/MarkerColor", QColor( "Yellow" ) ).value<QColor>();
}

void KsnipConfig::setMarkerColor( QColor color )
{
    mConfig.setValue( "Painter/MarkerColor", color );
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::markerSize() const
{
    return mConfig.value( "Painter/MarkerSize", 20 ).toInt();
}

void KsnipConfig::setMarkerSize( int size )
{
    mConfig.setValue( "Painter/MarkerSize", size );
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::captureDelay() const
{
    return mConfig.value( "ImageGrabber/CaptureDelay", 300 ).toInt() ;
}

void KsnipConfig::setCaptureDelay( int delay )
{
    mConfig.setValue( "ImageGrabber/CaptureDelay", delay );
    mConfig.sync();
    emit captureDelayUpdated(delay);
}