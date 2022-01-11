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

#include <QAbstractButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

#include "SettingsFilter.h"

void SettingsFilter::filterSettings(const QString &filterString,
									QTreeWidget *treeWidget,
									QStackedLayout *stackedLayout,
									QList<QTreeWidgetItem *> &navigatorItems) const
{
	if (filterString.isEmpty()) {
		foreach (auto navigatorItem, navigatorItems) {
			navigatorItem->setHidden(false);
		}
		return;
	}

	for (int index = 0; index < treeWidget->topLevelItemCount(); ++index) {
		filterNavigatorItem(treeWidget->topLevelItem(index), navigatorItems, stackedLayout, filterString);
	}

	for (int index = 0; index < navigatorItems.size(); ++index) {
		if (!navigatorItems[index]->isHidden()) {
			treeWidget->setCurrentItem(navigatorItems[index]);
			return;
		}
	}

	treeWidget->clearSelection();
	stackedLayout->setCurrentIndex(navigatorItems.size());
}

bool SettingsFilter::filterNavigatorItem(QTreeWidgetItem *navigatorItem,
										 QList<QTreeWidgetItem *> &navigatorItems,
										 QStackedLayout *stackedLayout,
										 const QString &filterString) const
{
	bool isFiltered{true};

	if (navigatorItem->text(0).contains(filterString, Qt::CaseInsensitive)) {
		navigatorItem->setDisabled(false);
		for (int index = 0; index < navigatorItem->childCount(); ++index) {
			filterNavigatorItem(navigatorItem->child(index), navigatorItems, stackedLayout, filterString);
		}
		isFiltered = false;
	} else {
		isFiltered = !settingsPageContainsFilterString(stackedLayout->itemAt(navigatorItems.indexOf(navigatorItem))->widget(), filterString);

		for (int index = 0; index < navigatorItem->childCount(); ++index) {
			isFiltered &= filterNavigatorItem(navigatorItem->child(index), navigatorItems, stackedLayout, filterString);
		}
	}

	navigatorItem->setHidden(isFiltered);
	return isFiltered;
}

bool SettingsFilter::settingsPageContainsFilterString(QWidget *settingsPage, const QString &filterString) const
{
	foreach (auto button, settingsPage->findChildren<QAbstractButton*>()) {
		if (button->text().contains(filterString, Qt::CaseInsensitive)) {
			return true;
		}
	}

	foreach (auto label, settingsPage->findChildren<QLabel*>()) {
		if (label->text().contains(filterString, Qt::CaseInsensitive)) {
			return true;
		}
	}

	foreach (auto lineEdit, settingsPage->findChildren<QLineEdit*>()) {
		if (lineEdit->text().contains(filterString, Qt::CaseInsensitive)) {
			return true;
		}
		if (lineEdit->placeholderText().contains(filterString, Qt::CaseInsensitive)) {
			return true;
		}
	}

	foreach (auto comboBox, settingsPage->findChildren<QComboBox*>()) {
		for (int index = 0; index < comboBox->count(); ++index) {
			if (comboBox->itemText(index).contains(filterString, Qt::CaseInsensitive)) {
				return true;
			}
		}
	}

	return false;
}
