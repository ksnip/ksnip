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

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QPointF>

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    ContextMenu();
    void exec(const QPointF &pos);
    void addArrangeMenu(bool enabled = true);
    void addEraseAction(bool enabled = true);
    void addCopyAction(bool enabled = true);
    void addPastAction(bool enabled = true);
    void addCancelAction();
    void setArrangeMenuEnabled(bool enabled);
    void setEraseActionEnabled(bool enabled);
    void setCopyActionEnabled(bool enabled);
    void setPastActionEnabled(bool enabled);

signals:
    void bringForwardTriggered();
    void bringToFrontTriggered();
    void sendBackwardTriggered();
    void sendToBackTriggered();
    void eraseTriggered();
    void copyTriggered(const QPointF &);
    void pastTriggered(const QPointF &);

private:
    QMenu   *mArrangeMenu;
    QAction *mBringForwardAction;
    QAction *mBringToFrontAction;
    QAction *mSendBackwardAction;
    QAction *mSendToBackAction;
    QAction *mEraseAction;
    QAction *mCopyAction;
    QAction *mPastAction;
    QAction *mCancelAction;
};

#endif // CONTEXTMENU_H
