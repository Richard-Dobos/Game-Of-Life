#include "FileManager.h"

void FileManager::loadFromFileToBuffer()
{
	std::ifstream stream(m_FilePath);
	std::stringstream ss;

	std::string line;

	while (getline(stream, line))
	{
		m_LoadBuffer.emplace_back(line);
	}

	for (std::string& data : m_LoadBuffer)
	{
		std::cout << data << '\n';
	}

	m_LoadBuffer.clear();
	stream.close();
}

void FileManager::saveToFile()
{
	checkExistingDir();

	std::ofstream stream(m_FilePath);

	if (stream.is_open())
		for (auto& data : m_SaveBuffer)
			stream << data;
		

	m_SaveBuffer.clear();
	stream.close();
}

std::pair<std::string, std::string> FileManager::seperateData(std::string& line)
{
	std::pair<std::string, std::string> retVal;

	for (size_t i = 0; i < line.size();i++)
	{
		if (line[i] == '=')
		{
			retVal.first = line.substr(0, i);
			retVal.second = line.substr(i + 1, line.size());
		}
	}

	return retVal;
}

void FileManager::createSaveCategory(const char* category)
{
	addToBuffer("#", category);
}

std::string FileManager::getDirectoriesFromPath()
{
	for (size_t i = m_FilePath.size(); i >= 0; i--)
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