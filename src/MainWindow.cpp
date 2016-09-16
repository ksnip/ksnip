/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
#include <QtGui>

#include <iostream>

#include "MainWindow.h"

MainWindow::MainWindow() : QWidget(),
    mPaintToolMenu(new QMenu),
    mNewCaptureMenu(new QMenu),
    mToolBar(new QToolBar),
    mNewCaptureButton(new CustomToolButton),
    mSaveButton(new QToolButton),
    mCopyToClipboardButton(new QToolButton),
    mPaintToolButton(new CustomToolButton), 
    mMenuBar(new QMenuBar),
    mNewRectAreaCaptureAction(new QAction(this)),
    mNewFullScreenCaptureAction(new QAction(this)),
    mNewCurrentScreenCaptureAction(new QAction(this)),
    mNewActiveWindowCaptureAction(new QAction(this)),
    mPenAction(new QAction(this)),
    mMarkerAction(new QAction(this)),
    mEraseAction(new QAction(this)),
    mCaptureScene(new PaintArea()),
    mCaptureView(new QGraphicsView(mCaptureScene)),
    mWindowLayout(new QVBoxLayout),
    mSnippingArea(new SnippingArea(this))
{
    createToolButtons();
    createToolBar();
    createMenuBar();
    createLayout();

    // Disable frame around the image and hide it as on startup it's empty and enable Antialiasing
    mCaptureView->setFrameStyle(0);
    mCaptureView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    mCaptureView->hide();

    // Setup the clipboard that we will use to copy images when required.
    mClipboard = QApplication::clipboard();

    // Setup application properties
    setWindowTitle("ksnip");
    setWindowIcon(QIcon::fromTheme("preferences-desktop-screensaver"));

    // Create a connection with other widget elements
    connect(mSnippingArea, SIGNAL(areaSelected(QRect)), this, SLOT(areaSelected(QRect)));
    connect(mCaptureScene, SIGNAL(imageChanged()), this, SLOT(imageChanged()));
  
    // Setup application properties that are required for saving settings
    QCoreApplication::setOrganizationName("ksnip");
    QCoreApplication::setOrganizationDomain("ksnip.local");
    QCoreApplication::setApplicationName("ksnip");
    
    // Temporary setting capture delay to 4000 for testing purpose
    setCaptureDelay(300);
    
    loadSettings();
}

void MainWindow::show(QPixmap screenshot)
{
    setWindowState(Qt::WindowActive);
    setWindowOpacity(1.0);

    if (screenshot.isNull()) {
        qCritical("PaintWindow::showWindow: No image provided to but it was expected.");
        return show();
    }

    mCaptureScene->loadCapture(screenshot);
    
    if (mCaptureScene->getAreaSize().width() > getCurrectScreenGeometry().width() ||
        mCaptureScene->getAreaSize().height() > getCurrectScreenGeometry().height()) {
        setWindowState(Qt::WindowMaximized);
    }

    else {
        resize(mCaptureScene->getAreaSize() + QSize(100, 150) );
    }

    mCaptureView->show();
    mCaptureView->setFocus();
    setSaveAble(true);

    QWidget::show();
}

void MainWindow::show()
{
    setWindowState(Qt::WindowActive);
    mCaptureView->hide();
    setSaveAble(false);
    QWidget::show();
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    saveSetting("MainWindow/Position", pos());
    QWidget::moveEvent(event);
}


void MainWindow::newRectAreaCaptureClicked()
{
    setWindowOpacity(0.0);
    delay(captureDelay);
    mSnippingArea->show();
}

void MainWindow::newCurrentScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    delay(captureDelay);
    show(grabScreen(getCurrectScreenGeometry()));
}

void MainWindow::mNewFullScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    delay(captureDelay);
    show(grabScreen(getFullScreenGeometry()));
}

void MainWindow::newWindowCaptureClicked()
{

}

