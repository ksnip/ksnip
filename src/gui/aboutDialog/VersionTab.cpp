/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "VersionTab.h"

VersionTab::VersionTab()
{
	mLayout = new QVBoxLayout();
	mContent = new QLabel();
	mContent->setText(QStringLiteral("<b>") + tr("Version") + QStringLiteral(": ") + QApplication::applicationVersion() + QStringLiteral("</b>") +
				   QStringLiteral("<br/><b>") + tr("Build") + QStringLiteral(": ") + QStringLiteral(KSNIP_BUILD_NUMBER) + QStringLiteral("</b>") +
				   QStringLiteral("</b><br/><br/>") +
				   tr("Using:") +
				   QStringLiteral("<ul>"
								  "<li>Qt5</li>"
								  "<li>X11</li>"
								  "<li>KDE Wayland</li>"
								  "<li>Gnome Wayland</li>"
								  "</ul>"));
	mContent->setTextInteractionFlags(Qt::TextSelectableByMouse);
	mLayout->addWidget(mContent);
	setLayout(mLayout);
}

VersionTab::~VersionTab()
{
	delete mContent;
	delete mLayout;
}
