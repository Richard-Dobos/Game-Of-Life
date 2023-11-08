#pragma once

#include <SDL.h>

class Scene
{
public:
	Scene();

protected:
	virtual void update(SDL_Renderer* renderer);
};