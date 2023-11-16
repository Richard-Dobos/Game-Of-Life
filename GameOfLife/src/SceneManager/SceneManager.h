#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

#include "../FileManager/FileManager.h"

#include "../Scene/Scene.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Scene/MainMenu/MainMenuScene.h"
#include "../Scene/EditorScene/EditorScene.h"

class SceneManager : public Scene
{
public:
	SceneManager(Scene* currentScene, const FileManager* fileManager)
		:m_CurrentScene(currentScene), m_FileManager(fileManager) {}

	Scene* getCurrentScene() const;

	void changeScene(const char* sceneName);

	template <typename T>
	void registerScene(const char* sceneName, SDL_Event* e)
	{
		m_Scenes[sceneName] = [e]() { return new T(e); };
	}

	std::function<Scene*> m_CurrentScene;

private:
	const FileManager* m_FileManager;
	std::unordered_map<const char*, std::function<Scene*>> m_Scenes;
};
