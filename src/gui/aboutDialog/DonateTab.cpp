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

#include "DonateTab.h"

DonateTab::DonateTab()
{
	mLayout = new QVBoxLayout();
	mContent = new QLabel();
	mContent->setText(QLatin1String("<b>") + tr("Donation") + QLatin1String("</b>") + QLatin1String("<br/>") +
					  tr("ksnip is a non-profitable copylefted libre software project, and<br/>"
		                    "still has some costs that need to be covered,<br/>"
		                    "like domain costs or hardware costs for cross-platform support.") + QLatin1String("<br/>") +
		              tr("If you want to help or just<br/>"
			                 "want to appreciate the work being done<br/>"
					         "by treating developers to a beer or coffee, you can do that") + QLatin1String(" <a href=\"https://www.paypal.me/damirporobic\">") + tr("here") + QLatin1String("</a>.<br/><br/>") +
					  tr("Donations are always welcome") + QLatin1String(" :)") + QLatin1String("<br/><br/>") +
		              QLatin1String("<b>") + tr("Become a GitHub Sponsor") + QLatin1String("?</b>") + QLatin1String("<br/>") +
		              tr("Also possible, ") + QLatin1String(" <a href=\"https://github.com/sponsors/DamirPorobic\">") + tr("here") + QLatin1String("</a>."));

	mContent->setTextFormat(Qt::RichText);
	mContent->setTextInteractionFlags(Qt::TextBrowserInteraction);
	mContent->setOpenExternalLinks(true);
	mLayout->addWidget(mContent);
	setLayout(mLayout);
}

DonateTab::~DonateTab()
{
	delete mContent;
	delete mLayout;
}
