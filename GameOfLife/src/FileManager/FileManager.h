#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

class FileManager
{
public:
	FileManager(const std::string& filePath);

	void swapBuffers();
	void clearLoadBuffer();
	void clearSaveBuffer();
	void loadFromFileToLoadBuffer();
	void saveToFileFromSaveBuffer();
	void createSaveCategory(const char* categoryName);
	bool findSaveCategory(const char* categoryName);

	std::vector<std::string>* getLoadBuffer() { return &m_LoadBuffer; }
	std::vector<std::string> loadDataFromCategory(std::string categoryName);

	template<typename T>
	void addToBuffer(std::string key, T value)
	{
		if (key != "#")
			m_SaveBuffer.emplace_back(std::format("{}={};\n", key, value));
			
		else
			m_SaveBuffer.emplace_back(std::format("#{}\n", value));
	}

	std::string m_AbsolutePath;

private:
	void checkExistingDir();
	bool checkValidPath(const std::string& path) const;

	std::string getDirectoriesFromPath();
	std::tuple<std::string, std::string> separateDataFromKeys(std::string& line) const;

private:
	std::string m_FilePath;
	std::vector<std::string>  m_SaveBuffer;
	std::vector<std::string>  m_LoadBuffer;
};