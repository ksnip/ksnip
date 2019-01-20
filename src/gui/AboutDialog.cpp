/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "AboutDialog.h"

AboutDialog::AboutDialog(MainWindow* parent) : QDialog(parent),
    mParent(parent),
    mMainLayout(new QVBoxLayout),
    mHeaderLayout(new QHBoxLayout),
    mTabWidget(new QTabWidget),
    mAboutWidget(new QWidget),
    mVersionWidget(new QWidget),
    mAuthorWidget(new QWidget),
    mCloseButton(new QPushButton)
{
    setWindowTitle(tr("About ") + QApplication::applicationName());

    createHeader();
    createAboutTab();
    createVersionTab();
    createAuthorTab();

    mTabWidget->addTab(mAboutWidget, tr("About"));
    mTabWidget->addTab(mVersionWidget, tr("Version"));
    mTabWidget->addTab(mAuthorWidget, tr("Author"));
    mTabWidget->setMinimumSize(mTabWidget->sizeHint());

    mCloseButton->setText(tr("Close"));
    connect(mCloseButton, &QPushButton::clicked, this, &AboutDialog::close);

    mMainLayout->addLayout(mHeaderLayout);
    mMainLayout->addWidget(mTabWidget);
    mMainLayout->addWidget(mCloseButton, 1, Qt::AlignRight);

    setLayout(mMainLayout);

    setFixedSize(sizeHint() + QSize(10, 0));
}

//
// Private Functions
//

void AboutDialog::createHeader()
{
    auto pixmap = new QPixmap(QStringLiteral(":/ksnip64.png"));
    auto label = new QLabel();
    mHeaderLayout = new QHBoxLayout();
    label->setPixmap(*pixmap);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mHeaderLayout->addWidget(label);
    label = new QLabel(QStringLiteral("<h2>") + QApplication::applicationName() + QStringLiteral("</h2>"));
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    mHeaderLayout->addWidget(label);
    mHeaderLayout->setAlignment(Qt::AlignLeft);
}

void AboutDialog::createAboutTab()
{
    auto layout = new QVBoxLayout();
    auto label = new QLabel();
    label->setText(QStringLiteral("<b>") + QApplication::applicationName() + QStringLiteral(" ") + tr("Screenshot Tool") + QStringLiteral("</b><br/><br/>") +
	    tr("(C) 2018 Damir Porobic") + QStringLiteral("<br/><br/>") +
        tr("License: ") + QStringLiteral("<a href=\"https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html\">GNU General Public License Version 2</a>")
                       + QStringLiteral("<br/><br/>") +
        tr("Please use ") + QStringLiteral("<a href=\"https://github.com/damirporobic/ksnip/issues/\">GitHub</a>") + tr(" to report bugs."));
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
    layout->addWidget(label);
    mAboutWidget->setLayout(layout);
}

void AboutDialog::createVersionTab()
{
    auto layout = new QVBoxLayout();
    auto label = new QLabel();
	label->setText(QStringLiteral("<b>") + tr("Version") + QStringLiteral(": ") + QApplication::applicationVersion() + QStringLiteral("</b>") +
		QStringLiteral("<br/><b>") + tr("Build") + QStringLiteral(": ") + QStringLiteral(KSNIP_BUILD_NUMBER) + QStringLiteral("</b>") +
		QStringLiteral("</b><br/><br/>") +
		tr("Using:") +
		QStringLiteral("<ul>"
                                  "<li>Qt5</li>"
                                  "<li>X11</li>"
                                  "<li>KDE Wayland</li>"
                                  "<li>Gnome Wayland</li>"
		               "</ul>"));
    layout->addWidget(label);
    mVersionWidget->setLayout(layout);
}

void AboutDialog::createAuthorTab()
{
    auto layout = new QVBoxLayout();
    auto label = new QLabel();
    label->setText(QStringLiteral("<h4>") + tr("The Author:") + QStringLiteral("</h4>") +
                   QStringLiteral("Damir Porobic") + QStringLiteral(" (<a href=\"mailto:damir.porobic@gmx.com\" target=\"_top\">Email</a>)") +
                   QStringLiteral("<h4>") + tr("Contributors:") + QStringLiteral("</h4>") +
                   QStringLiteral("Lvaskz - ") + tr("Spanish Translation") + QStringLiteral(" (<a href=\"mailto:lvaskz@protonmail.com\" target=\"_top\">Email</a>)"));
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);

    layout->addWidget(label);

    mAuthorWidget->setLayout(layout);
}
