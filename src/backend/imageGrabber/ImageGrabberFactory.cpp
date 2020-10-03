/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ImageGrabberFactory.h"

AbstractImageGrabber* ImageGrabberFactory::createImageGrabber()
{
#if defined(__APPLE__)
    return new MacImageGrabber();
#endif

#if defined(__linux__)
    if (PlatformChecker::instance()->isX11()) {
        return new X11ImageGrabber();
    } else if (PlatformChecker::instance()->isWayland()) {
        auto config = KsnipConfigProvider::instance();
    	if (config->forceGenericWaylandEnabled() || PlatformChecker::instance()->isSnap()) {
		    return new WaylandImageGrabber();
    	} else if(PlatformChecker::instance()->isKde()) {
		    return new KdeWaylandImageGrabber();
	    } else if (PlatformChecker::instance()->isGnome()) {
		    return new GnomeWaylandImageGrabber();
	    } else {
		    qCritical("Unknown wayland platform, using default wayland Image Grabber.");
		    return new WaylandImageGrabber();
    	}
    } else {
        qCritical("Unknown platform, using default X11 Image Grabber.");
        return new X11ImageGrabber();
    }
#endif

#if  defined(_WIN32)
    return new WinImageGrabber();
#endif
}
