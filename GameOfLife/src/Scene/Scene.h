#pragma once

#include <SDL.h>

class Scene
{
public:
	Scene(SDL_Event* e)
		:m_Event(e) {}
	virtual ~Scene() = default;

	virtual void update(SDL_Renderer* renderer) = 0;

private:
	virtual void loadSettings() = 0;

protected:
	SDL_Event* m_Event;
};