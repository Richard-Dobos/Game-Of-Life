#pragma once

#include "../Scene.h"

class EditorScene : Scene
{
public:
	EditorScene();

	void update(SDL_Renderer* renderer) override;
};