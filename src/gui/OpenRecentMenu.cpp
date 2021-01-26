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

#include "OpenRecentMenu.h"


OpenRecentMenu::OpenRecentMenu(QWidget *parent)
	: QMenu(parent),
	  mRecentImagesPathStore(RecentImagesPathStore::instance()),
	  mRecentImageSelectedMapper(new QSignalMapper(this))
{
	connect(&mRecentImagesPathStore, &RecentImagesPathStore::recentImagesPathChanged,
			this, &OpenRecentMenu::populateMenu);
	populateMenu();
}

void OpenRecentMenu::populateMenu()
{
	delete mRecentImageSelectedMapper;
	mRecentImageSelectedMapper = new QSignalMapper(this);

	clear();

	const auto recentImages = mRecentImagesPathStore.getRecentImagesPath();

	int imageIdx = 0;
	for (; imageIdx<recentImages.size(); ++imageIdx) {
		const auto path = recentImages.at(recentImages.size() - 1 - imageIdx);

		QAction *action = new QAction(mRecentImageSelectedMapper);
		action->setText(path);
		action->setShortcut(Qt::CTRL + Qt::Key_0 + imageIdx);
		addAction(action);

		mRecentImageSelectedMapper->setMapping(action, path);
		connect(action, SIGNAL(triggered()),
				mRecentImageSelectedMapper, SLOT(map()));
	}

	setEnabled(imageIdx != 0);
	connect(mRecentImageSelectedMapper, QOverload<const QString &>::of(&QSignalMapper::mapped),
		[=](const QString &text){
		emit openRecentSelected(text);
	});
}
