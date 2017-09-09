/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : System.h

	System base class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "ISystem.h"
#include "util/StaticTypeCounter.h"
#include "Log/ILogSubscriber.h"


namespace ECS
{
	template<class T>
	class System : public ISystem, protected Log::ILogSubscriber
	{
	public:

		static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

	protected:

		System() : ILogSubscriber(typeid(T).name())
		{
			LogInfo("System %s created.", typeid(T).name());
		}

	public:

		virtual ~System()
		{
			LogInfo("System %s released.", typeid(T).name());
		}

		virtual void Tick(float dt)
		{}

		inline SystemTypeId GetStaticSystemTypeID() const
		{
			return STATIC_SYSTEM_TYPE_ID;
		}

	private:

		static inline const u64 SetSystemTypeId()
		{
			return util::StaticTypeCounter<ISystem>::Increment();
		}
	};

	template<class T>
	const SystemTypeId System<T>::STATIC_SYSTEM_TYPE_ID = System<T>::SetSystemTypeId();
}

#endif // __SYSTEM_H__