/// @file rawsquares.hpp
/// @author James R Swift
/// @date 26/06/2019
/// @brief Less common header for library, on raw squares.

#pragma once
#include "library.h"
#include "types.hpp"

namespace AbelianSquaresAnalysis {

	namespace squares {

		namespace raw {

			/// @brief Details on why a word isn't a raw square
			enum isRawSquareOutputReason {
				OddLength = 0, ///< The word tested was an odd length.
				NotNonTrivialSquare, ///< The word tested wasn't itself a non-trivial square.
				NonTrivialSquareWithin, ///< The word was non-trivial, but also contained within itself other non-trivial squares.
				Pass ///< The tested word is a raw square
			};

			/// @brief Utility function for determining if a given word is a raw square.
			/// @param[in] input Word to test
			/// @param[out] code Details on why a word isn't a raw square.
			/// @return Whether the word is a raw square.
			bool asalib isRawSquare(types::word input, isRawSquareOutputReason& code);


		} // namespace raw

	} // namespace squares

} // namespace AbelianSquaresAnalysis
