/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ContextMenu.h"

ContextMenu::ContextMenu() :
    mArrangeMenu(nullptr),
    mBringForwardAction(nullptr),
    mBringToFrontAction(nullptr),
    mSendBackwardAction(nullptr),
    mSendToBackAction(nullptr),
    mEraseAction(nullptr),
    mCopyAction(nullptr),
    mPastAction(nullptr),
    mCancelAction(nullptr)
{
}

void ContextMenu::exec(const QPointF& pos)
{
    auto selectedAction = QMenu::exec(pos.toPoint());

    if (mBringForwardAction && selectedAction == mBringForwardAction) {
        bringForwardTriggered();
    } else if (mBringToFrontAction && selectedAction == mBringToFrontAction) {
        bringToFrontTriggered();
    } else if (mSendBackwardAction && selectedAction == mSendBackwardAction) {
        sendBackwardTriggered();
    } else if (mSendToBackAction && selectedAction == mSendToBackAction) {
        sendToBackTriggered();
    } else if (mEraseAction && selectedAction == mEraseAction) {
        eraseTriggered();
    } else if (mCopyAction && selectedAction == mCopyAction) {
        copyTriggered(pos);
    } else if (mPastAction && selectedAction == mPastAction) {
        pastTriggered(pos);
    }
}

void ContextMenu::addArrangeMenu(bool enabled)
{
    if (!mArrangeMenu) {
        mArrangeMenu = addMenu(tr("Arrange"));
        mBringForwardAction = mArrangeMenu->addAction(tr("Bring Forward"));
        mBringToFrontAction = mArrangeMenu->addAction(tr("Bring to Front"));
        mSendBackwardAction = mArrangeMenu->addAction(tr("Send Backward"));
        mSendToBackAction = mArrangeMenu->addAction(tr("Send to Back"));
        setArrangeMenuEnabled(enabled);
    }
}

void ContextMenu::addCopyAction(bool enabled)
{
    if (!mCopyAction) {
        mCopyAction = addAction(tr("Copy"));
        setCopyActionEnabled(enabled);
    }
}

void ContextMenu::addPastAction(bool enabled)
{
    if (!mPastAction) {
        mPastAction = addAction(tr("Past"));
        setPastActionEnabled(enabled);
    }
}

void ContextMenu::addEraseAction(bool enabled)
{
    if (!mEraseAction) {
        mEraseAction = addAction(tr("Erase"));
        setEraseActionEnabled(enabled);
    }
}

void ContextMenu::addCancelAction()
{
    if (!mCancelAction) {
        mCancelAction = addAction(tr("Cancel"));
    }
}

void ContextMenu::setArrangeMenuEnabled(bool enabled)
{
    if (mArrangeMenu) {
        mArrangeMenu->setEnabled(enabled);
    }
}

void ContextMenu::setCopyActionEnabled(bool enabled)
{
    if (mCopyAction) {
        mCopyAction->setEnabled(enabled);
    }
}

void ContextMenu::setEraseActionEnabled(bool enabled)
{
    if (mEraseAction) {
        mEraseAction->setEnabled(enabled);
    }
}

void ContextMenu::setPastActionEnabled(bool enabled)
{
    if (mPastAction) {
        mPastAction->setEnabled(enabled);
    }
}

