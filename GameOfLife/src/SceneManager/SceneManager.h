#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>
#include "../Scene/Scene.h"

class SceneManager : Scene
{
public:
	SceneManager();

	Scene* getCurrentScene() const;
	void changeScene(const char* sceneName);

	template <typename T>
	void registerScene(const char* sceneName);

	Scene* m_CurrentScene;
private:
	std::unordered_map<const char*, Scene*> m_Scenes;
	//std::vector<std::pair<const char*, std::function<Scene* ()>>> m_Scenes;
};
