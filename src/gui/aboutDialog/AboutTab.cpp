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

#include "AboutTab.h"

AboutTab::AboutTab()
{
	mLayout = new QVBoxLayout();
	mContent = new QLabel();
	mContent->setText(QLatin1String("<b>") + QApplication::applicationName() + QLatin1String(" ") + tr("Screenshot Tool") + QLatin1String("</b><br/><br/>") +
				   QLatin1String("(C) 2020 Damir Porobic") + QLatin1String("<br/><br/>") +
				   tr("License: ") + QLatin1String("<a href=\"https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html\">GNU General Public License Version 2</a>")
				   + QLatin1String("<br/><br/>") +
				   tr("Please use ") + QLatin1String("<a href=\"https://github.com/ksnip/ksnip/issues/\">GitHub</a>") + tr(" to report bugs."));
	mContent->setTextFormat(Qt::RichText);
	mContent->setTextInteractionFlags(Qt::TextBrowserInteraction);
	mContent->setOpenExternalLinks(true);
	mLayout->addWidget(mContent);
	setLayout(mLayout);
}

AboutTab::~AboutTab()
{
	delete mLayout;
	delete mContent;
}
