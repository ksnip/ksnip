/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CALLCOUNTER_H
#define KSNIP_CALLCOUNTER_H

#include <QList>
#include <QPair>

template<typename K>
class CallCounter
{
public:
	explicit CallCounter() = default;
	~CallCounter() = default;
	void increment(K key);
	int count(K key) const;

private:
	QList<QPair<K,int>> mInnerCounter;
};

template<typename K>
void CallCounter<K>::increment(K key)
{
	for(auto entry : mInnerCounter) {
		if(entry.first == key) {
			entry.second++;
			return;
		}
	}
	mInnerCounter.append(QPair<K, int>(key,1));
}

template<typename K>
int CallCounter<K>::count(K key) const
{
	for(auto entry : mInnerCounter) {
		if(entry.first == key) {
			return entry.second;
		}
	}
	return 0;
}


#endif //KSNIP_CALLCOUNTER_H
