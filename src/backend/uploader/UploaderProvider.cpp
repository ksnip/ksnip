/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "UploaderProvider.h"

UploaderProvider::UploaderProvider() :
	mConfig(KsnipConfigProvider::instance()),
	mImgurUploader(nullptr),
	mScriptUploader(nullptr)
{
}

UploaderProvider::~UploaderProvider()
{
	delete mImgurUploader;
	delete mScriptUploader;
}

IUploader* UploaderProvider::get()
{
	switch (mConfig->uploaderType()) {
		case UploaderType::Imgur:
			return getImgurUploader();
		case UploaderType::Script:
			return getScriptUploader();
		default:
			return getImgurUploader();
	}
}

IUploader* UploaderProvider::getScriptUploader()
{
	if(mScriptUploader == nullptr) {
		mScriptUploader = new ScriptUploader;
		connectSignals(mScriptUploader);
	}
	return mScriptUploader;
}

IUploader* UploaderProvider::getImgurUploader()
{
	if(mImgurUploader == nullptr) {
		mImgurUploader = new ImgurUploader;
		connectSignals(mImgurUploader);
	}
	return mImgurUploader;
}

void UploaderProvider::connectSignals(IUploader *uploader)
{ 
	connect(dynamic_cast<QObject*>(uploader), SIGNAL(finished(UploadResult)), this, SIGNAL(finished(UploadResult)));
}


