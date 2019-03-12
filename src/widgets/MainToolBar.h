/*
 *  Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_MAINTOOLBAR_H
#define KSNIP_MAINTOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QLabel>

#include "CaptureModePicker.h"
#include "CustomSpinBox.h"

class MainToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit MainToolBar(const QList<CaptureModes> &captureModes);
    ~MainToolBar() override;
    void selectCaptureMode(CaptureModes captureModes);
    void setCaptureDelay(int delay);
    void setSaveActionEnabled(bool enabled);
    void setCopyToClipboardActionEnabled(bool enabled);
    QAction* newCaptureAction() const;
    QAction* saveAction() const;
    QAction* copyToClipboardAction() const;

signals:
    void captureModeSelected(CaptureModes mode) const;
    void saveActionTriggered() const;
    void copyToClipboardActionTriggered() const;
    void captureDelayChanged(int delay) const;

public slots:
    void newCaptureTriggered();

private:
    QToolButton *mSaveButton;
    QToolButton *mCopyToClipboardButton;
    CaptureModePicker *mCaptureModePicker;
    CustomSpinBox *mDelayPicker;
    QLabel *mDelayLabel;
    QAction *mNewCaptureAction;
    QAction *mSaveAction;
    QAction *mCopyToClipboardAction;

};


#endif //KSNIP_MAINTOOLBAR_H
