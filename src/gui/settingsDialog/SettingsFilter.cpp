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

#include <functional>

#include <QAbstractButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

#include "SettingsFilter.h"

void SettingsFilter::filterSettings(const QString &filterString,
									QTreeWidget *treeWidget,
									std::function<QWidget*(QTreeWidgetItem*)> getSettingsPageFun) const
{
	if (filterString.isEmpty()) {
		for (size_t topLevelItemIndex = 0; topLevelItemIndex < treeWidget->topLevelItemCount(); ++topLevelItemIndex) {
			auto topLevelItem = treeWidget->topLevelItem(topLevelItemIndex);
			for (size_t childIndex = 0; childIndex < topLevelItem->childCount(); ++childIndex) {
				topLevelItem->child(childIndex)->setHidden(false);
			}
			topLevelItem->setHidden(false);
		}
		return;
	}

	for (int index = 0; index < treeWidget->topLevelItemCount(); ++index) {
		filterNavigatorItem(treeWidget->topLevelItem(index), filterString, getSettingsPageFun);
	}

	for (size_t topLevelItemIndex = 0; topLevelItemIndex < treeWidget->topLevelItemCount(); ++topLevelItemIndex) {
		if (!treeWidget->topLevelItem(topLevelItemIndex)->isHidden()) {
			treeWidget->setCurrentItem(treeWidget->topLevelItem(topLevelItemIndex));
			return;
		}
	}

	treeWidget->clearSelection();
}

bool SettingsFilter::filterNavigatorItem(QTreeWidgetItem *navigatorItem,
										 const QString &filterString,
										 std::function<QWidget*(QTreeWidgetItem*)> getSettingsPageFun) const
{
	bool isFiltered{true};

	if (navigatorItem->text(0).contains(filterString, Qt::CaseInsensitive)) {
		navigatorItem->setDisabled(false);
		for (int index = 0; index < navigatorItem->childCount(); ++index) {
			filterNavigatorItem(navigatorItem->child(index), filterString, getSettingsPageFun);
		}
		isFiltered = false;
	} else {
		isFiltered = !settingsPageContainsFilterString(getSettingsPageFun(navigatorItem), filterString);

		for (int index = 0; index < navigatorItem->childCount(); ++index) {
			isFiltered &= filterNavigatorItem(navigatorItem->child(index), filterString, getSettingsPageFun);
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
