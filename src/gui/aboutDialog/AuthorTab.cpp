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
		           QStringLiteral("<b>") + tr("The Author:") + QStringLiteral("</b><br>") +
				   QStringLiteral("Damir Porobic ") + createEmailEntry(QStringLiteral("damir.porobic@gmx.com")) + QStringLiteral("<br><br>") +
				   QStringLiteral("<b>") + tr("Contributors:") + QStringLiteral("</b><br>") +
				   createContributorEntry(QStringLiteral("Galileo Sartor"), tr("Snap & Flatpak Support")) +
				   createContributorEntry(QStringLiteral("Luis Vásquez"), tr("Spanish Translation"), QStringLiteral("lvaskz@protonmail.com")) +
				   createContributorEntry(QStringLiteral("Heimen Stoffels"), tr("Dutch Translation"), QStringLiteral("vistausss@outlook.com")) +
				   createContributorEntry(QStringLiteral("Yury Martynov"), tr("Russian Translation"), QStringLiteral("email@linxon.ru")) +
				   createContributorEntry(QStringLiteral("Allan Nordhøy"), tr("Norwegian Bokmål Translation"), QStringLiteral("epost@anotheragency.no")) +
				   createContributorEntry(QStringLiteral("4goodapp"), tr("French Translation")) +
				   createContributorEntry(QStringLiteral("epsiloneridani"), tr("Polish Translation"))
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
	auto baseEntry = name + QStringLiteral(" - ") + role;
	if(!email.isEmpty()) {
		baseEntry +=  QStringLiteral(" ") + createEmailEntry(email);
	}
	return baseEntry + QStringLiteral("<br>");
}

QString AuthorTab::createEmailEntry(const QString &email) const
{
	return QStringLiteral("(<a href=\"mailto:") + email + QStringLiteral("\" target=\"_top\">Email</a>)");
}
