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

namespace ECS
{
	template<class T>
	class System;

	using SystemTypeId   = TypeID;

	using SystemPriority = u16;


	static const SystemTypeId INVALID_SYSTEMID				= INVALID_TYPE_ID;

	

	static const SystemPriority LOWEST_SYSTEM_PRIORITY		= std::numeric_limits<SystemPriority>::min();

	static const SystemPriority VERY_LOW_SYSTEM_PRIORITY	= 99;
	static const SystemPriority LOW_SYSTEM_PRIORITY			= 100;

	static const SystemPriority NORMAL_SYSTEM_PRIORITY		= 200;

	static const SystemPriority MEDIUM_SYSTEM_PRIORITY		= 300;

	static const SystemPriority HIGH_SYSTEM_PRIORITY		= 400;
	static const SystemPriority VERY_HIGH_SYSTEM_PRIORITY	= 401;

	static const SystemPriority HIGHEST_SYSTEM_PRIORITY		= std::numeric_limits<SystemPriority>::max();


	class ECS_API ISystem
	{
		friend class SystemManager;

	private:

		/// Summary:	Duration since last system update in milliseconds.
		f32						m_TimeSinceLastUpdate;

		SystemPriority			m_Priority;

		/// Summary:	The system update interval.
		/// A negative value means system should update each time the engine receives an update.
		f32						m_UpdateInterval;

		u8						m_Enabled		: 1;
		u8						m_NeedsUpdate	: 1;
		u8						m_Reserved		: 6;

	protected:

		ISystem(SystemPriority priority = NORMAL_SYSTEM_PRIORITY, f32 updateInterval_ms = -1.0f);

	public:

		virtual ~ISystem();

		virtual inline const SystemTypeId GetStaticSystemTypeID() const = 0;
		virtual inline const char* GetSystemTypeName() const = 0;

		virtual void PreUpdate(f32 dt)	= 0;
		virtual void Update(f32 dt)		= 0;
		virtual void PostUpdate(f32 dt) = 0;
	};
}

#endif // __I_SYSTEM_H__