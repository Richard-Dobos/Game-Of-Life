#include "EditorScene.h"

void EditorScene::update(SDL_Renderer* renderer)
{
	std::cout << "\n Render Settings: " << m_RenderBoardSettings;
	checkForSettingsShortcut();
}

void EditorScene::renderBoardSettingsMenu(SDL_Renderer* renderer)
{
	if (!m_RenderBoardSettings)
		return;
}

void EditorScene::checkForSettingsShortcut()
{
	if(m_Event->type == SDL_KEYDOWN)
	{ 
		if (m_Event->key.keysym.sym = SDLK_t)
		{
			m_RenderBoardSettings = !m_RenderBoardSettings;
			std::cout << "\nTest";
		}
	}
}