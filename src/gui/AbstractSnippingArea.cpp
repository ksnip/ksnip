/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#include "AbstractSnippingArea.h"

AbstractSnippingArea::AbstractSnippingArea()
    : mMouseIsDown(false),
      mCursorFactory(new CursorFactory()),
      mConfig(KsnipConfig::instance()),
      mBackground(nullptr)
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    QScopedPointer<QCursor> cursor(mCursorFactory->createSnippingCursor());
    QWidget::setCursor(*cursor);
}

AbstractSnippingArea::~AbstractSnippingArea()
{
    delete mCursorFactory;
    delete mBackground;
}

void AbstractSnippingArea::showWithoutBackground()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    clearBackgroundImage();
    showSnippingArea();
}

void AbstractSnippingArea::showWithBackground(const QPixmap &background)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setBackgroundImage(background);
    showSnippingArea();
}

QRect AbstractSnippingArea::selectedRectArea() const
{
    auto topLeft = mapToGlobal(mCaptureArea.topLeft());
    auto bottomRight = mapToGlobal(mCaptureArea.bottomRight());
    return {topLeft, bottomRight};
}

void AbstractSnippingArea::showSnippingArea()
{
    init();
    setFullScreen();
    QApplication::setActiveWindow(this);
    grabKeyboard(); // Issue #57
}

void AbstractSnippingArea::setBackgroundImage(const QPixmap &background)
{
    clearBackgroundImage();
    mBackground = new QPixmap(background);
}

void AbstractSnippingArea::clearBackgroundImage()
{
    delete mBackground;
}

void AbstractSnippingArea::init()
{
    mCursorRulerEnabled = mConfig->cursorRulerEnabled();
    mCursorInfoEnabled = mConfig->cursorInfoEnabled();
    setMouseTracking(mCursorRulerEnabled || mCursorInfoEnabled);
    mMouseIsDown = false;
}

void AbstractSnippingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseDownPosition = event->pos();
    updateCapturedArea(mMouseDownPosition, event->pos());
    mMouseIsDown = true;
}

void AbstractSnippingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseIsDown = false;
    emit finished();
    closeSnippingArea();
}

bool AbstractSnippingArea::closeSnippingArea()
{
    releaseKeyboard(); // Issue #57
    return QWidget::close();
}

void AbstractSnippingArea::mouseMoveEvent(QMouseEvent *event)
{
    if (mMouseIsDown) {
        updateCapturedArea(mMouseDownPosition, event->pos());
    }
    update();
    QWidget::mouseMoveEvent(event);
}

void AbstractSnippingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (mBackground != nullptr) {
        painter.drawPixmap(geometry(), *mBackground);
    }

    if (mMouseIsDown) {
        painter.setClipRegion(QRegion(geometry()).subtracted(QRegion(mCaptureArea)));
    }

    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRect(geometry());

    if (mCursorRulerEnabled && !mMouseIsDown) {
        drawCursorRuler(painter);
    }

    if (mCursorInfoEnabled) {
        if (mMouseIsDown) {
            drawCursorSizeInfo(painter);
        } else {
            drawCursorPositionInfo(painter);
        }
    }

    if (mMouseIsDown) {
        painter.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawRect(mCaptureArea);
    }

    QWidget::paintEvent(event);
}

void AbstractSnippingArea::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit canceled();
        closeSnippingArea();
    }
    QWidget::keyPressEvent(event);
}

void AbstractSnippingArea::updateCapturedArea(const QPoint &point1, const QPoint &point2)
{
    mCaptureArea = QRect(point1, point2).normalized();
}

QString AbstractSnippingArea::createPositionInfoText(int number1, int number2) const
{
    return QString::number(number1) + QStringLiteral(", ") + QString::number(number2);
}

