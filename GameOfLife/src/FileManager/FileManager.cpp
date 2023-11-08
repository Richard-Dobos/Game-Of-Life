#include "FileManager.h"

namespace fileManager
{
	void FileManager::loadFromFile()
	{
		std::ifstream stream(m_FilePath);


	}

	void FileManager::saveToFile()
	{
		if (!std::filesystem::exists(m_FilePath))
		{
			std::string path = getDirectoriesFromPath();

			if (path == "Error")
			{
				std::cout << "\nInvalid path provided.";
				return;
			}

			std::filesystem::create_directory(getDirectoriesFromPath());
		}

		std::ofstream stream(m_FilePath);
		std::string testMassage = "This is a test save file.";

		if (stream.is_open())
			stream << testMassage;

		stream.close();
	}

	std::string FileManager::getDirectoriesFromPath()
	{
		for (int i = m_FilePath.size(); i >= 0; i--)
			if (m_FilePath[i] == '/')
				return m_FilePath.substr(0, i);

		return "Error";
	}

	bool FileManager::checkValidPath(std::string &path) const
	{
		if (path == "Error")
			return false;

		return true;
	}
}