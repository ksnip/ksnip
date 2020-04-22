/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent),
    mMainLayout(new QVBoxLayout),
    mHeaderLayout(new QHBoxLayout),
    mTabWidget(new QTabWidget),
	mAboutTab(new AboutTab),
	mVersionTab(new VersionTab),
    mAuthorTab(new AuthorTab),
    mDonateTab(new DonateTab),
    mCloseButton(new QPushButton)
{
    setWindowTitle(tr("About ") + QApplication::applicationName());

    createHeader();

    mTabWidget->addTab(mAboutTab, tr("About"));
    mTabWidget->addTab(mVersionTab, tr("Version"));
    mTabWidget->addTab(mAuthorTab, tr("Author"));
    mTabWidget->addTab(mDonateTab, tr("Donate"));
    mTabWidget->setMinimumSize(mTabWidget->sizeHint());

    mCloseButton->setText(tr("Close"));
    connect(mCloseButton, &QPushButton::clicked, this, &AboutDialog::close);

    mMainLayout->addLayout(mHeaderLayout);
    mMainLayout->addWidget(mTabWidget);
    mMainLayout->addWidget(mCloseButton, 1, Qt::AlignRight);

    setLayout(mMainLayout);

    setFixedSize(sizeHint() + QSize(10, 0));
}

AboutDialog::~AboutDialog()
{
	delete mMainLayout;
	delete mCloseButton;
	delete mAboutTab;
	delete mVersionTab;
	delete mAuthorTab;
	delete mDonateTab;
}

void AboutDialog::createHeader()
{
	auto pixmap = QPixmap(QStringLiteral(":/icons/ksnip"));
	auto scaledPixmap = pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    auto label = new QLabel();
    mHeaderLayout = new QHBoxLayout();
	label->setPixmap(scaledPixmap);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mHeaderLayout->addWidget(label);
    label = new QLabel(QStringLiteral("<h2>") + QApplication::applicationName() + QStringLiteral("</h2>"));
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mHeaderLayout->addWidget(label);
    mHeaderLayout->setAlignment(Qt::AlignLeft);
}
