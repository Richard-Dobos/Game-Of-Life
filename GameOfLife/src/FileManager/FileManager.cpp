#include "FileManager.h"

FileManager::FileManager(const std::string& filePath)
	:m_FilePath(filePath) 
{
	const std::string absolutePath = std::filesystem::current_path().string();
	std::vector<int> slashIndecies;

	for (int i = 0; i < absolutePath.size() - 1; i++)
	{
		if (absolutePath[i] == '\\')
		{
			slashIndecies.emplace_back(i);
		}
	}

	for (int i = 1; i < slashIndecies.size(); i++)
	{
		std::string comp = absolutePath.substr(slashIndecies[i - 1] + 1, slashIndecies[i] - slashIndecies[i - 1] - 1);

		if (comp == "GameOfLife")
			m_AbsolutePath = absolutePath.substr(0, slashIndecies[i]);
	}
}

void FileManager::swapBuffers()
{
	std::vector<std::string> temp = m_LoadBuffer;

	m_LoadBuffer = m_SaveBuffer;
	m_SaveBuffer = temp;
}

void FileManager::clearLoadBuffer()
{
	m_LoadBuffer.clear();
}

void FileManager::clearSaveBuffer()
{
	m_SaveBuffer.clear();
}

void FileManager::loadFromFileToLoadBuffer()
{
	std::ifstream stream(m_FilePath);
	std::stringstream ss;

	std::string line;

	while (getline(stream, line))
		m_LoadBuffer.emplace_back(line);

	stream.close();
}

void FileManager::saveToFileFromSaveBuffer()
{
	checkExistingDir();

	std::ofstream stream(m_FilePath);

	if (stream.is_open())
		for (const auto& data : m_SaveBuffer)
			stream << data;

	stream.close();
	m_SaveBuffer.clear();
}

void FileManager::createSaveCategory(const char* category)
{
	if (findSaveCategory(category))
	{
		std::cout << "\nCategory with name: " << category << "!! Already exists.";
		return;
	}

	addToBuffer("#", category);
}

bool FileManager::findSaveCategory(const char* category)
{
	if (m_LoadBuffer.empty())
		loadFromFileToLoadBuffer();
	
	for (std::string line : m_LoadBuffer)
	{
		auto [firstPart, secondPart] = separateDataFromKeys(line);

		if (firstPart == "#" && secondPart == category)
		{
			return true;
		}
	}
	
	return false;
}

std::vector<std::string> FileManager::loadDataFromCategory(std::string categoryName)
{
	std::vector<std::string> returnVal;

	std::string category = "#" + categoryName;
	std::string currentCategory;

	for (int i = 0; i < m_LoadBuffer.size(); i++)
	{
		if (m_LoadBuffer[i][0] == '#')
			currentCategory = m_LoadBuffer[i];

		if (currentCategory == category)
			returnVal.emplace_back(m_LoadBuffer[i]);
	}

	return returnVal;
}

void FileManager::checkExistingDir()
{
	if (!std::filesystem::exists(m_FilePath))
	{
		std::string path = getDirectoriesFromPath();

		if (path == "Error")
		{
			std::cout << "\nInvalid path provided.";
			return;
		}

		std::filesystem::create_directory(path);
	}
}

bool FileManager::checkValidPath(const std::string &path) const
{
	if (path == "Error")
		return false;

	return true;
}

std::string FileManager::getDirectoriesFromPath()
{
	for (size_t i = m_FilePath.size(); i >= 0; i--)
		if (m_FilePath[i] == '/')
			return m_FilePath.substr(0, i);

	return "Error";
}

std::tuple<std::string, std::string> FileManager::separateDataFromKeys(std::string& line) const
{
	std::pair<std::string, std::string> retVal;

	for (size_t i = 0; i < line.size();i++)
	{
		if (line[i] == '=' || line[i] == '#')
		{
			retVal.first = line.substr(0, i);
			retVal.second = line.substr(i + 1, line.size());
		}
	}

	return retVal;
}
