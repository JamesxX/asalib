/// @file utility.cpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Implement commonly used utility functions.

#include <asalib/public/utility.hpp>

#include <fstream>
#include <filesystem>
#include <iomanip>

nlohmann::json asalib AbelianSquaresAnalysis::utility::LoadJSONFromFile(std::string file_location) {
	std::ifstream i(file_location);
	nlohmann::json j;
	i >> j;
	return j;
}

std::string asalib AbelianSquaresAnalysis::utility::GetParentDirectory(std::string file_location) {
	return std::filesystem::path(file_location).parent_path().string();
}

std::string asalib AbelianSquaresAnalysis::utility::PrepareSubdirectory(std::string directory, std::string subdirectory) {
	std::string outputDirectory = directory + "\\" + subdirectory;
	std::filesystem::create_directory(outputDirectory);
	return outputDirectory;
}

std::string asalib AbelianSquaresAnalysis::utility::CurrentExecutablePath() {
	return std::filesystem::current_path().string();
}