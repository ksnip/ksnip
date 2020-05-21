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

#include "SingleCaptureHandler.h"

SingleCaptureHandler::SingleCaptureHandler(KImageAnnotator *kImageAnnotator, IToastService *toastService, QWidget *parent) :
	mKImageAnnotator(kImageAnnotator),
	mToastService(toastService),
	mParent(parent),
	mCaptureChangeListener(nullptr)
{

}

void SingleCaptureHandler::close()
{

}

bool SingleCaptureHandler::isSaved() const
{
	return false;
}

QString SingleCaptureHandler::path() const
{
	return QString();
}

void SingleCaptureHandler::saveAs()
{

}

void SingleCaptureHandler::save()
{

}

void SingleCaptureHandler::load(const CaptureDto &capture)
{

}

QImage SingleCaptureHandler::image() const
{
	return mKImageAnnotator->image();
}

void SingleCaptureHandler::insertImageItem(const QPointF &pos, const QPixmap &pixmap)
{
	mKImageAnnotator->insertImageItem(pos, pixmap);
}

void SingleCaptureHandler::addListener(ICaptureChangeListener *captureChangeListener)
{
	mCaptureChangeListener = captureChangeListener;
}
