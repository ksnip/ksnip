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

#ifndef KSNIP_SINGLECAPTUREHANDLER_H
#define KSNIP_SINGLECAPTUREHANDLER_H

#include <kImageAnnotator/KImageAnnotator.h>

#include "src/gui/captureHandler/ICaptureHandler.h"
#include "src/gui/operations/CanDiscardOperation.h"
#include "src/gui/IToastService.h"

using kImageAnnotator::KImageAnnotator;

class SingleCaptureHandler : public QObject, public ICaptureHandler
{
Q_OBJECT
public:
	explicit SingleCaptureHandler(KImageAnnotator *kImageAnnotator, IToastService *toastService, QWidget *parent);
	~SingleCaptureHandler() override = default;
	bool canClose() override;
	bool isSaved() const override;
	QString path() const override;
	void saveAs() override;
	void save() override;
	void load(const CaptureDto &capture) override;
	QImage image() const override;
	void insertImageItem(const QPointF &pos, const QPixmap &pixmap) override;
	void addListener(ICaptureChangeListener *captureChangeListener) override;

private:
	KImageAnnotator *mKImageAnnotator;
	IToastService *mToastService;
	QWidget *mParent;
	ICaptureChangeListener *mCaptureChangeListener;
	bool mIsSaved;
	QString mPath;

	bool discardChanges();
	void resetStats();

private slots:
	void captureChanged();
	void innerSave(bool isInstant);
	void markUnsaved();
};

#endif //KSNIP_SINGLECAPTUREHANDLER_H
