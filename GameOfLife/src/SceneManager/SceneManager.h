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
	void registerScene(const char* sceneName)
	{
		if (m_Scenes.contains(sceneName))
			return;

		m_Scenes[sceneName] = new T(m_Event, m_WindowProperties);
	}

	void changeScene(const char* sceneName)
	{
		if (!m_Scenes.contains(sceneName))
			return;

		delete m_CurrentScene;

		m_CurrentScene = m_Scenes[sceneName];
	}

	void update(SDL_Renderer* renderer)
	{
		m_CurrentScene->update(renderer);
	}

private:
	Scene* m_CurrentScene;
	std::unordered_map<const char*, Scene*> m_Scenes;

};