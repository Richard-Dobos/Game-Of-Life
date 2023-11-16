#pragma once

#include <SDL.h>

class Scene
{
public:
	Scene() = default;
	Scene(SDL_Event* e)
		:m_Event(e) {}
	virtual ~Scene() = default;

	virtual void update(SDL_Renderer* renderer);

protected:
	SDL_Event* m_Event;
};