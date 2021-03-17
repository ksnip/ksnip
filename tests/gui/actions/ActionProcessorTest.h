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

#ifndef KSNIP_ACTIONPROCESSORTEST_H
#define KSNIP_ACTIONPROCESSORTEST_H

#include <QtTest>

#include "src/gui/actions/ActionProcessor.h"

class ActionProcessorTest : public QObject
{
	Q_OBJECT
private slots:
	void Process_Should_TriggerCapture_When_CaptureEnabled();
	void Process_Should_NotTriggerCapture_When_CaptureDisabled();
	void Process_Should_StartPostProcessing_When_CaptureDisabledAndPostProcessingEnabled();
	void Process_Should_NotStartPostProcessing_When_CaptureDisabledAndPostProcessingDisabled();
	void Process_Should_NotStartPostProcessing_When_CaptureEnabledAndPostProcessingDisabled();
	void Process_Should_NotStartPostProcessing_When_CaptureEnabledAndPostProcessingEnabled();
	void CaptureFinished_Should_StartPostProcessing_When_CaptureEnabledAndPostProcessingEnabled();
	void CaptureFinished_Should_StartPostProcessing_When_CaptureEnabledAndPostProcessingDisabled();
	void CaptureFinished_Should_SendSignalsForAllSelectedActions();
	void CaptureFinished_Should_NotSendSignalsForNotSelectedActions();
};

#endif //KSNIP_ACTIONPROCESSORTEST_H
