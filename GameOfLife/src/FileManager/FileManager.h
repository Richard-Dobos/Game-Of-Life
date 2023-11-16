#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>

class FileManager
{
public:
	FileManager(const std::string& filePath)
		:m_FilePath(filePath) {}

	void loadFromFileToBuffer();
	void saveToFile();

	void createSaveCategory(const char* categoryName);

	template<typename T>
	void addToBuffer(std::string key, T value)
	{
		if (key != "#")
			m_SaveBuffer.emplace_back(std::format("{}={};\n", key, value));

		else
			m_SaveBuffer.emplace_back(std::format("#{};\n", value));
	}

private:
	void checkExistingDir();

	bool findCategory(const char* category) const;
	bool checkValidPath(std::string& path) const;

	std::string getDirectoriesFromPath();
	std::pair<std::string, std::string> seperateData(std::string& line);

private:
	std::string m_FilePath;
	std::vector<std::string>  m_SaveBuffer;
	std::vector<std::string>  m_LoadBuffer;
};