void MainWindow::saveCaptureClicked()
{
    QString format = "png";
    QString initialPath = QDir::homePath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                       initialPath,
                       tr("%1 Files (*.%2);;All Files (*)")
                       .arg(format.toUpper())
                       .arg(format));

    if (fileName.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Unable to save"));
        msgBox.setText(tr("Filename is empty, unable to save the image."));
        msgBox.exec();
        return;
    }

    if (!mCaptureScene->exportAsImage().save(fileName)) {
        qCritical("PaintWindow::saveCaptureClicked: Failed to save image, something went wrong.");
        return;
    }

    setSaveAble(false);
}

void MainWindow::copyToClipboardClicked()
{
    mClipboard->setImage(mCaptureScene->exportAsImage());
}

void MainWindow::penClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Pen);
    saveSetting("MainWindow/PaintMode", PaintArea::Pen);
}

void MainWindow::markerClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Marker);
    saveSetting("MainWindow/PaintMode", PaintArea::Marker);
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Erase);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        mSnippingArea->hide();
        setWindowOpacity(1.0);
    }

    QWidget::keyPressEvent(event);
}

void MainWindow::areaSelected(QRect rect)
{
    delay(captureDelay);
    show(grabScreen(rect));
}

/*
 * Should be called when ever the paintArea was changed, like new
 * drawing and similar
 */
void MainWindow::imageChanged()
{
    setSaveAble(true);
}

void MainWindow::setCaptureDelay(int ms)
{
    if (ms < 300)
        captureDelay = 300;
    else
        captureDelay = ms;
}


QPixmap MainWindow::grabScreen(QRect rect)
{
    QPixmap screenshot;
    screenshot = QPixmap();
    screenshot = QPixmap::grabWindow(QApplication::desktop()->winId(), 
                                     rect.topLeft().x(),
                                     rect.topLeft().y(),
                                     rect.width(),
                                     rect.height());
    return screenshot;
}

void MainWindow::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/*
 * Sets the state of the widget when the image was changed or save, depending
 * on the provided boolean value. If true, the save button is enabled and
 * the title changed.
 */
void MainWindow::setSaveAble(bool saveAble)
{
    if (saveAble) {
        mSaveButton->setEnabled(true);
        setWindowTitle("*ksnip - " + tr("Unsaved"));
    } else {
        mSaveButton->setEnabled(false);
        setWindowTitle("ksnip");
    }
}

