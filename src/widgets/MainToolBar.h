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
    explicit MainToolBar(const QList<CaptureModes> &captureModes, QAction* undoAction, QAction* redoAction);
    ~MainToolBar() override;
    void selectCaptureMode(CaptureModes captureModes);
    void setCaptureDelay(int delay);
    void setSaveActionEnabled(bool enabled);
    void setCopyActionEnabled(bool enabled);
    void setCropEnabled(bool enabled);
    QAction* newCaptureAction() const;
    QAction* saveAction() const;
    QAction* copyToClipboardAction() const;
    QAction* cropAction() const;
    QAction* undoAction() const;
    QAction* redoAction() const;

signals:
    void captureModeSelected(CaptureModes mode) const;
    void saveActionTriggered() const;
    void copyActionTriggered() const;
    void captureDelayChanged(int delay) const;
    void cropActionTriggered() const;

public slots:
    void newCaptureTriggered();

private:
    QToolButton *mSaveButton;
    QToolButton *mCopyButton;
    QToolButton *mCropButton;
    QToolButton *mUndoButton;
    QToolButton *mRedoButton;
    CaptureModePicker *mCaptureModePicker;
    CustomSpinBox *mDelayPicker;
    QLabel *mDelayLabel;
    QAction *mNewCaptureAction;
    QAction *mSaveAction;
    QAction *mCopyAction;
    QAction *mCropAction;
    QAction *mUndoAction;
    QAction *mRedoAction;

};


#endif //KSNIP_MAINTOOLBAR_H
