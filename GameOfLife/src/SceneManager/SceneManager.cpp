#include"SceneManager.h"

template <typename T>
void SceneManager::registerScene(const char* sceneName)
{
	m_Scenes[sceneName] = []() { return new T(); };
	//m_Scenes.emplace_back(std::make_pair(sceneName, []() { return new T() }));
}

Scene* SceneManager::getCurrentScene() const
{
	return m_CurrentScene;
}

void SceneManager::changeScene(const char* sceneName)
{
	if (m_Scenes.contains(sceneName))
		m_CurrentScene = m_Scenes[sceneName];

	else
		std::cout << "Couldn't find specified scene.";
}