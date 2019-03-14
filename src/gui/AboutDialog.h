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

#ifndef KSNIP_ABOUTDIALOG_H
#define KSNIP_ABOUTDIALOG_H

#include <QDialog>

#include "MainWindow.h"
#include "BuildConfig.h"

class QLabel;
class MainWindow;

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(MainWindow *parent = nullptr);

private:
    MainWindow  *mParent;
    QVBoxLayout *mMainLayout;
    QHBoxLayout *mHeaderLayout;
    QTabWidget  *mTabWidget;
    QWidget     *mAboutWidget;
    QWidget     *mVersionWidget;
    QWidget     *mAuthorWidget;
    QPushButton *mCloseButton;

    void createHeader();
    void createAboutTab();
    void createVersionTab();
    void createAuthorTab();
    QString createContributorEntry(const QString &name, const QString &role, const QString &email = QString()) const;
    QString createEmailEntry(const QString &email) const;
};

#endif // KSNIP_ABOUTDIALOG_H
