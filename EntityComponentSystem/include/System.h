/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : System.h

	System base class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "API.h"

#include "ISystem.h"
#include "util/FamilyTypeCounter.h"


namespace ECS
{
	template<class T>
	class System : public ISystem
	{
	protected:

		Log::Logger* m_Logger;

	public:

		static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

	protected:

		System() : m_Logger(GetLogger(typeid(T).name()))
		{
			m_Logger->LogInfo("System %s created.", typeid(T).name());
		}

	public:

		virtual ~System()
		{
			m_Logger->LogInfo("System %s released.", typeid(T).name());
		}

		virtual void Tick(float dt)
		{}

		inline SystemTypeId GetStaticSystemTypeID() const
		{
			return STATIC_SYSTEM_TYPE_ID;
		}

	}; // class System<T>

	template<class T>
	const SystemTypeId System<T>::STATIC_SYSTEM_TYPE_ID = util::Internal::FamilyTypeCounter<ISystem>::Increment();

} // namespace ECS

#endif // __SYSTEM_H__