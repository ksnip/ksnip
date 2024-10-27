/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_INSTANCELOCK_H
#define KSNIP_INSTANCELOCK_H

#include <QSharedPointer>
#include <QSharedMemory>
#include <QCoreApplication>

#include "IInstanceLock.h"
#include "SingleInstanceConstants.h"
#include "src/common/provider/IUsernameProvider.h"

class InstanceLock : public IInstanceLock
{
	Q_OBJECT
public:
	explicit InstanceLock(const QSharedPointer<IUsernameProvider> &usernameProvider);
	~InstanceLock() override;

	bool lock() override;

private:
	QSharedMemory *mSingular;

	bool create();
};


#endif //KSNIP_INSTANCELOCK_H
