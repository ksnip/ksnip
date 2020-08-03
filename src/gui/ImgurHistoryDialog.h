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

#ifndef KSNIP_IMGURHISTORYDIALOG_H
#define KSNIP_IMGURHISTORYDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QHeaderView>
#include <QPushButton>

#include "src/backend/uploader/imgur/ImgurResponseLogger.h"

class ImgurHistoryDialog : public QDialog
{
Q_OBJECT
public:
	explicit ImgurHistoryDialog();
	~ImgurHistoryDialog() override;

private:
	QVBoxLayout *mLayout;
	QTableWidget *mTableWidget;
	QPushButton *mCloseButton;

	void addEntryToTable(const QString &entry, int row) const;
	void populateTable(const QStringList &logEntries);
	void createTable(int rowCount);

private slots:
	void cellClicked(int row, int column) const;

};

#endif //KSNIP_IMGURHISTORYDIALOG_H
