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

#ifndef KSNIP_ACTIONPROCESSOR_H
#define KSNIP_ACTIONPROCESSOR_H

#include <QObject>

#include "Action.h"

class ActionProcessor : public QObject
{
	Q_OBJECT

public:
	ActionProcessor();
	~ActionProcessor() override = default;
	void process(const Action &action);
	void setPostProcessingEnabled(bool enabled);

signals:
	void triggerCapture(CaptureModes mode, bool includeCursor, int delay) const;
	void triggerPinImage() const;
	void triggerCopyToClipboard() const;
	void triggerSave() const;
	void triggerUpload() const;
	void triggerOpenDirectory() const;

public slots:
	void captureFinished();
	void captureCanceled();

private:
	bool mCaptureInProgress;
	bool mPostProcessingEnabled;
	Action mCurrentAction;

	void preCaptureProcessing();
	void postCaptureProcessing();
};


#endif //KSNIP_ACTIONPROCESSOR_H
