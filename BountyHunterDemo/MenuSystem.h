///-------------------------------------------------------------------------------------------------
/// File:	MenuSystem.h.
///
/// Summary:	Declares the menu system class.
///-------------------------------------------------------------------------------------------------

#ifndef __MENU_SYSTEM_H__
#define __MENU_SYSTEM_H__

#include <ECS.h>

#include "GameEvents.h"

class MenuSystem : public ECS::System<MenuSystem>, protected ECS::Event::IEventListener
{
private:

	void RegisterEventCallbacks();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void MenuSystem::OnKeyDownEvent(const KeyDownEvent* event);
	///
	/// Summary:	Processes keys and raises Game specific event like pause, resume, quit.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	4/10/2017
	///
	/// Parameters:
	/// event - 	The event.
	///-------------------------------------------------------------------------------------------------

	void OnKeyDownEvent(const KeyDownEvent* event);

public:

	MenuSystem();
	~MenuSystem();

}; // class MenuSystem

#endif // __MENU_SYSTEM_H__
