///-------------------------------------------------------------------------------------------------
/// File:	InputSystem.h.
///
/// Summary:	Declares the input system class.
///-------------------------------------------------------------------------------------------------

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__


#include <System.h>

class InputSystem : public ECS::System<InputSystem>
{
private:

	int				m_NumKeys;
	unsigned char*	m_OldKeyStates;

public:

	InputSystem();
	~InputSystem();

	virtual void PreUpdate(float dt) override;

}; // class InputSystem

#endif // __INPUT_SYSTEM_H__