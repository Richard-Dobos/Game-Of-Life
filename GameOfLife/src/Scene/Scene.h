#pragma once

#include <SDL.h>
#include "../WindowProperties.h"

class Scene
{
public:
	Scene(SDL_Event* e, WindowProperties* windowProperties)
		:m_Event(e), m_WindowProperties(windowProperties) {}
	virtual ~Scene() = default;

	virtual void update(SDL_Renderer* renderer) = 0;

protected:
	SDL_Event* m_Event;
	WindowProperties* m_WindowProperties;
};