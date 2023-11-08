#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <tuple>

namespace fileManager 
{
	class FileManager
	{
	public:
		FileManager(const std::string& filePath)
			:m_FilePath(filePath) {}

		void loadFromFile();
		void saveToFile();

	private:
		std::string getDirectoriesFromPath();
		bool checkValidPath(std::string &path) const;

	private:
		std::string m_FilePath;
	};
}