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

#include "ActionProcessorTests.h"

#include "src/gui/actions/ActionProcessor.h"

#include "tests/utils/TestRunner.h"

void ActionProcessorTests::Process_Should_TriggerCapture_When_CaptureEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setCaptureDelay(2000);
	action.setIncludeCursor(true);
	action.setCaptureMode(CaptureModes::CurrentScreen);
	ActionProcessor processor;
	QSignalSpy spy(&processor, &ActionProcessor::triggerCapture);

	// act
	processor.process(action);

	// assert
	QCOMPARE(spy.count(), 1);
    QCOMPARE(qvariant_cast<CaptureModes>(spy.at(0).at(0)), CaptureModes::CurrentScreen);
    QCOMPARE(qvariant_cast<bool>(spy.at(0).at(1)), true);
    QCOMPARE(qvariant_cast<int>(spy.at(0).at(2)), 2000);
}

void ActionProcessorTests::Process_Should_NotTriggerCapture_When_CaptureDisabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(false);
	action.setCaptureDelay(2000);
	action.setIncludeCursor(true);
	action.setCaptureMode(CaptureModes::CurrentScreen);
	ActionProcessor processor;
	QSignalSpy spy(&processor, &ActionProcessor::triggerCapture);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 0);
}

void ActionProcessorTests::Process_Should_StartPostProcessing_When_CaptureDisabledAndPostProcessingEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(false);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 1);
}

void ActionProcessorTests::Process_Should_NotStartPostProcessing_When_CaptureDisabledAndPostProcessingDisabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(false);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(false);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 0);
}

void ActionProcessorTests::Process_Should_NotStartPostProcessing_When_CaptureEnabledAndPostProcessingDisabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(false);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 0);
}

void ActionProcessorTests::Process_Should_NotStartPostProcessing_When_CaptureEnabledAndPostProcessingEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 0);
}

void ActionProcessorTests::CaptureFinished_Should_StartPostProcessing_When_CaptureEnabledAndPostProcessingEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(spy.count(), 1);
}

void ActionProcessorTests::CaptureFinished_Should_StartPostProcessing_When_CaptureEnabledAndPostProcessingDisabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(false);
	QSignalSpy spy(&processor, &ActionProcessor::triggerSave);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(spy.count(), 1);
}

void ActionProcessorTests::CaptureFinished_Should_SendSignalsForAllSelectedActions()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(true);
	action.setIsCopyToClipboardEnabled(true);
	action.setIsOpenDirectoryEnabled(true);
	action.setIsUploadEnabled(true);
	action.setIsPinImageEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(false);
	QSignalSpy saveSignalSpy(&processor, &ActionProcessor::triggerSave);
	QSignalSpy copySignalSpy(&processor, &ActionProcessor::triggerCopyToClipboard);
	QSignalSpy openSignalSpy(&processor, &ActionProcessor::triggerOpenDirectory);
	QSignalSpy uploadSignalSpy(&processor, &ActionProcessor::triggerUpload);
	QSignalSpy pinSignalSpy(&processor, &ActionProcessor::triggerPinImage);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(saveSignalSpy.count(), 1);
    QCOMPARE(copySignalSpy.count(), 1);
    QCOMPARE(openSignalSpy.count(), 1);
    QCOMPARE(uploadSignalSpy.count(), 1);
    QCOMPARE(pinSignalSpy.count(), 1);
}

void ActionProcessorTests::CaptureFinished_Should_NotSendSignalsForNotSelectedActions()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsSaveEnabled(false);
	action.setIsCopyToClipboardEnabled(false);
	action.setIsOpenDirectoryEnabled(false);
	action.setIsUploadEnabled(false);
	action.setIsPinImageEnabled(false);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(false);
	QSignalSpy saveSignalSpy(&processor, &ActionProcessor::triggerSave);
	QSignalSpy copySignalSpy(&processor, &ActionProcessor::triggerCopyToClipboard);
	QSignalSpy openSignalSpy(&processor, &ActionProcessor::triggerOpenDirectory);
	QSignalSpy uploadSignalSpy(&processor, &ActionProcessor::triggerUpload);
	QSignalSpy pinSignalSpy(&processor, &ActionProcessor::triggerPinImage);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(saveSignalSpy.count(), 0);
    QCOMPARE(copySignalSpy.count(), 0);
    QCOMPARE(openSignalSpy.count(), 0);
    QCOMPARE(uploadSignalSpy.count(), 0);
    QCOMPARE(pinSignalSpy.count(), 0);
}

void ActionProcessorTests::Process_Should_MarkActionAsInProgress_When_CaptureEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	ActionProcessor processor;

	// act
	processor.process(action);

	// assert
    QCOMPARE(processor.isActionInProgress(), true);
}

void ActionProcessorTests::CaptureFinished_Should_MarkActionAsNotInProgress_When_CaptureEnabled()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	ActionProcessor processor;
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(processor.isActionInProgress(), false);
}

void ActionProcessorTests::CaptureFinished_Should_SendShowSignalWithMinimizedSetToTrue_When_HideSelected()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsHideMainWindowEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerShow);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(spy.count(), 1);
    QCOMPARE(qvariant_cast<bool>(spy.at(0).at(0)), true);
}

void ActionProcessorTests::CaptureFinished_Should_SendShowSignalWithMinimizedSetToFalse_When_HideNotSelected()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(true);
	action.setIsHideMainWindowEnabled(false);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerShow);
	processor.process(action);

	// act
	processor.captureFinished();

	// assert
    QCOMPARE(spy.count(), 1);
    QCOMPARE(qvariant_cast<bool>(spy.at(0).at(0)), false);
}

void ActionProcessorTests::Process_Should_NotSendShowSignal_When_HideNotSelectedAndCaptureNotSelected()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(false);
	action.setIsHideMainWindowEnabled(false);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerShow);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 0);
}

void ActionProcessorTests::Process_Should_SendShowSignalWithMinimizedSetToTrue_When_HideSelectedAndCaptureNotSelected()
{
	// arrange
	Action action;
	action.setIsCaptureEnabled(false);
	action.setIsHideMainWindowEnabled(true);
	ActionProcessor processor;
	processor.setPostProcessingEnabled(true);
	QSignalSpy spy(&processor, &ActionProcessor::triggerShow);

	// act
	processor.process(action);

	// assert
    QCOMPARE(spy.count(), 1);
    QCOMPARE(qvariant_cast<bool>(spy.at(0).at(0)), true);
}

TEST_MAIN(ActionProcessorTests)