void AbstractSnippingArea::drawCursorRuler(QPainter &painter) const
{
    auto pos = getMousePosition();
    int offset = 4;
    QLine midToTop(QPoint(pos.x(), pos.y() - offset), QPoint(pos.x(), geometry().top()));
    QLine midToRight(QPoint(pos.x() + offset, pos.y()), QPoint(geometry().right(), pos.y()));
    QLine midToBottom(QPoint(pos.x(), pos.y() + offset), QPoint(pos.x(), geometry().bottom()));
    QLine midToLeft(QPoint(pos.x() - offset, pos.y()), QPoint(geometry().left(), pos.y()));

    painter.setPen(QPen(Qt::red, 1, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin));
    painter.drawLine(midToTop);
    painter.drawLine(midToRight);
    painter.drawLine(midToBottom);
    painter.drawLine(midToLeft);
}

void AbstractSnippingArea::drawCursorPositionInfo(QPainter &painter) const
{
    QPoint textOffset(10, 8);
    auto pos = getMousePosition();
    auto text = createPositionInfoText(pos.x(), pos.y());
    auto textBoundingRect = getTextBounding(painter, text);
    textBoundingRect.moveTopLeft(pos + textOffset);
    auto boxRect = textBoundingRect;
    textBoundingRect.adjust(0, 0, 7, 4);
    boxRect.adjust(-3, 0, 5, 0);

    painter.setPen(QPen(Qt::red, 1));
    painter.setBrush(QColor(0, 0, 0, 200));

    painter.drawRoundedRect(boxRect, 2, 2);
    painter.drawText(textBoundingRect, text);
}

void AbstractSnippingArea::drawCursorSizeInfo(QPainter &painter) const
{
    painter.setPen(QPen(Qt::red, 1));
    drawCursorWidthInfo(painter);
    drawCursorHeightInfo(painter);
}

void AbstractSnippingArea::drawCursorWidthInfo(QPainter &painter) const
{
    QPoint lineOffset(0, -10);
    QPoint lineEndOffset(0, -3);
    QPoint widthTextOffset(0, -8);
    QLine lineEndLeft(QPoint(0, 0), QPoint(0, 6));
    QLine lineEndRight(lineEndLeft);
    QLine line(mCaptureArea.topLeft(), mCaptureArea.topRight());
    auto widthText = QString::number(mCaptureArea.width());

    line.translate(lineOffset);
    lineEndLeft.translate(line.p1() + lineEndOffset);
    lineEndRight.translate(line.p2() + lineEndOffset);

    auto lineCenter = MathHelper::getLineCenter(line);
    auto widthTextBoundingRect = getTextBounding(painter, widthText);
    widthTextBoundingRect.moveCenter(lineCenter + widthTextOffset);
    widthTextBoundingRect.adjust(0, 0, 2, 2);

    painter.drawLine(line);
    painter.drawLine(lineEndLeft);
    painter.drawLine(lineEndRight);
    painter.drawText(widthTextBoundingRect, widthText);
}

void AbstractSnippingArea::drawCursorHeightInfo(QPainter &painter) const
{
    QPoint lineOffset(-10, 0);
    QPoint lineEndOffset(-3, 0);
    QPoint heightTextOffset(-5, 0);
    QLine lineEndTop(QPoint(0, 0), QPoint(6, 0));
    QLine lineEndBottom(lineEndTop);
    QLine line(mCaptureArea.topLeft(), mCaptureArea.bottomLeft());
    auto heightText = QString::number(mCaptureArea.height());

    line.translate(lineOffset);
    lineEndTop.translate(line.p1() + lineEndOffset);
    lineEndBottom.translate(line.p2() + lineEndOffset);

    auto lineCenter = MathHelper::getLineCenter(line);
    auto heightTextBoundingRect = getTextBounding(painter, heightText);
    heightTextOffset.setX(heightTextOffset.x() - (heightTextBoundingRect.width() / 2));
    heightTextBoundingRect.moveCenter(lineCenter + heightTextOffset);

    painter.drawLine(line);
    painter.drawLine(lineEndTop);
    painter.drawLine(lineEndBottom);
    painter.drawText(heightTextBoundingRect, heightText);
}

QRect AbstractSnippingArea::getTextBounding(const QPainter &painter, const QString &text) const
{
    auto fontMetric = painter.fontMetrics();
    return fontMetric.boundingRect(text);
}
