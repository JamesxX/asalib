/// @file utility.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, declaring utility functions used in asalib, including functions easing the use of the library also.

#pragma once
#include "library.h"

#include <common/json.hpp>
#include <iomanip>
#include <fstream>

namespace AbelianSquaresAnalysis {

	namespace utility {

		/// @brief Utility function for loading JSON from a file.
		/// @param[in] file_location Location of file from which to load JSON object.
		/// @return JSON object.
		nlohmann::json asalib LoadJSONFromFile(std::string file_location);

		/// @brief Utility function for loading JSON from a file and casting it to desired C++ representation.
		/// @tparam _Ty Type of desired C++ representation.
		/// @param[in] file_location Location of file from which to load JSON object which is then cast to desired type.
		/// @return C++ representation of loaded JSON.
		template<class _Ty>
		_Ty LoadClassFromFile(std::string file_location) {
			return LoadJSONFromFile(file_location).get<_Ty>();
		}

		/// @brief Utility function for getting the parent directory of a file.
		/// @param[in] file_location Location of file of which to get parent directory.
		/// @return Parent directory.
		std::string asalib GetParentDirectory(std::string file_location);

		/// @brief Utility function for saving a C++ type to a file in JSON format.
		/// @tparam _Ty Type of C++ representation.
		/// @param[in] file_location Location at which to store JSON representation.
		/// @param[in] resource C++ representation to store as JSON at file_location.
		template<class _Ty>
		void SaveClassToFile(std::string file_location, const _Ty& resource) {
			nlohmann::json j = resource;
			std::ofstream outputFile(file_location);
			outputFile << std::setw(4) << j;
		}

		/// @brief Utility function to create a subdirectory if not already existing, and to return subsequent directory as a string.
		/// @param[in] directory Parent directory
		/// @param[in] subdirectory Subdirectory to create if required.
		/// @return Filepath of subdirectory, created or not.
		std::string asalib PrepareSubdirectory(std::string directory, std::string subdirectory);

		/// @brief Utility function for getting absolute current executable path.
		/// @return Absolute executable path.
		std::string asalib CurrentExecutablePath();
	}

}