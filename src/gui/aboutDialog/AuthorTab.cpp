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
		           QLatin1Literal("<b>") + tr("The Author:") + QLatin1Literal("</b><br>") +
				   QLatin1Literal("Damir Porobic ") + createEmailEntry(QLatin1Literal("damir.porobic@gmx.com")) + QLatin1Literal("<br><br>") +
				   QLatin1Literal("<b>") + tr("Contributors:") + QLatin1Literal("</b><br>") +
				   createContributorEntry(QLatin1Literal("Galileo Sartor"), tr("Snap & Flatpak Support")) +
				   createContributorEntry(QLatin1Literal("fnkabit"), tr("Feature Implementation")) +
				   createContributorEntry(QStringLiteral("Luis Vásquez"), tr("Spanish Translation"), QLatin1Literal("lvaskz@protonmail.com")) +
				   createContributorEntry(QLatin1Literal("Heimen Stoffels"), tr("Dutch Translation"), QLatin1Literal("vistausss@outlook.com")) +
				   createContributorEntry(QLatin1Literal("Yury Martynov"), tr("Russian Translation"), QLatin1Literal("email@linxon.ru")) +
				   createContributorEntry(QStringLiteral("Allan Nordhøy"), tr("Norwegian Bokmål Translation"), QLatin1Literal("epost@anotheragency.no")) +
				   createContributorEntry(QLatin1Literal("4goodapp"), tr("French Translation")) +
				   createContributorEntry(QLatin1Literal("epsiloneridani"), tr("Polish Translation"))
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
	auto baseEntry = name + QLatin1Literal(" - ") + role;
	if(!email.isEmpty()) {
		baseEntry +=  QLatin1Literal(" ") + createEmailEntry(email);
	}
	return baseEntry + QLatin1Literal("<br>");
}

QString AuthorTab::createEmailEntry(const QString &email)
{
	return QLatin1Literal("(<a href=\"mailto:") + email + QLatin1Literal(R"(" target="_top">Email</a>))");
}
