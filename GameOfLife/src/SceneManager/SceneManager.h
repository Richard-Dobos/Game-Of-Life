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
	void setStartScene() { m_CurrentScene = new T(m_Event, m_WindowProperties, this); }

	template<typename T>
	void changeScene() { m_CurrentScene = new T(m_Event, m_WindowProperties, this); }

	void update(SDL_Renderer* renderer) 
	{ 
		uint32_t frameStart;
		uint32_t frameTime;

		frameStart = SDL_GetTicks();
		
		m_CurrentScene->update(renderer); 
		
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		
		if (1000 / m_WindowProperties->refreshRate > frameTime)
		{
			SDL_Delay(1000 / m_WindowProperties->refreshRate - frameTime);
		}
	}

private:
	Scene* m_CurrentScene = nullptr;
};