void MainWindow::createToolButtons()
{
    // Create tool button for selecting new capture mode
    mNewRectAreaCaptureAction->setIconText(tr("Rectangular Area"));
    mNewRectAreaCaptureAction->setIcon(QIcon::fromTheme("tool_rectangle"));
    connect(mNewRectAreaCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newRectAreaCaptureClicked()));

    mNewCurrentScreenCaptureAction->setIconText(tr("Current Screen"));
    mNewCurrentScreenCaptureAction->setIcon(QIcon::fromTheme("view-fullscreen"));
    connect(mNewCurrentScreenCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newCurrentScreenCaptureClicked()));

    mNewFullScreenCaptureAction->setIconText(tr("Full Screen (All Monitors)"));
    mNewFullScreenCaptureAction->setIcon(QIcon::fromTheme("view-fullscreen"));
    connect(mNewFullScreenCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(mNewFullScreenCaptureClicked()));

    mNewActiveWindowCaptureAction->setIconText(tr("Active Window"));
    mNewActiveWindowCaptureAction->setIcon(QIcon::fromTheme("window"));
    connect(mNewActiveWindowCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newWindowCaptureClicked()));

    mNewCaptureMenu->addAction(mNewRectAreaCaptureAction);
    mNewCaptureMenu->addAction(mNewFullScreenCaptureAction);
    mNewCaptureMenu->addAction(mNewCurrentScreenCaptureAction);
    mNewCaptureMenu->addAction(mNewActiveWindowCaptureAction);

    mNewCaptureButton->setMenu(mNewCaptureMenu);
    mNewCaptureButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mNewCaptureButton->setDefaultAction(mNewRectAreaCaptureAction);
    mNewCaptureButton->setButtonText(tr("New"));

    // Create save tool button
    mSaveButton->setText(tr("Save"));
    mSaveButton->setToolTip("Save Screen Capture to file system");
    mSaveButton->setIcon(QIcon::fromTheme("document-save-as"));
    mSaveButton->connect(mSaveButton, SIGNAL(clicked()), this, SLOT(saveCaptureClicked()));
    mSaveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mSaveButton->setEnabled(false);
    mSaveButton->sizeHint();

    // Create copy to clipboard tool button
    mCopyToClipboardButton->setText(tr("Copy"));
    mCopyToClipboardButton->setToolTip("Copy Screen Capture to clipboard");
    mCopyToClipboardButton->setIcon(QIcon::fromTheme("edit-copy"));
    mCopyToClipboardButton->connect(mCopyToClipboardButton, SIGNAL(clicked()), this,
                                    SLOT(copyToClipboardClicked()));
    mCopyToClipboardButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // Create tool button for selecting paint tool
    mPenAction->setText(tr("Pen"));
    mPenAction->setIcon(QIcon::fromTheme("tool_pen"));
    connect(mPenAction, SIGNAL(triggered()), this, SLOT(penClicked()));

    mMarkerAction->setText(tr("Marker"));
    mMarkerAction->setIcon(QIcon::fromTheme("draw-brush"));
    connect(mMarkerAction, SIGNAL(triggered()), this, SLOT(markerClicked()));

    mEraseAction->setText(tr("Erase"));
    mEraseAction->setIcon(QIcon::fromTheme("draw-eraser"));
    connect(mEraseAction, SIGNAL(triggered()), this, SLOT(eraseClicked()));

    mPaintToolMenu->addAction(mPenAction);
    mPaintToolMenu->addAction(mMarkerAction);
    mPaintToolMenu->addAction(mEraseAction);

    mPaintToolButton->setMenu(mPaintToolMenu);
    mPaintToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::createToolBar()
{
    mToolBar->addWidget(mNewCaptureButton);
    mToolBar->addSeparator();
    mToolBar->addWidget(mSaveButton);
    mToolBar->addWidget(mCopyToClipboardButton);
    mToolBar->addSeparator();
    mToolBar->addWidget(mPaintToolButton);
}

void MainWindow::createLayout()
{
    mWindowLayout->addWidget(mMenuBar);
    mWindowLayout->addWidget(mToolBar);
    mWindowLayout->addWidget(mCaptureView);
    mWindowLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mWindowLayout->setContentsMargins(0,0,0,0);
    setLayout(mWindowLayout);
}

void MainWindow::createMenuBar()
{
    mMenuBar->addMenu(tr("File"));
    mMenuBar->addMenu(tr("&Edit"));
    mMenuBar->addMenu(tr("&Settings"));
    mMenuBar->addMenu(tr("&Help"));
}

void MainWindow::saveSetting(QString key, QVariant value)
{
    QSettings settings;
    settings.setValue(key, value);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    
    move(settings.value("MainWindow/Position").value<QPoint>());

    if (settings.value("MainWindow/PaintMode").toInt() == PaintArea::Marker) {    
        mCaptureScene->setPaintMode(PaintArea::Marker);
        mPaintToolButton->setDefaultAction(mMarkerAction);
    } else {
        mCaptureScene->setPaintMode(PaintArea::Pen);
        mPaintToolButton->setDefaultAction(mPenAction);
    }
}

QRect MainWindow::getCurrectScreenGeometry()
{
    return QApplication::desktop()->screenGeometry();
}

QRect MainWindow::getFullScreenGeometry()
{
    return QApplication::desktop()->screen()->geometry();
}







