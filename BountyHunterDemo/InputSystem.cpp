///-------------------------------------------------------------------------------------------------
/// File:	InputSystem.cpp.
///
/// Summary:	Implements the input system class.
///-------------------------------------------------------------------------------------------------

#include "InputSystem.h"
#include "GameEvents.h"

#include <SDL.h>

InputSystem::InputSystem()
{
	const Uint8* keyStates = SDL_GetKeyboardState(&this->m_NumKeys);

	this->m_OldKeyStates = new unsigned char[m_NumKeys];
	memcpy(this->m_OldKeyStates, keyStates, sizeof(unsigned char) * m_NumKeys);
}

InputSystem::~InputSystem()
{
	delete[] this->m_OldKeyStates;
	this->m_OldKeyStates = nullptr;
}

void InputSystem::PreUpdate(float dt)
{
	SDL_Event event;

	// only handle keyboard and mouse events
	while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_MOUSEWHEEL))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				if (this->m_OldKeyStates[event.key.keysym.scancode])
				{
					ECS::ECS_Engine->SendEvent<KeyPressedEvent>(event.key.keysym.sym);
				}
				else
				{
					ECS::ECS_Engine->SendEvent<KeyDownEvent>(event.key.keysym.sym);
				}
				break;
			}

			case SDL_KEYUP:
				ECS::ECS_Engine->SendEvent<KeyUpEvent>(event.key.keysym.sym);
				break;
			

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button) 
				{
					case SDL_BUTTON_LEFT:
						ECS::ECS_Engine->SendEvent<LeftButtonDownEvent>(event.motion.x, event.motion.y);
						break;

					case SDL_BUTTON_RIGHT:
						ECS::ECS_Engine->SendEvent<RightButtonDownEvent>(event.motion.x, event.motion.y);
						break;
				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						ECS::ECS_Engine->SendEvent<LeftButtonUpEvent>(event.motion.x, event.motion.y);
						break;

					case SDL_BUTTON_RIGHT:
						ECS::ECS_Engine->SendEvent<RightButtonUpEvent>(event.motion.x, event.motion.y);
						break;
				}
				break;
			}
		}
	}

	// store key states
	memcpy(this->m_OldKeyStates, SDL_GetKeyboardState(NULL), sizeof(unsigned char) * m_NumKeys);
}