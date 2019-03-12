/*
 *  Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "MainToolBar.h"

MainToolBar::MainToolBar(const QList<CaptureModes> &captureModes) : QToolBar(),
                                                                    mSaveButton(new QToolButton(this)),
                                                                    mCopyToClipboardButton(new QToolButton(this)),
                                                                    mCaptureModePicker(new CaptureModePicker(captureModes)),
                                                                    mDelayPicker(new CustomSpinBox(0,100)),
                                                                    mDelayLabel(new QLabel),
                                                                    mNewCaptureAction(new QAction(this)),
                                                                    mSaveAction(new QAction(this)),
                                                                    mCopyToClipboardAction(new QAction(this))
{
    connect(mCaptureModePicker, &CaptureModePicker::captureModeSelected, this, &MainToolBar::captureModeSelected);

	setStyleSheet("QToolBar { border: 0px }");

    mSaveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mSaveButton->addAction(mSaveAction);
    mSaveButton->setDefaultAction(mSaveAction);

    mCopyToClipboardButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mCopyToClipboardButton->addAction(mCopyToClipboardAction);
    mCopyToClipboardButton->setDefaultAction(mCopyToClipboardAction);

    mNewCaptureAction->setText(tr("New"));
    mNewCaptureAction->setShortcut(QKeySequence::New);
    connect(mNewCaptureAction, &QAction::triggered, this, &MainToolBar::newCaptureTriggered);

	auto clockPixmap = IconLoader::load(QStringLiteral("clock.svg")).pixmap(QSize(24, 24));
	mDelayLabel->setPixmap(clockPixmap);
	mDelayLabel->setContentsMargins(0, 0, 2, 0);
	mDelayLabel->setToolTip(tr("Delay in seconds between triggering\n"
	                           "and capturing screenshot."));
    mDelayPicker->setSuffix(tr("s"));
	mDelayPicker->setFixedWidth(55);
	mDelayPicker->setToolTip(mDelayLabel->toolTip());
    connect(mDelayPicker, &CustomSpinBox::valueChanged, this, &MainToolBar::captureDelayChanged);

    mSaveAction->setText(tr("Save"));
    mSaveAction->setToolTip(tr("Save Screen Capture to file system"));
	mSaveAction->setIcon(IconLoader::load(QStringLiteral("save.svg")));
    mSaveAction->setShortcut(QKeySequence::Save);
    connect(mSaveAction, &QAction::triggered, this, &MainToolBar::saveActionTriggered);

    mCopyToClipboardAction->setText(tr("Copy"));
    mCopyToClipboardAction->setToolTip(tr("Copy Screen Capture to clipboard"));
	mCopyToClipboardAction->setIcon(IconLoader::load(QStringLiteral("copyToClipboard.svg")));
    mCopyToClipboardAction->setShortcut(QKeySequence::Copy);
    connect(mCopyToClipboardAction, &QAction::triggered, this, &MainToolBar::copyToClipboardActionTriggered);

    setWindowTitle(tr("Tools"));
    setFloatable(false);
    setMovable(false);
    setAllowedAreas(Qt::BottomToolBarArea);
    addWidget(mCaptureModePicker);
    addSeparator();
    addWidget(mSaveButton);
    addWidget(mCopyToClipboardButton);
    addSeparator();
    addWidget(mDelayLabel);
    addWidget(mDelayPicker);
    setFixedSize(sizeHint());
}

MainToolBar::~MainToolBar()
{
    delete mSaveButton;
    delete mCopyToClipboardButton;
    delete mCaptureModePicker;
    delete mDelayPicker;
    delete mNewCaptureAction;
    delete mSaveAction;
    delete mCopyToClipboardAction;
}

void MainToolBar::selectCaptureMode(CaptureModes captureModes)
{
    mCaptureModePicker->setCaptureMode(captureModes);
}

void MainToolBar::setCaptureDelay(int delay)
{
    mDelayPicker->setValue(delay);
}

void MainToolBar::newCaptureTriggered()
{
    mCaptureModePicker->trigger();
}

void MainToolBar::setSaveActionEnabled(bool enabled)
{
    mSaveAction->setEnabled(enabled);
}

void MainToolBar::setCopyToClipboardActionEnabled(bool enabled)
{
    mCopyToClipboardAction->setEnabled(enabled);
}

QAction *MainToolBar::newCaptureAction() const
{
    return mNewCaptureAction;
}

QAction *MainToolBar::saveAction() const
{
    return mSaveAction;
}

QAction *MainToolBar::copyToClipboardAction() const
{
    return mCopyToClipboardAction;
}
