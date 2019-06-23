/*
	SingleWord/singleword_main.cpp
	Entry point for single word analysis program.

	SingleWord.exe  [-d] [-v] [--] [--version] [-h] <string> ...
*/

#include <asalib/public/library.h>
#include <asalib/public/prefix.hpp>
#include <asalib/public/types.hpp>
#include <common/tclap/CmdLine.h>
#include <iostream>
#include <string>

using namespace AbelianSquaresAnalysis;

#define asalib_VERBOSE(v,...) if (v) printf(##__VA_ARGS__)

#ifdef _WIN64
#define asalib_singleword_dictionary_found "\tFound %llu "
#define asalib_singleword_dictionary_ofwhich "\t\tOf which %llu trivial and %llu non-trivial.\n"
#define asalib_singleword_dictionary_detailedinformation "\t\tOutputing detailed information:\n"
#define asalib_singleword_dictionary_detail "\t\t\t\"%s\" at position %zu, %s\n"
#else
#define asalib_singleword_dictionary_found "\tFound %lu "
#define asalib_singleword_dictionary_ofwhich "\t\tOf which %lu trivial and %lu non-trivial.\n"
#define asalib_singleword_dictionary_detailedinformation "\t\tOutputing detailed information on total squares:\n"
#define asalib_singleword_dictionary_detail "\t\t\t\"%s\" at position %zu, %s\n"
#endif

inline void PrintDetailedInformationOnType(prefix::prefixAnalysisOutputSquareType& typeOutput) {
	printf(asalib_singleword_dictionary_detailedinformation);
	for (auto& square : typeOutput.list) {
		printf(asalib_singleword_dictionary_detail, square.word.c_str(), square.position, ((std::string)square.vector).c_str());
	}
}

#define asalib_singleword_type_output(type, wordOutput, detailed) \
	printf( asalib_singleword_dictionary_found #type " abelian squares:\n", wordOutput.type.trivial + wordOutput.type.nontrivial);\
	printf( asalib_singleword_dictionary_ofwhich, wordOutput.type.trivial, wordOutput.type.nontrivial);\
	if ( detailed ) PrintDetailedInformationOnType(wordOutput.type);


int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Analyse abelian squares in a given word", ' ', AbelianSquaresAnalysis::BUILD);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information on found squares", cmd, false);
		TCLAP::UnlabeledMultiArg<std::string> cmd_inputWords("words", "List of words to analyse", true, "string", cmd, false);
		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();
		std::vector<std::string> inputWords = cmd_inputWords.getValue();

		// For every input word
		for (const auto& word : inputWords) {

			asalib_VERBOSE(verboseOption, "Analysing \"%s\" . . .\n", word.c_str());
			prefix::AnalysePrefixOutput wordOutput;
			prefix::AnalysePrefix(word, wordOutput);

			asalib_singleword_type_output(total, wordOutput, detailedOption);
			asalib_singleword_type_output(distinct, wordOutput, detailedOption);
			asalib_singleword_type_output(nonequivalent, wordOutput, detailedOption);

		}

		asalib_VERBOSE(verboseOption, "Program completed successfull\n");
		asalib_wait_debug();
		return 0;

	}
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	asalib_wait_always();
	return 150; // Generic error code
}