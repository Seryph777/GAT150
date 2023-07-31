#pragma once
#include <string>

#include <filesystem>


namespace kiko
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path); // Variable with'&' means reference

	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);

}
