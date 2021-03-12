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

#include "RecentImagesMenu.h"


RecentImagesMenu::RecentImagesMenu(IRecentImageService *recentImageService, QWidget *parent) :
	QMenu(parent),
	mRecentImageService(recentImageService)
{
	connect(this, &QMenu::aboutToShow, this, &RecentImagesMenu::populateMenu);
}

void RecentImagesMenu::populateMenu()
{
	clear();

	const auto recentImages = mRecentImageService->getRecentImagesPath();

	auto imageIndex = 0;
	for(const auto& path : recentImages) {
		auto action = createAction(path, imageIndex++);
		addAction(action);
	}

	setEnabled(recentImages.size() > 0);
}

QAction *RecentImagesMenu::createAction(const QString &path, int index)
{
	auto action = new QAction(this);
	action->setText(path);
	action->setShortcut(Qt::CTRL + Qt::Key_0 + index);

	connect(action, &QAction::triggered, this, [this, path](){
		emit openRecentSelected(path);
	});

	return action;
}
