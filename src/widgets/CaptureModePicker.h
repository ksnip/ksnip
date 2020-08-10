/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CAPTUREMODEPICKER_H
#define KSNIP_CAPTUREMODEPICKER_H

#include <QAction>

#include "src/widgets/CustomToolButton.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/enum/CaptureModes.h"

class CaptureModePicker : public CustomToolButton
{
Q_OBJECT
public:
    explicit CaptureModePicker(const QList<CaptureModes> &captureModes);
    ~CaptureModePicker() override = default;
    void setCaptureMode(CaptureModes mode);
    CaptureModes captureMode() const;
    QList<QAction*> captureActions() const;

signals:
    void captureModeSelected(CaptureModes mode) const;

private:
    CaptureModes mSelectedCaptureMode;
    QList<QAction*> mCaptureActions;

    void init(const QList<CaptureModes> &captureModes);
    void selectCaptureMode(CaptureModes mode);

	QAction *createAction(const QString &text, const QString &tooltip, const QString &iconName, CaptureModes captureMode, const QKeySequence &shortcut);
	bool isCaptureModeSupported(const QList<CaptureModes> &captureModes, CaptureModes captureMode) const;
};

#endif //KSNIP_CAPTUREMODEPICKER_H
