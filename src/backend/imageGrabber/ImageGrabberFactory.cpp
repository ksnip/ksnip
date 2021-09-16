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
	auto logger = LoggerProvider::instance();
#if defined(__APPLE__)
	logger->log(QLatin1String("MacImageGrabber selected"));
    return new MacImageGrabber();
#endif

#if defined(UNIX_X11)
    if (PlatformChecker::instance()->isX11()) {
    	if(PlatformChecker::instance()->isGnome()) {
			logger->log(QLatin1String("GnomeX11ImageGrabber selected"));
			return new GnomeX11ImageGrabber();
		} else {
			logger->log(QLatin1String("X11ImageGrabber selected"));
			return new X11ImageGrabber();
		}
    } else if (PlatformChecker::instance()->isWayland()) {
        auto config = KsnipConfigProvider::instance();
    	if (config->forceGenericWaylandEnabled() || PlatformChecker::instance()->isSnap()) {
			logger->log(QLatin1String("WaylandImageGrabber selected"));
		    return new WaylandImageGrabber();
    	} else if(PlatformChecker::instance()->isKde()) {
			logger->log(QLatin1String("KdeWaylandImageGrabber selected"));
		    return new KdeWaylandImageGrabber();
	    } else if (PlatformChecker::instance()->isGnome()) {
			logger->log(QLatin1String("GnomeWaylandImageGrabber selected"));
		    return new GnomeWaylandImageGrabber();
	    } else {
		    qCritical("Unknown wayland platform, using default wayland Image Grabber.");
			logger->log(QLatin1String("WaylandImageGrabber selected"));
		    return new WaylandImageGrabber();
    	}
    } else {
        qCritical("Unknown platform, using default X11 Image Grabber.");
        return new X11ImageGrabber();
    }
#endif

#if  defined(_WIN32)
	logger->log(QLatin1String("WinImageGrabber selected"));
    return new WinImageGrabber();
#endif
}
