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

#include "DonateTab.h"

DonateTab::DonateTab()
{
	mLayout = new QVBoxLayout();
	mContent = new QLabel();
	mContent->setText(QStringLiteral("<b>") + tr("Donate a Beer?") + QStringLiteral("</b>") + QStringLiteral("<br/>") +
					  tr("Sure, you can do that") + QStringLiteral(" <a href=\"https://www.paypal.me/damirporobic\">") + tr("here") + QStringLiteral("</a>.<br/><br/>") +
		              QStringLiteral("<b>") + tr("Become a Sponsor") + QStringLiteral("?</b>") + QStringLiteral("<br/>") +
		              tr("Also possible, ") + QStringLiteral(" <a href=\"https://github.com/sponsors/DamirPorobic\">") + tr("here") + QStringLiteral("</a>.<br/><br/>") +
					  tr("Donations are always welcome") + QStringLiteral(" :)"));
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
