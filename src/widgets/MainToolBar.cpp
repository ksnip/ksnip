/*
 *  Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "MainToolBar.h"

MainToolBar::MainToolBar(
		const QList<CaptureModes> &captureModes,
		QAction* undoAction,
		QAction* redoAction,
		const QSharedPointer<IIconLoader> &iconLoader,
		const QSharedPointer<IScaledSizeProvider> &scaledSizeProvider) :
	QToolBar(),
	mSaveButton(new QToolButton(this)),
	mCopyButton(new QToolButton(this)),
	mCropButton(new QToolButton(this)),
	mUndoButton(new QToolButton(this)),
	mRedoButton(new QToolButton(this)),
	mCaptureModePicker(new CaptureModePicker(captureModes, iconLoader)),
	mDelayPicker(new CustomSpinBox(0,100)),
	mDelayLabel(new QLabel(this)),
	mNewCaptureAction(new QAction(this)),
	mSaveAction(new QAction(this)),
	mCopyAction(new QAction(this)),
	mCropAction(new QAction(this)),
	mUndoAction(undoAction),
	mRedoAction(redoAction)
{
    connect(mCaptureModePicker, &CaptureModePicker::captureModeSelected, this, &MainToolBar::captureModeSelected);

	setStyleSheet(QLatin1String("QToolBar { border: 0px }"));

    mNewCaptureAction->setText(tr("New"));
    mNewCaptureAction->setShortcut(QKeySequence::New);
    connect(mNewCaptureAction, &QAction::triggered, this, &MainToolBar::newCaptureTriggered);

    mSaveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mSaveButton->addAction(mSaveAction);
    mSaveButton->setDefaultAction(mSaveAction);

    mCopyButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mCopyButton->addAction(mCopyAction);
    mCopyButton->setDefaultAction(mCopyAction);

    mUndoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mUndoButton->addAction(mUndoAction);
    mUndoButton->setDefaultAction(mUndoAction);

    mRedoButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mRedoButton->addAction(mRedoAction);
    mRedoButton->setDefaultAction(mRedoAction);

    mCropButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mCropButton->addAction(mCropAction);
    mCropButton->setDefaultAction(mCropAction);

	auto clockIcon = iconLoader->loadForTheme(QLatin1String("clock.svg"));
	auto clockPixmap = clockIcon.pixmap(scaledSizeProvider->scaledSize(QSize(24, 24)));
	mDelayLabel->setPixmap(clockPixmap);
	mDelayLabel->setContentsMargins(0, 0, 2, 0);
	mDelayLabel->setToolTip(tr("Delay in seconds between triggering\n"
	                           "and capturing screenshot."));
    //: The small letter s stands for seconds.
    mDelayPicker->setSuffix(tr("s"));
	mDelayPicker->setFixedWidth(scaledSizeProvider->scaledWidth(55));
	mDelayPicker->setToolTip(mDelayLabel->toolTip());
    connect(mDelayPicker, &CustomSpinBox::valueChanged, this, &MainToolBar::captureDelayChanged);

    mSaveAction->setText(tr("Save"));
    mSaveAction->setToolTip(tr("Save Screen Capture to file system"));
	mSaveAction->setIcon(iconLoader->loadForTheme(QLatin1String("save.svg")));
    mSaveAction->setShortcut(QKeySequence::Save);
    connect(mSaveAction, &QAction::triggered, this, &MainToolBar::saveActionTriggered);

    mCopyAction->setText(tr("Copy"));
    mCopyAction->setToolTip(tr("Copy Screen Capture to clipboard"));
	mCopyAction->setIcon(iconLoader->loadForTheme(QLatin1String("copy.svg")));
    mCopyAction->setShortcut(QKeySequence::Copy);
    connect(mCopyAction, &QAction::triggered, this, &MainToolBar::copyActionTriggered);

    mUndoAction->setIcon(iconLoader->loadForTheme(QLatin1String("undo.svg")));;
    mUndoAction->setText(tr("Undo"));
    mUndoAction->setShortcut(QKeySequence::Undo);

    mRedoAction->setIcon(iconLoader->loadForTheme(QLatin1String("redo.svg")));
	mRedoAction->setText(tr("Redo"));
    mRedoAction->setShortcut(QKeySequence::Redo);

    mCropAction->setText(tr("Crop"));
    mCropAction->setToolTip(tr("Crop Screen Capture"));
    mCropAction->setIcon(iconLoader->loadForTheme(QLatin1String("crop.svg")));
    mCropAction->setShortcut(Qt::SHIFT + Qt::Key_C);
    connect(mCropAction, &QAction::triggered, this, &MainToolBar::cropActionTriggered);

    setWindowTitle(tr("Tools"));
    setFloatable(false);
    setMovable(false);
    setAllowedAreas(Qt::BottomToolBarArea);
    addWidget(mCaptureModePicker);
    addSeparator();
    addWidget(mSaveButton);
    addWidget(mCopyButton);
    addWidget(mUndoButton);
    addWidget(mRedoButton);
    addSeparator();
    addWidget(mCropButton);
    addSeparator();
    addWidget(mDelayLabel);
    addWidget(mDelayPicker);
    setFixedSize(sizeHint());
}

MainToolBar::~MainToolBar()
{
    delete mCaptureModePicker;
    delete mDelayPicker;
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

void MainToolBar::setCopyActionEnabled(bool enabled)
{
    mCopyAction->setEnabled(enabled);
}

void MainToolBar::setCropEnabled(bool enabled)
{
    mCropAction->setEnabled(enabled);
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
    return mCopyAction;
}

QAction *MainToolBar::cropAction() const
{
    return mCropAction;
}

QAction *MainToolBar::undoAction() const
{
    return mUndoAction;
}

QAction *MainToolBar::redoAction() const
{
    return mRedoAction;
}

QList<QAction *> MainToolBar::captureActions() const
{
	return mCaptureModePicker->captureActions();
}

void MainToolBar::setCollapsed(bool isCollapsed)
{
	isCollapsed ? setFixedSize(0, 0) : setFixedSize(sizeHint());
}

bool MainToolBar::isCollapsed() const
{
	return size() != sizeHint();
}
