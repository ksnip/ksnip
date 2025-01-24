/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "OcrWindow.h"

OcrWindow::OcrWindow(const QPixmap &pixmap, const QString &title, const QSharedPointer<IPluginManager> &pluginManager) :
	mTextEdit(new QTextEdit(this)),
	mProcessIndicator(new ProcessIndicator(this)),
	mLayout(new QGridLayout(this))
{
	setWindowTitle(title);
	setGeometry(geometry().x(), geometry().y(), pixmap.size().width(), pixmap.size().height());

	mLayout->addWidget(mTextEdit, 0, 0);
	mLayout->addWidget(mProcessIndicator, 0, 0, Qt::AlignCenter);

	setProcessingVisible(true);

	auto ocrProcessingFuture = QtConcurrent::run([=]() { return this->process(pixmap, pluginManager); });

	connect(&mOcrProcessFutureWatcher, &QFutureWatcher<QString>::finished, this, &OcrWindow::processingFinished);
	mOcrProcessFutureWatcher.setFuture(ocrProcessingFuture);
}

void OcrWindow::closeEvent(QCloseEvent *event)
{
	emit closeRequest();
	QDialog::closeEvent(event);
}

QString OcrWindow::process(const QPixmap &pixmap, const QSharedPointer<IPluginManager> &pluginManager)
{
	auto ocrPlugin = pluginManager->get(PluginType::Ocr).objectCast<IPluginOcr>();
	return ocrPlugin->recognize(pixmap);
}

void OcrWindow::setProcessingVisible(bool isVisible)
{
	if(isVisible) {
		mProcessIndicator->start();
	} else {
		mProcessIndicator->stop();
	}

	mTextEdit->setVisible(!isVisible);
	mProcessIndicator->setVisible(isVisible);
}

void OcrWindow::processingFinished()
{
	setProcessingVisible(false);

	auto text = mOcrProcessFutureWatcher.future().result();
	mTextEdit->setText(text);
}
