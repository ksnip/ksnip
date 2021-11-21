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

#include "ContactTab.h"

ContactTab::ContactTab() :
	mLayout(new QVBoxLayout()),
	mContent(new QLabel())
{
	mContent->setText(
			QLatin1String("<b>") + tr("Community") + QLatin1String("</b>") +
			QLatin1String("<br>") +
			tr("If you have general questions, ideas or just want to talk about ksnip,<br/>"
			      "please join our %1 or our %2 server.")
			.arg(QLatin1String("<a href=\"http://discord.ksnip.org\">Discord</a>"))
			.arg(QLatin1String("<a href=\"https://web.libera.chat/?channels=#ksnip\">IRC</a>"))	+
			QLatin1String("<br/><br/>") +
			QLatin1String("<b>") + tr("Bug Reports") + QLatin1String("</b>") +
			QLatin1String("<br>") +
			tr("Please use %1 to report bugs.")
			.arg(QLatin1String("<a href=\"https://github.com/ksnip/ksnip/issues/\">GitHub</a>")));
	mContent->setTextFormat(Qt::RichText);
	mContent->setTextInteractionFlags(Qt::TextBrowserInteraction);
	mContent->setOpenExternalLinks(true);
	mLayout->addWidget(mContent);
	setLayout(mLayout);


}

ContactTab::~ContactTab()
{
	delete mLayout;
	delete mContent;
}
