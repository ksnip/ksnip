/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "UpdateWatermarkOperation.h"

UpdateWatermarkOperation::UpdateWatermarkOperation(QWidget *parent)
{
	mParent = parent;
}

bool UpdateWatermarkOperation::execute()
{
	auto title = tr("Select Image");
	auto filter = tr("Images") + QStringLiteral(" (*.png *.gif *.jpg);;") + tr("All Files") + QStringLiteral("(*)");
	QFileDialog dialog(mParent, title, QString(), filter);
	dialog.setAcceptMode(QFileDialog::AcceptOpen);

	if (dialog.exec() != QDialog::Accepted) {
		return false;
	}

	auto pathToImage = dialog.selectedFiles().first();
	return mImageLoader.save(QPixmap(pathToImage));
}
