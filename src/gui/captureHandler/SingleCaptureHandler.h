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
#include "src/gui/AbstractToastService.h"

using kImageAnnotator::KImageAnnotator;

class SingleCaptureHandler : public QObject, public ICaptureHandler
{
Q_OBJECT
public:
	explicit SingleCaptureHandler(KImageAnnotator *kImageAnnotator, AbstractToastService *toastService, QWidget *parent);
	~SingleCaptureHandler() override = default;
	void close() override;
	bool isSaved() const override;
	QString path() const override;
	void save(bool isInstant) override;
	void load(const CaptureDto &capture) override;

signals:
	void captureChanged() const override;
	void captureEmpty() const override;

private:
	KImageAnnotator *mKImageAnnotator;
	AbstractToastService *mToastService;
	QWidget *mParent;
};

#endif //KSNIP_SINGLECAPTUREHANDLER_H
