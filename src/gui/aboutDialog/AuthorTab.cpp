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

#include "AuthorTab.h"

AuthorTab::AuthorTab()
{
	mLayout = new QVBoxLayout();
	mContent = new QLabel();
	mContent->setText(
		           QLatin1String("<b>") + tr("The Authors:") + QLatin1String("</b><br>") +
				   QLatin1String("Damir Porobic ") + createEmailEntry(QLatin1String("damir.porobic@gmx.com")) + QLatin1String("<br>") +
				   QLatin1String("Stefan Comanescu") + createEmailEntry(QLatin1String("fnkabit@gmail.com")) + QLatin1String("<br><br>") +
				   QLatin1String("<b>") + tr("Contributors:") + QLatin1String("</b><br>") +
				   createContributorEntry(QLatin1String("Galileo Sartor"), tr("Snap & Flatpak Support")) +
				   createContributorEntry(QLatin1String("Luis Vásquez"), tr("Spanish Translation"), QLatin1String("lvaskz@protonmail.com")) +
				   createContributorEntry(QLatin1String("Heimen Stoffels"), tr("Dutch Translation"), QLatin1String("vistausss@outlook.com")) +
				   createContributorEntry(QLatin1String("Yury Martynov"), tr("Russian Translation"), QLatin1String("email@linxon.ru")) +
				   createContributorEntry(QLatin1String("Allan Nordhøy"), tr("Norwegian Bokmål Translation"), QLatin1String("epost@anotheragency.no")) +
				   createContributorEntry(QLatin1String("4goodapp"), tr("French Translation")) +
				   createContributorEntry(QLatin1String("epsiloneridani"), tr("Polish Translation"))
	);
	mContent->setTextFormat(Qt::RichText);
	mContent->setTextInteractionFlags(Qt::TextBrowserInteraction);
	mContent->setOpenExternalLinks(true);

	mLayout->addWidget(mContent);

	setLayout(mLayout);
}

AuthorTab::~AuthorTab()
{
	delete mLayout;
	delete mContent;
}

QString AuthorTab::createContributorEntry(const QString &name, const QString &role, const QString &email) const
{
	auto baseEntry = name + QLatin1String(" - ") + role;
	if(!email.isEmpty()) {
		baseEntry +=  QLatin1String(" ") + createEmailEntry(email);
	}
	return baseEntry + QLatin1String("<br>");
}

QString AuthorTab::createEmailEntry(const QString &email)
{
	return QLatin1String("(<a href=\"mailto:") + email + QLatin1String(R"(" target="_top">Email</a>))");
}
