/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_ACTIONTESTS_H
#define KSNIP_ACTIONTESTS_H

#include <QtTest>

class ActionTests : public QObject
{
    Q_OBJECT
private slots:
    void EqualsOperator_Should_ReturnTrue_When_AllValuesMatch();
    void EqualsOperator_Should_ReturnFalse_When_NameIsDifferent();
    void EqualsOperator_Should_ReturnFalse_When_ShortcutDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsCaptureEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IncludeCursorDifferent();
    void EqualsOperator_Should_ReturnFalse_When_CaptureDelayDifferent();
    void EqualsOperator_Should_ReturnFalse_When_CaptureModeDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsSaveEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsCopyToClipboardEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsUploadEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsOpenDirectoryEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsPinScreenshotEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsHideMainWindowEnabledDifferent();
    void EqualsOperator_Should_ReturnFalse_When_IsGlobalShortcutDifferent();
};

#endif //KSNIP_ACTIONTESTS_H
