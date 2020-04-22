/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "ImgurHistoryDialog.h"

ImgurHistoryDialog::ImgurHistoryDialog()
{
	setWindowTitle(QApplication::applicationName() + QStringLiteral(" - ") + tr("Imgur History"));
	setMinimumWidth(650);
	setMinimumHeight(400);

	ImgurResponseLogger imgurResponseLogger;
	auto logEntries = imgurResponseLogger.getLogs();

	createTable(logEntries.count());

	populateTable(logEntries);

	mCloseButton = new QPushButton(tr("Close"));
	connect(mCloseButton, &QPushButton::clicked, this, &QDialog::close);

	mLayout = new QVBoxLayout;
	mLayout->addWidget(mTableWidget);
	mLayout->addWidget(mCloseButton);
	mLayout->setAlignment(Qt::AlignRight);
	setLayout(mLayout);
}


ImgurHistoryDialog::~ImgurHistoryDialog()
{
	delete mTableWidget;
	delete mLayout;
	delete mCloseButton;
}

void ImgurHistoryDialog::createTable(int rowCount)
{
	mTableWidget = new QTableWidget(rowCount, 3, this);
	mTableWidget->setHorizontalHeaderLabels(QStringList{ tr("Time Stamp"), tr("Link"), tr("Delete Link") });
	auto header = mTableWidget->horizontalHeader();
	header->setStretchLastSection(true);

	connect(mTableWidget, &QTableWidget::cellClicked, this, &ImgurHistoryDialog::cellClicked);
}

void ImgurHistoryDialog::populateTable(const QStringList &logEntries)
{
	for (const auto &entry : logEntries) {
		addEntryToTable(entry, logEntries.indexOf(entry));
	}
	mTableWidget->resizeColumnsToContents();
}

void ImgurHistoryDialog::addEntryToTable(const QString &entry, int row) const
{
	auto cells = entry.split(QStringLiteral(","));
	auto dateCell = new QTableWidgetItem(cells[0]);
	auto linkCell = new QTableWidgetItem(cells[1]);
	auto deleteLinkCell = new QTableWidgetItem(cells[2]);
	mTableWidget->setItem(row, 0, dateCell);
	mTableWidget->setItem(row, 1, linkCell);
	mTableWidget->setItem(row, 2, deleteLinkCell);
}

void ImgurHistoryDialog::cellClicked(int row, int column) const
{
	if (column == 1 || column == 2) {
		auto cell = mTableWidget->item(row, column);
		QDesktopServices::openUrl(cell->text());
	}
}
