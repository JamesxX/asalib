/// @file generation.cpp
/// @author James R Swift
/// @date 26/06/2019
/// @brief Implementation of generation of binary words.

#include <asalib/public/library.h>
#include <asalib/public/generation.hpp>

asalib char AbelianSquaresAnalysis::generation::binary::alphabet[] = { 'A', 'B' };

asalib std::vector<std::string> AbelianSquaresAnalysis::generation::binary::generateSquares(generateSquaresArgs Args) {

	/*if (Args.ABuffer == nullptr) {
		Args.ABuffer = std::string(Args._length, alphabet[0]).c_str();
	}

	if (Args.BBuffer == nullptr) {
		Args.BBuffer = std::string(Args._length, alphabet[1]).c_str();
	}*/

	std::vector<std::string> output;
	if (Args._blockCount == 2) { // end of recursion
		for (unsigned int i = 1; i < Args._length; i++) {
			output.push_back(std::string(i, alphabet[(unsigned int)Args.posAlphabetStart]) + std::string(Args._length - i, alphabet[(unsigned int)!Args.posAlphabetStart]));
		}
	}
	else {
		for (unsigned int i = 1; i < (Args._length - Args._blockCount - 1); i++) {

			generateSquaresArgs recursionArgs = {
				Args._blockCount - 1,
				Args._length - i,
				!Args.posAlphabetStart
			};

			for (auto& entry : generateSquares(recursionArgs)) {
				output.push_back(std::string(i, alphabet[(unsigned int)Args.posAlphabetStart]) + entry);
			}
		}
	}

	return output;
}

asalib std::vector<std::string> AbelianSquaresAnalysis::generation::binary::generateSquaresX(generateSquaresArgs Args) {

	if (Args._blockCount == 3) {
		std::vector<std::string> output; // Reserve?
		for (unsigned a = 1; a <= (Args._length - 2); a++) {
			for (unsigned b = a + 1; b <= (Args._length - 1); b++) {
				std::string generated;
				generated.reserve(Args._length);
				generated.append(a, alphabet[0]);
				generated.append(b - a, alphabet[1]);
				generated.append(Args._length - b, alphabet[0]);
				output.push_back(generated);
			}
		}

	}
	else if (Args._blockCount == 4) {
		std::vector<std::string> output; // Reserve?
		for (unsigned a = 1; a <= (Args._length - 3); a++) {
			for (unsigned b = a + 1; b <= (Args._length - 2); b++) {
				for (unsigned c = b + 1; c <= (Args._length - 1); c++){
					std::string generated;
					generated.reserve(Args._length);
					generated.append(a, alphabet[0]);
					generated.append(b - a, alphabet[1]);
					generated.append(c - b, alphabet[0]);
					generated.append(Args._length - c, alphabet[1]);
					output.push_back(generated);
				}
			}
		}
	}
	else {
		throw new std::exception("No implementation for given block number!");
	}

	std::vector<std::string> output;
	if (Args._blockCount == 2) { // end of recursion
		for (unsigned int i = 1; i < Args._length; i++) {
			output.push_back(std::string(i, alphabet[(unsigned int)Args.posAlphabetStart]) + std::string(Args._length - i, alphabet[(unsigned int)!Args.posAlphabetStart]));
		}
	}
	else {
		for (unsigned int i = 1; i < (Args._length - Args._blockCount - 1); i++) {

			generateSquaresArgs recursionArgs = {
				Args._blockCount - 1,
				Args._length - i,
				!Args.posAlphabetStart
			};

			for (auto& entry : generateSquares(recursionArgs)) {
				output.push_back(std::string(i, alphabet[(unsigned int)Args.posAlphabetStart]) + entry);
			}
		}
	}

	return output;
}