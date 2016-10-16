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

#include <QObject>

#ifndef CMDOPTION_H
#define CMDOPTION_H

class CmdOption
{
public:
    CmdOption ( QString name, QString description, QString longName = 0 );

    QString name() const;
    void setName ( QString name );

    QString longName() const;
    void setLongName ( QString longName );

    QString description() const;
    void setDescription ( QString description );

    bool isSet() const;
    void set ( bool enabled );

    QString value() const;
    void setValue ( QString value );

private:
    QString mName;
    QString mLongName;
    QString mDescription;
    bool    mIsSet; 
    QString mValue;
};

#endif // CMDOPTION_H
