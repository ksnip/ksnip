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

#ifndef KSNIP_MULTICAPTUREHANDLER_H
#define KSNIP_MULTICAPTUREHANDLER_H

#include <kImageAnnotator/KImageAnnotator.h>

#include "src/gui/captureHandler/ICaptureHandler.h"
#include "src/gui/captureHandler/CaptureTabStateHandler.h"
#include "src/gui/operations/CanDiscardOperation.h"
#include "src/gui/operations/SaveOperation.h"
#include "src/gui/IToastService.h"
#include "src/common/provider/NewCaptureNameProvider.h"
#include "src/common/provider/PathFromCaptureProvider.h"

using kImageAnnotator::KImageAnnotator;

class MultiCaptureHandler : public QObject, public ICaptureHandler
{
Q_OBJECT
public:
	explicit MultiCaptureHandler(KImageAnnotator *kImageAnnotator, IToastService *toastService, QWidget *parent);
	~MultiCaptureHandler() override;
	void close() override;
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
	CaptureTabStateHandler *mTabStateHandler;
	IToastService *mToastService;
	QWidget *mParent;
	ICaptureChangeListener *mCaptureChangeListener;
	NewCaptureNameProvider mNewCaptureNameProvider;
	PathFromCaptureProvider mPathFromCaptureProvider;

	bool discardChanges(int index);
	void removeTab(int currentTabIndex);

private slots:
	void tabCloseRequested(int index);
	void saveAt(int index, bool isInstant);
	void captureChanged();
	void captureEmpty();
};

#endif //KSNIP_MULTICAPTUREHANDLER_H
