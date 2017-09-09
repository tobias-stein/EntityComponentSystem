/*
	Author : Tobias Stein
	Date   : 30th August, 2017
	File   : SystemManager.h

	Entity Component System API.

	All Rights Reserved. (c) Copyright 2016 - 2017.
*/

#pragma once

#ifdef ECS_EXPORTS  
	#define ECS_API __declspec(dllexport)   
#else  
	#define ECS_API __declspec(dllimport)   
#endif  


namespace ECS {

} // namespace ECS