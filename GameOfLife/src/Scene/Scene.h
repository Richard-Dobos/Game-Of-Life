#pragma once

#include <SDL.h>
#include "../WindowProperties.h"
#include "../SaveManager/SaveManager.h"

class Scene
{
public:
	Scene(SDL_Event* e, WindowProperties* windowProperties, SaveManager* saveManager)
		:m_Event(e), m_SaveManager(saveManager), m_WindowProperties(windowProperties) {}
	virtual ~Scene() = default;

	virtual void update(SDL_Renderer* renderer) = 0;

protected:
	SDL_Event* m_Event;
	SaveManager* m_SaveManager;
	WindowProperties* m_WindowProperties;
};