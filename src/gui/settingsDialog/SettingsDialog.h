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

#ifndef KSNIP_SETTINGSDIALOG_H
#define KSNIP_SETTINGSDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QStackedLayout>
#include <QApplication>

#include "AnnotationSettings.h"
#include "ApplicationSettings.h"
#include "ImageGrabberSettings.h"
#include "ImgurUploaderSettings.h"
#include "ScriptUploaderSettings.h"
#include "HotKeySettings.h"
#include "UploaderSettings.h"
#include "SaverSettings.h"
#include "StickerSettings.h"
#include "TrayIconSettings.h"
#include "SnippingAreaSettings.h"
#include "WatermarkSettings.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/common/provider/ScaledSizeProvider.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent, const QList<CaptureModes> &captureModes);
    ~SettingsDialog() override;

private:
	KsnipConfig *mConfig;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;
	ApplicationSettings *mApplicationSettings;
	ImageGrabberSettings *mImageGrabberSettings;
	ImgurUploaderSettings *mImgurUploaderSettings;
	ScriptUploaderSettings *mScriptUploaderSettings;
	HotKeySettings *mHotKeySettings;
    AnnotationSettings *mAnnotationSettings;
    UploaderSettings *mUploaderSettings;
    SaverSettings *mSaverSettings;
    StickerSettings *mStickerSettings;
	TrayIconSettings *mTrayIconSettings;
    SnippingAreaSettings *mSnippingAreaSettings;
	WatermarkSettings *mWatermarkSettings;
	QTreeWidget *mTreeWidget;
    QStackedLayout *mStackedLayout;
    QList<QTreeWidgetItem*> mNavigatorItems;

    void saveSettings();
    void initGui();

private slots:
    void switchTab();
    void cancelClicked();
    void okClicked();
};

#endif // KSNIP_SETTINGSDIALOG_H
