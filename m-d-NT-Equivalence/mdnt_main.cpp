/*
	SingleWord/singleword_main.cpp
	Entry point for single word analysis program.

	SingleWord.exe  [-d] [-v] [--] [--version] [-h] <string> ...
*/

#include <asalib/public/library.h>
#include <asalib/public/squares.hpp>
#include <asalib/public/types.hpp>
#include <common/tclap/CmdLine.h>
#include <iostream>
#include <string>
#include <array>
#include <numeric>

using namespace AbelianSquaresAnalysis;

// Test for block counts 4, 5, 6, and 7. Implement 4 only to begin with

#pragma region generation

//template<size_t blockCount>
struct generatedWordOutput
{
	//std::array<unsigned int, blockCount> blockLength;

	inline
		generatedWordOutput(unsigned int _desiredBlockCount = 0)
		: blockCount{ _desiredBlockCount }, blockLength(blockCount)
	{
		//
	}

	inline 
		void setBlockCount(unsigned int _desiredBlockCount)
	{
		blockCount = _desiredBlockCount;
		blockLength.resize(blockCount);
	}

	std::vector<unsigned int> blockLength;
	unsigned int blockCount;
	unsigned int lengthBound;
	std::string generatedWord;
};

template <template<typename...> class R = std::vector,
	typename Top,
	typename Sub = typename Top::value_type>
	R<typename Sub::value_type> flatten(Top const& all)
{
	using std::begin;
	using std::end;

	R<typename Sub::value_type> accum;

	for (auto& sub : all)
		accum.insert(end(accum), begin(sub), end(sub));

	return accum;
}

//template<size_t blockCount>
std::vector<generatedWordOutput> generatedBlockLengths(unsigned int blockCount, unsigned int lengthBound)
{
	// 2D Array [length][unqiueWord]
	std::vector<std::vector<generatedWordOutput>> output;

	// Start with the generic case of blocks length 1
	generatedWordOutput genericCase(blockCount);
	//genericCase.blockLength.fill(1);
	std::fill(genericCase.blockLength.begin(), genericCase.blockLength.end(), 1);
	genericCase.lengthBound = lengthBound;
	std::vector<generatedWordOutput> outputLength_blockCount = { genericCase };
	output.push_back(outputLength_blockCount);

	std::vector<generatedWordOutput> *previousLengthVector = &output.back();

	while(output.size() < (lengthBound - blockCount) )
	{

		std::vector<generatedWordOutput> outputLength_current;

		for (auto& entry : *previousLengthVector)
		{
			for (unsigned int currentWorkingBlock = 0; currentWorkingBlock < blockCount; currentWorkingBlock++)
			{
				generatedWordOutput Copy(entry);
				Copy.blockLength[currentWorkingBlock]++;
				outputLength_current.push_back(Copy);
			}
		}

		output.push_back(outputLength_current);
		previousLengthVector = &outputLength_current;

	}

	return flatten(output);

}

const char alphabet[] = { 'A', 'B' };

//template<size_t blockCount>
void expandGeneratedBlockLengths(std::vector<generatedWordOutput>& input)
{
	for (generatedWordOutput& entry : input)
	{
		entry.generatedWord.reserve(std::accumulate(entry.blockLength.begin(), entry.blockLength.end(), 0));

		for (unsigned int currentWorkingBlock = 0; currentWorkingBlock < entry.blockLength.size(); currentWorkingBlock++)
		{
			entry.generatedWord.append(entry.blockLength[currentWorkingBlock], alphabet[currentWorkingBlock % 2]);
		}
	}
}


#pragma endregion

#pragma region equivalence class predicate

//template<size_t blockCount>
struct generatedOutputPostAnalysis_t
{
	generatedWordOutput generatedOutput;
	squares::AnalysisOutput squaresAnalysis;
};

//template<size_t blockCount>
void generatedOutputAnalysis(generatedWordOutput& generatedOutput)
{
	generatedOutputPostAnalysis_t analysisOutput;
	analysisOutput.generatedOutput = generatedOutput;

	if (analysisOutput.generatedOutput.generatedWord.length() == 0) 
	{
		// Error, should have already been expanded
	}

	squares::AnalyseWord(analysisOutput.generatedOutput.generatedWord, analysisOutput.squaresAnalysis);

}

//template<size_t blockCount>
bool equivalencePredicateBlockCount(const generatedWordOutput& left, const generatedWordOutput& right)
{
	if (left.blockCount % 2 == 0) // Even block lengths
	{
		return (left.blockLength[0] == right.blockLength[0]) && (left.blockLength[1] == right.blockLength[1]);
	}
	else { // odd block lengths
		return (left.blockLength[0] == right.blockLength[0]);
	}
}

//template<size_t blockCount>
bool equivalencePredicateMDNT(const generatedOutputPostAnalysis_t& left, const generatedOutputPostAnalysis_t& right)
{
	// Requires generatedOutputAnalysis to have been called on both!!
	
	// Is NT-D count equal for both?
	if (left.squaresAnalysis.distinct.nontrivial != right.squaresAnalysis.distinct.nontrivial) {
		return false;
	}

	// Is left a permutation of right?
	return std::is_permutation(left.begin(), left.end(), right.begin());
}

#pragma endregion

int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Generate set for equivalence class given length upper bound and block count", ' ', AbelianSquaresAnalysis::BUILD);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information on found squares", cmd, false);
		TCLAP::ValueArg<unsigned int> cmd_inNumBlocks("b", "blocks", "Input morphism file", false, 4, "number", cmd);
		TCLAP::ValueArg<unsigned int> cmd_inMaxLength("l", "length", "Input morphism file", false, 50, "number", cmd);
		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();
		unsigned int inNumBlocks = cmd_inNumBlocks.getValue();
		unsigned int inMaxLength = cmd_inMaxLength.getValue();

		// generate blocklengths
		std::vector<generatedWordOutput> generatedBlockLengths(inMaxLength);

		asalib_VERBOSE(verboseOption, "Program completed successfully\n");
		asalib_wait_debug();
		return 0;

	}
	catch (TCLAP::ArgException& e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	asalib_wait_always();
	return 150; // Generic error code
}