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

/*
 * Implementation based on the Miniature IOC Container from phillipvoyle on codeproject.com, kudos to him.
 * Link: https://www.codeproject.com/Articles/1029836/A-Miniature-IOC-Container-in-Cplusplus
 */

#ifndef KSNIP_DEPENDENCYINJECTOR_H
#define KSNIP_DEPENDENCYINJECTOR_H

#include <QSharedPointer>
#include <QMap>

class DependencyInjector
{
private:
	static int NextTypeId;

public:

	//one typeid per type
	template<typename T>
	static int getTypeID()
	{
		static int typeId = NextTypeId++;
		return typeId;
	}

	class FactoryRoot
	{
	public:
		virtual ~FactoryRoot() = default;
	};

	QMap<int, QSharedPointer<FactoryRoot>> mFactories;

	template<typename T>
	class CFactory: public FactoryRoot
	{
	private:
		std::function<QSharedPointer<T> ()> mFunctor;

	public:
		~CFactory() override = default;

		explicit CFactory(std::function<QSharedPointer<T> ()> functor) : mFunctor(functor)
		{
		}

		QSharedPointer<T> getObject()
		{
			return mFunctor();
		}
	};

	template<typename T>
	QSharedPointer<T> get()
	{
		auto typeId = getTypeID<T>();
		auto factoryBase = mFactories[typeId];
		auto factory = qSharedPointerCast<CFactory<T>>(factoryBase);
		return factory->getObject();
	}

	template<typename TInterface, typename ...TS>
	void registerFunctor(std::function<QSharedPointer<TInterface>
	(QSharedPointer<TS> ...ts)> functor)
	{
		mFactories[getTypeID<TInterface>()] = QSharedPointer<CFactory<TInterface>>::create([=]{
			return functor(get<TS>()...);
		});
	}

	// Register a single instance, always returns same instance, effectively single instance
	template<typename TInterface>
	void registerInstance(QSharedPointer<TInterface> t)
	{
		mFactories[getTypeID<TInterface>()] =
				QSharedPointer<CFactory<TInterface>>::create([=]{
					return t;
				});
	}

	template<typename TInterface, typename ...TS>
	void registerFunctor(QSharedPointer<TInterface> (*functor)(QSharedPointer<TS> ...ts))
	{
		registerFunctor(std::function<QSharedPointer<TInterface>
				(QSharedPointer<TS> ...ts)>(functor));
	}

	// Returns for every request a new instance
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void registerFactory()
	{
		registerFunctor(
				std::function<QSharedPointer<TInterface>(QSharedPointer<TArguments> ...ts)>(
						[](QSharedPointer<TArguments>...arguments) -> QSharedPointer<TInterface> {
							return QSharedPointer<TConcrete>::create(std::forward<QSharedPointer<TArguments>>(arguments)...);
						}));
	}

	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void registerInstance()
	{
		registerInstance<TInterface>(QSharedPointer<TConcrete>::create(get<TArguments>()...));
	}
};

#endif //KSNIP_DEPENDENCYINJECTOR_H
