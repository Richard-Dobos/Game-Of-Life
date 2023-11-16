#include"SceneManager.h"

Scene* SceneManager::getCurrentScene() const
{
	return m_CurrentScene;
}

void SceneManager::changeScene(const char* sceneName)
{
	if (m_Scenes.contains(sceneName))
	{
		m_CurrentScene = m_Scenes[sceneName];
	}

	else
		std::cout << "Couldn't find specified scene.";
}