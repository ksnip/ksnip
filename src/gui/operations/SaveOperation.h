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

#ifndef KSNIP_SAVEOPERATION_H
#define KSNIP_SAVEOPERATION_H

#include "src/backend/config/KsnipConfig.h"
#include "src/backend/config/SavePathProvider.h"
#include "src/backend/ImageSaver.h"

class SaveOperation
{
public:
    SaveOperation(const QImage &image);
    ~SaveOperation() = default;
    bool execute();

private:
    QImage mImage;
    SavePathProvider mSavePathProvider;
    ImageSaver mImageSaver;
};

#endif //KSNIP_SAVEOPERATION_H
