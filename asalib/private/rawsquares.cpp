/// @file rawsquares.hpp
/// @author James R Swift
/// @date 26/06/2019
/// @brief Implementations of raw squares logic

#include <asalib/public/rawsquares.hpp>
#include <asalib/public/squares.hpp>

bool asalib AbelianSquaresAnalysis::squares::raw::isRawSquare(types::word input, isRawSquareOutputReason& code) {

	if (input.length() % 2 != 0) {
		code = isRawSquareOutputReason::OddLength;
		return false;
	}

	// Generate the alphabet of the input word.
	// This could be simplified to be a constant, given the alphabet is always binary.
	types::parihkVector alphabet = input.countAlphabetSize();
	std::string_view inputView(input);

	// Skip expensive function calls if input isn't a square.
	// Assumption : input is not a trivial square, as we aren't doing block count of 1.
	if (!squares::AnalyseSubstring({ inputView, input.length(), 0, input.countAlphabetSize() }).isSquare) {
		code = isRawSquareOutputReason::NotNonTrivialSquare;
		return false;
	}

	// Input is certainly a square.
	// Do there exist non-trivial squares within?
	for (unsigned int len = 2; len < input.length(); len += 2) {
		// for every valid start position
		for (unsigned int pos = 0; pos < (input.length() - len + 1); pos++) {

			squares::substringAnalysisInput AnalysisInput;
			AnalysisInput.word = inputView;
			AnalysisInput.length = len;
			AnalysisInput.position = pos;
			AnalysisInput.alphabet = alphabet;

			// non trivial square found within!
			squares::substringAnalysisOutput computation_output = squares::AnalyseSubstring(AnalysisInput);
			if (computation_output.isSquare && !computation_output.isTrivial) {
				code = isRawSquareOutputReason::NonTrivialSquareWithin;
				return false;
			}
		}
	}

	// No non-trivial squares within found, square is raw
	code = isRawSquareOutputReason::Pass;
	return true;
}