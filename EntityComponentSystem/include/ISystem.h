/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : ISystem.h
	
	Interface class for system class

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_SYSTEM_H__
#define __I_SYSTEM_H__

#include "API.h"

#include "Event/Event.h"
#include "Event/EventHandler.h"

namespace ECS
{
	template<class T>
	class System;

	using SystemTypeId   = TypeID;

	using SystemPriority = u16;


	static const SystemTypeId INVALID_SYSTEMID				= INVALID_TYPE_ID;

	

	static const SystemPriority LOWEST_SYSTEM_PRIORITY		= 0;

	static const SystemPriority VERY_LOW_SYSTEM_PRIORITY	= 99;
	static const SystemPriority LOW_SYSTEM_PRIORITY			= 100;

	static const SystemPriority NORMAL_SYSTEM_PRIORITY		= 200;

	static const SystemPriority MEDIUM_SYSTEM_PRIORITY		= 300;

	static const SystemPriority HIGH_SYSTEM_PRIORITY		= 400;
	static const SystemPriority VERY_HIGH_SYSTEM_PRIORITY	= 401;

	static const SystemPriority HIGHEST_SYSTEM_PRIORITY		= 65535;



	struct SystemEnabled : public Event::Event<SystemEnabled>
	{
		SystemTypeId m_SystemTypeID;

		SystemEnabled(SystemTypeId systemTypeId) :
			m_SystemTypeID(systemTypeId)
		{}

	}; // struct SystemEnabled


	struct SystemDisabled : public Event::Event<SystemDisabled>
	{
		SystemTypeId m_SystemTypeID;

		SystemDisabled(SystemTypeId systemTypeId) :
			m_SystemTypeID(systemTypeId)
		{}

	}; // struct SystemDisabled


	class ECS_API ISystem
	{
	protected:

		const SystemPriority	m_Priority;

		bool					m_Enabled;



		ISystem(SystemPriority priority = NORMAL_SYSTEM_PRIORITY);

	public:

		virtual ~ISystem();

		virtual inline const SystemTypeId GetStaticSystemTypeID() const = 0;
		virtual inline const char* GetSystemTypeName() const = 0;

		virtual void PreUpdate(f32 dt) = 0;
		virtual void Update(f32 dt) = 0;
		virtual void PostUpdate(f32 dt) = 0;

		// ACCESSOR & MUTATOR

		void SetActive(bool state);

		inline bool IsActive() const { return this->m_Enabled; }

		inline const SystemPriority GetSystemPriority() const { return this->m_Priority; }
	};
}

#endif // __I_SYSTEM_H__