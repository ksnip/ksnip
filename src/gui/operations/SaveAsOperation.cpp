/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "SaveAsOperation.h"

SaveAsOperation::SaveAsOperation(QWidget* parent, const QImage &image)
{
    Q_ASSERT(parent != nullptr);

    mParent = parent;
    mImage = image;
}

bool SaveAsOperation::execute()
{
    auto path = mSavePathProvider.savePath();

    auto title = QObject::tr("Save As");
    auto filter = QObject::tr("Images") + QStringLiteral(" (*.png *.gif *.jpg);;") + QObject::tr("All Files") + QStringLiteral("(*)");
    QFileDialog saveDialog(mParent, title, path, filter);
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);

    if (saveDialog.exec() != QDialog::Accepted) {
        return false;
    }

    path = saveDialog.selectedFiles().first();

    return mImageSaver.save(mImage, path);
}
