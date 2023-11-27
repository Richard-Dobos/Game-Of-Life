#pragma once

#include <SDL.h>
#include <unordered_map>

#include "../Scene/Scene.h"
#include "../WindowProperties.h"

class SceneManager : public Scene
{
public:
	SceneManager(SDL_Event* event, WindowProperties* windowProperties)
		:Scene(event, windowProperties) {}

	template<typename T>
	void changeScene()
	{
		m_CurrentScene = new T(m_Event, m_WindowProperties, this);
	}

	void update(SDL_Renderer* renderer)
	{
		m_CurrentScene->update(renderer);
	}

private:
	Scene* m_CurrentScene = nullptr;
};