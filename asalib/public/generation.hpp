/// @file generation.hpp
/// @author James R Swift
/// @date 26/06/2019
/// @brief Less common library header on the generation of binary words.

#pragma once
#include "library.h"

#include <vector>
#include <string>

namespace AbelianSquaresAnalysis {

	namespace generation {

		namespace binary {

			/// @brief binary alphabet
			asalib extern char alphabet[];

			/// @brief Arguments for generateSquares
			struct generateSquaresArgs {
				unsigned int _blockCount; ///< Number of blocks in generated word
				unsigned int _length; ///< Length of words to generate
				bool posAlphabetStart = false; ///< INTERNAL

				/// @brief Comparison functions used internally
				/// @param[in] other other generateSquaresArgs with which to compare
				/// @return Are the two equal.
				inline bool operator==(const generateSquaresArgs &other) const {
					return (_blockCount == other._blockCount
						&& _length == other._length
						&& posAlphabetStart == other.posAlphabetStart);
				}

				/*const char* ABuffer;
				const char* BBuffer;*/

			};

			/// @brief Generate binary words to a specification
			/// @param[in] Args Specification of generated words
			/// @return Vector of generated words (as std::string)
			asalib std::vector<std::string> generateSquares(generateSquaresArgs Args);

			/// @brief Generate binary words of either 3 or 4 blocks
			/// @param[in] Args Specification of generated words
			/// @return Vector of generated words (as std::string)
			asalib std::vector<std::string> generateSquaresX(generateSquaresArgs Args);

		} // namespace binary

	} // namespace generation

} // namespace AbelianSquaresAnalysis
