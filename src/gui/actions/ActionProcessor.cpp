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

#include "ActionProcessor.h"

ActionProcessor::ActionProcessor() :
	mCurrentAction(nullptr),
	mCaptureInProgress(false)
{

}

void ActionProcessor::process(const Action *action)
{
	Q_ASSERT(action != nullptr);

	mCurrentAction = action;
	if (mCurrentAction->isCaptureEnabled()) {
		preCaptureProcessing();
	} else {
		postCaptureProcessing();
	}
}

void ActionProcessor::captureFinished()
{
	if(mCaptureInProgress) {
		mCaptureInProgress = false;
		postCaptureProcessing();
	}
}

void ActionProcessor::captureCanceled()
{
	mCaptureInProgress = false;
}

void ActionProcessor::preCaptureProcessing()
{
	Q_ASSERT(mCurrentAction != nullptr);

	qDebug("Preprocess");

	mCaptureInProgress = true;
	emit triggerCapture(mCurrentAction->captureMode(), mCurrentAction->includeCursor(), mCurrentAction->captureDelay());
}

void ActionProcessor::postCaptureProcessing()
{
	Q_ASSERT(mCurrentAction != nullptr);

	qDebug("Postprocess");

	if (mCurrentAction->isSaveEnabled()) {
		qDebug("Save");
		emit triggerSave();
	}

	if (mCurrentAction->isCopyToClipboardEnabled()) {
		qDebug("Copy");
		emit triggerCopyToClipboard();
	}

	if (mCurrentAction->isOpenDirectoryEnabled()) {
		qDebug("Open");
		emit triggerOpenDirectory();
	}

	if (mCurrentAction->isPinImageEnabled()) {
		qDebug("Pin");
		emit triggerPinImage();
	}

	if (mCurrentAction->isUploadEnabled()) {
		qDebug("Upload");
		emit triggerUpload();
	}
}
