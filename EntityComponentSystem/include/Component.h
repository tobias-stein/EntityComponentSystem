/*
	Author : Tobias Stein
	Date   : 2nd July, 2016
	File   : Component.h
	
	Base component class which provides a unique id.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "IComponent.h"
#include "util/StaticTypeCounter.h"

#include "Log/Logger.h"

namespace ECS
{
	template<class T>
	class Component : public IComponent
	{
	public:

		static const ComponentTypeId STATIC_COMPONENT_TYPE_ID;

		Component() 
		{}

		virtual ~Component()
		{}		

		inline ComponentTypeId GetStaticComponentTypeID() const
		{
			return STATIC_COMPONENT_TYPE_ID;
		}
	private:

		static inline const u64 SetComponentTypeId()
		{
			u64 CID = util::StaticTypeCounter<IComponent>::Increment();
			Log::Logger::GetInstance().LogDebug("Register component \'%s\' [COMPONENT-ID: %d]", typeid(T).name(), CID);
			return CID;
		}		
	};

	// This private member only exists to force the compiler to create an instance of Component T,
	// which will set its unique identifier.
	template<class T>
	const ComponentTypeId Component<T>::STATIC_COMPONENT_TYPE_ID = Component<T>::SetComponentTypeId();
}

#endif // __COMPONENT_H__