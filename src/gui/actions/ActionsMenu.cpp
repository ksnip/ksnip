/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "ActionsMenu.h"

ActionsMenu::ActionsMenu(KsnipConfig *config) :
	mConfig(config)
{
	Q_ASSERT(mConfig != nullptr);

	connect(mConfig, &KsnipConfig::actionsChanged, this, &ActionsMenu::actionsChanged);

	actionsChanged();
}

void ActionsMenu::actionsChanged()
{
	clear();

	auto actions = mConfig->actions();
	for (const auto& action : actions) {
		auto item = addAction(action.name());
		connect(item, &QAction::triggered, [this, action]() { emit triggered(action); });
	}

	setEnabled(!actions.isEmpty());
}
