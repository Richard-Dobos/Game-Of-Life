#pragma once

#include "../Scene.h"

class EditorScene : public Scene
{
public:
	EditorScene(SDL_Event* e)
		:Scene(e) {}

	void update(SDL_Renderer* renderer) override;
};