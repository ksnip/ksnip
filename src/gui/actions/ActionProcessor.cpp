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
	mIsCaptureInProgress(false),
	mIsPostProcessingEnabled(false),
	mIsActionInProgress(false)
{

}

void ActionProcessor::process(const Action &action)
{
	mCurrentAction = action;
	mIsActionInProgress = true;

	if (mCurrentAction.isCaptureEnabled()) {
		preCaptureProcessing();
	} else {
		postCaptureProcessing();
	}
}

void ActionProcessor::setPostProcessingEnabled(bool enabled)
{
	mIsPostProcessingEnabled = enabled;
}

bool ActionProcessor::isActionInProgress() const
{
	return mIsActionInProgress;
}

void ActionProcessor::captureFinished()
{
	if(mIsCaptureInProgress) {
		mIsCaptureInProgress = false;
		postCaptureProcessing();
	}
}

void ActionProcessor::captureCanceled()
{
	mIsCaptureInProgress = false;
	mIsActionInProgress = false;
}

void ActionProcessor::preCaptureProcessing()
{
	mIsCaptureInProgress = true;
	emit triggerCapture(mCurrentAction.captureMode(), mCurrentAction.includeCursor(), mCurrentAction.captureDelay());
}

void ActionProcessor::postCaptureProcessing()
{
	if (!mIsPostProcessingEnabled && !mCurrentAction.isCaptureEnabled()) {
		mIsActionInProgress = false;
		return;
	}

	if (mCurrentAction.isSaveEnabled()) {
		emit triggerSave();
	}

	if (mCurrentAction.isCopyToClipboardEnabled()) {
		emit triggerCopyToClipboard();
	}

	if (mCurrentAction.isOpenDirectoryEnabled()) {
		emit triggerOpenDirectory();
	}

	if (mCurrentAction.isPinImageEnabled()) {
		emit triggerPinImage();
	}

	if (mCurrentAction.isUploadEnabled()) {
		emit triggerUpload();
	}

	if (mCurrentAction.isHideMainWindowEnabled()) {
		emit triggerShow(true);
	}

	if (!mCurrentAction.isHideMainWindowEnabled() && mCurrentAction.isCaptureEnabled()) {
		emit triggerShow(false);
	}

	mIsActionInProgress = false;
}
