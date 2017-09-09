/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : IComponent.h
	
	Interface class for component class

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_COMPONENT_H__
#define __I_COMPONENT_H__

#include "util/IdManager.h"

namespace ECS
{
	using ComponentId = util::ObjectId;
	using ComponentTypeId = util::TypeId;


	class Entity;

	template<class T>
	class Component;

	class IComponent : public util::IdManager
	{
		friend class Entity;

	protected:
		
		Entity* m_Owner;

		bool m_Enabled;

	public:

		IComponent() :
			m_Owner(nullptr),
			m_Enabled(true)
		{}

		virtual ~IComponent()
		{}


		// Cast
		template<class T>
		inline Component<T>* As()
		{
			return reinterpret_cast<Component<T>*>(this);
		}

		// ACCESSOR

		inline const ComponentId GetComponentId() const
		{
			return this->m_Id;
		}

		inline Entity* GetOwner() const
		{
			return this->m_Owner;
		}

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

#endif // __I_COMPONENT_H__