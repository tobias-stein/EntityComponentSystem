/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : ISystem.h
	
	Interface class for system class

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_SYSTEM_H__
#define __I_SYSTEM_H__

#include "util/IdManager.h"

namespace ECS
{
	template<class T>
	class System;

	using SystemTypeId = util::TypeId;

	using SystemPriority = u16;


	static const SystemTypeId INVALID_SYSTEMID = util::INVALID_TYPE_ID;

	

	static const SystemPriority LOWEST_SYSTEM_PRIORITY		= 0;

	static const SystemPriority VERY_LOW_SYSTEM_PRIORITY	= 99;
	static const SystemPriority LOW_SYSTEM_PRIORITY			= 100;

	static const SystemPriority NORMAL_SYSTEM_PRIORITY		= 200;

	static const SystemPriority MEDIUM_SYSTEM_PRIORITY		= 300;

	static const SystemPriority HIGH_SYSTEM_PRIORITY		= 400;
	static const SystemPriority VERY_HIGH_SYSTEM_PRIORITY	= 401;

	static const SystemPriority HIGHEST_SYSTEM_PRIORITY		= 65535;

	class ISystem
	{
	protected:

		const SystemPriority	m_Priority;

		bool					m_Enabled;



		ISystem(SystemPriority priority = NORMAL_SYSTEM_PRIORITY) :
			m_Priority(priority),
			m_Enabled(true)
		{}

	public:

		virtual ~ISystem()
		{}

		virtual const char* GetSystemTypeName() const = 0;

		virtual void Tick(float dt)
		{}
		

		// ACCESSOR & MUTATOR

		inline void SetActive(bool state)
		{
			this->m_Enabled = state;
		}

		inline bool IsActive() const
		{
			return this->m_Enabled;
		}

		inline const SystemPriority GetSystemPriority() const
		{
			return this->m_Priority;
		}
	};
}

#endif // __I_SYSTEM_H__