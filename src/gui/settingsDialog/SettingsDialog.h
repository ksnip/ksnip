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

#ifndef KSNIP_SETTINGSDIALOG_H
#define KSNIP_SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedLayout>
#include <QApplication>

#include "AnnotationSettings.h"
#include "ApplicationSettings.h"
#include "ImageGrabberSettings.h"
#include "ImgurUploaderSettings.h"
#include "backend/config/KsnipConfig.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override;

private:
    QPushButton *mOkButton;
    QPushButton *mCancelButton;
	ApplicationSettings *mApplicationSettings;
	ImageGrabberSettings *mImageGrabberSettings;
	ImgurUploaderSettings *mImgurUploaderSettings;
    AnnotationSettings *mAnnotationSettings;
    QListWidget *mListWidget;
    QStackedLayout *mStackedLayout;
    KsnipConfig *mConfig;

    void saveSettings();
    void initGui();

private slots:
    void switchTab();
    void cancelClicked();
    void okClicked();
};

#endif // KSNIP_SETTINGSDIALOG_H
