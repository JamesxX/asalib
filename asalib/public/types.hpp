/// @file types.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, defining commonly used types.

#pragma once
#include "library.h"
#include <string>
#include <map>
#include <common/json.hpp>

namespace AbelianSquaresAnalysis {

	namespace types {

		typedef unsigned int length; ///< Internally used type for consistency between builds.

#ifdef _WIN64
		typedef unsigned long long int integer; ///< Internally used type for consistency between builds.
#else
		typedef unsigned long int integer; ///< Internally used type for consistency between builds.
#endif

		/// @brief Structure used to store information about a given substring, for arbitrary alphabet sizes.
		class parihkVector : public std::map<char, types::integer> {
		public:

			/// @brief Default constructor for parihkVector class
			parihkVector();

			/// @brief Builds the string representation of a parihk vector, used in detail output.
			/// @return String representation of parihk vector.
			inline operator std::string() const {
				bool first = true;
				std::string output = "(";
				for (const auto& entry : *this) {
					if (!first) {
						output += ", ";
					}
					output += std::to_string(entry.second);
					first = false;
				}
				output += ")^2";
				return output;
			}

			/// @brief Utility function for determining if the parihk vector denotes a trivial square.
			/// @return Is the parihk vector one of a trivial square.
			bool asalib isTrivial() const;
		};

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::types::parihkVector to JSON.
		/// @param[out] j JSON object.
		/// @param[in] data input AbelianSquaresAnalysis::types::parihkVector.
		/// @see AbelianSquaresAnalysis::types::parihkVector.
		void asalib to_json(nlohmann::json& j, const types::parihkVector& data);

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::types::parihkVector from JSON.
		/// @param[in] j JSON object.
		/// @param[out] data input AbelianSquaresAnalysis::types::parihkVector.
		/// @see AbelianSquaresAnalysis::types::parihkVector.
		void asalib from_json(const nlohmann::json& j, types::parihkVector& data);

		/// @brief Class extension of std::string to represent words internally.
		///
		/// This class implements several utility functions in order to simplify algorithms.
		class word : public std::string {
		public:

			/// @brief Default constructor for types::word class
			inline word() : word("") {}

			/// @brief Constructor of types:word class with initial string value.
			///
			/// This function sanitizes the input to reduce algorithm cost later.
			/// @param[in] in Initial value that types::word class holds.
			inline word(std::string in): std::string(in)
			{
				std::transform(this->begin(), this->end(), this->begin(), ::tolower);
			}

			/// @brief Counts the number of different characters in a word, and constructs a copyable parihkVector
			/// representing said alphabet.
			/// @return empty parihk vector representing alphabet size.
			types::parihkVector asalib countAlphabetSize();

			/// @brief Counts the occurence of different characters in word for a given alphabet.
			/// @warning When analyzing substrings of a greater word, the input parihk vector must be a copy construct parihk vector of the alphabet over the parent word!
			/// @param[in] offset start point of occurences count.
			/// @param[in] count number of positions to check.
			/// @param[in/out] out Modified alphabet parihk vector counting occurences of given characters.
			void countOccurences(size_t offset, size_t count, types::parihkVector& out);
		};

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::types::word to JSON.
		/// @param[out] j JSON object.
		/// @param[in] data input AbelianSquaresAnalysis::types::word.
		/// @see AbelianSquaresAnalysis::types::word.
		void asalib to_json(nlohmann::json& j, const types::word& data);

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::types::word from JSON.
		/// @param[in] j JSON object.
		/// @param[out] data input AbelianSquaresAnalysis::types::word.
		/// @see AbelianSquaresAnalysis::types::word.
		void asalib from_json(const nlohmann::json& j, types::word& data);

		typedef bool boolean; ///< Internally used type for consistency between builds.
		typedef std::map<types::word, types::word> mapping; ///< Type containing morphism information.
		typedef std::map<std::string, mapping> morphism_list; ///< Type containing a list of morphisms.


	}

}