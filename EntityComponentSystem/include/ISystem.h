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

	static const SystemTypeId INVALID_SYSTEMID = util::INVALID_TYPE_ID;



	class ISystem
	{
	protected:

		bool m_Enabled;

		ISystem() :
			m_Enabled(true)
		{}

	public:

		virtual ~ISystem()
		{}

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
	};
}

#endif // __I_SYSTEM_H__