#include "FileManager.h"

void FileManager::loadFromFileToLoadBuffer()
{
	std::ifstream stream(m_FilePath);
	std::stringstream ss;

	std::string line;

	m_LoadBuffer.clear();

	while (getline(stream, line))
		m_LoadBuffer.emplace_back(line);

	stream.close();
}

void FileManager::saveToFileFromSaveBuffer()
{
	checkExistingDir();
	m_SaveBuffer.clear();

	std::ofstream stream(m_FilePath);

	if (stream.is_open())
		for (const auto& data : m_SaveBuffer)
			stream << data;

	stream.close();
}

void FileManager::swapBuffers()
{
	std::vector<std::string> temp = m_LoadBuffer;

	m_LoadBuffer = m_SaveBuffer;
	m_SaveBuffer = temp;
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

void FileManager::createSaveCategory(const char* category)
{
	if (findSaveCategory(category))
	{
		std::cout << "\nCategory with name: " << category << "!! Already exists.";
		return;
	}

	addToBuffer("#", category);
}

std::string FileManager::getDirectoriesFromPath()
{
	for (size_t i = m_FilePath.size(); i >= 0; i--)
		if (m_FilePath[i] == '/')
			return m_FilePath.substr(0, i);

	return "Error";
}

bool FileManager::checkValidPath(const std::string &path) const
{
	if (path == "Error")
		return false;

	return true;
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

void FileManager::loadDefaultSettings()
{

}