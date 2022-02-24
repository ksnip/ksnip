/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_DELAYHANDLER_H
#define KSNIP_DELAYHANDLER_H

#include <QSharedPointer>

#include "src/backend/config/IConfig.h"

class DelayHandler : public QObject
{
	Q_OBJECT
public:
	explicit DelayHandler(const QSharedPointer<IConfig> &config);
	~DelayHandler() override = default;
    int getDelay(int delay);
	int implicitDelay() const;

private:
	int mImplicitDelay;
	QSharedPointer<IConfig> mConfig;

private slots:
	void delayChanged();
};

#endif //KSNIP_DELAYHANDLER_H
