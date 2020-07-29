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

#ifndef KSNIP_IMGURUPLOADERSETTINGS_H
#define KSNIP_IMGURUPLOADERSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QDesktopServices>

#include "src/backend/config/KsnipConfig.h"
#include "src/backend/uploader/imgur/ImgurWrapper.h"
#include "src/gui/ImgurHistoryDialog.h"
#include "src/widgets/CustomLineEdit.h"
#include "src/common/constants/DefaultValues.h"

class ImgurUploaderSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit ImgurUploaderSettings(KsnipConfig *ksnipConfig);
	~ImgurUploaderSettings() override;
	void saveSettings();

private:
	KsnipConfig *mConfig;
	QCheckBox *mForceAnonymousCheckbox;
	QCheckBox *mDirectLinkToImageCheckbox;
	QCheckBox *mAlwaysCopyToClipboardCheckBox;
	QCheckBox *mOpenLinkInBrowserCheckbox;
	QLineEdit *mClientIdLineEdit;
	QLineEdit *mClientSecretLineEdit;
	QLineEdit *mPinLineEdit;
	CustomLineEdit *mBaseUrlLineEdit;
	QLabel *mUsernameLabel;
	QLabel *mBaseUrlLabel;
	QPushButton *mGetPinButton;
	QPushButton *mGetTokenButton;
	QPushButton *mHistoryButton;
	ImgurWrapper *mImgurWrapper;
	QGridLayout *mLayout;

	void initGui();
	void loadConfig();

private slots:
	void requestImgurPin();
	void getImgurToken();
	void imgurClientEntered(const QString &text);
	void imgurTokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username);
	void imgurTokenError(const QString &message);
	void showImgurHistoryDialog();
};

#endif //KSNIP_IMGURUPLOADERSETTINGS_H
