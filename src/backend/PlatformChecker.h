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

#ifndef PLATFORMCHECKER_H
#define PLATFORMCHECKER_H

#include <QString>

#include "src/common/runner/CommandRunner.h"

class PlatformChecker
{
    enum class Platform
    {
        X11,
        Wayland,
        Unknown
    };

    enum class Environment
    {
        Gnome,
        KDE,
        Unknown
    };

public:
    static PlatformChecker *instance();

    bool isX11() const;
    bool isWayland() const;
    bool isKde() const;
    bool isGnome() const;

private:
    Platform   mPlatform;
    Environment mEnvironment;

    void checkPlatform();
    void checkEnvironment();
    bool outputContainsValue(const QString& output, const QString& value) const;

    PlatformChecker();
};

#endif // PLATFORMCHECKER_H
