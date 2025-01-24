/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_KEYEVENTFILTER_H
#define KSNIP_KEYEVENTFILTER_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QSharedPointer>

#include "src/gui/globalHotKeys/keyHandler/IKeyHandler.h"

class NativeKeyEventFilter: public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit NativeKeyEventFilter(const QSharedPointer<IKeyHandler> &keyHandler);
    ~NativeKeyEventFilter() override = default;

    bool nativeEventFilter(const QByteArray &, void *message,
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                           qintptr
#else
                           long
#endif
                               *) override;

signals:
    void triggered() const;

private:
    QSharedPointer<IKeyHandler> mKeyHandler;
};

#endif //KSNIP_KEYEVENTFILTER_H
