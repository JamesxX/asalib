/*
	RawSquaresByBlock/rawsquares_main.cpp
*/

#include <asalib/public/library.h>
#include <asalib/public/rawsquares.hpp>
#include <asalib/public/generation.hpp>
#include <asalib/public/types.hpp>

#include <common/tclap/CmdLine.h>

#include <iostream>
#include <string>
#include <functional>

using namespace AbelianSquaresAnalysis;

int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Generates words having a number of blocks and a given length, and checks for raw abelian sqaures.", ' ', AbelianSquaresAnalysis::BUILD);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information on found squares", cmd, false);
		TCLAP::SwitchArg cmd_outputRelativity("r", "relative", "Set output directory relative to input file", cmd, false);
		TCLAP::ValueArg<std::string> cmd_outFile("o", "outfile", "Output file", false, "output", "string", cmd);
		TCLAP::ValueArg<unsigned int> cmd_inNumBlocks("b", "blocks", "Input morphism file", false, 3, "number", cmd);
		TCLAP::ValueArg<unsigned int> cmd_inMaxLength("l", "length", "Input morphism file", false, 50, "number", cmd);
		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();
		bool outputRelativity = cmd_outputRelativity.getValue();
		std::string outputFile = cmd_outFile.getValue();
		unsigned int inNumBlocks = cmd_inNumBlocks.getValue();
		unsigned int inMaxLength = cmd_inMaxLength.getValue();

		squares::raw::isRawSquareOutputReason outputCode;
		std::vector<std::string> squares = generation::binary::generateSquares({ inNumBlocks, inMaxLength });
		
		for (auto& square : squares) {
			bool isRaw = isRawSquare(square, outputCode);
			std::string pretty = ((types::word)square).prettyPrint();

			if (isRawSquare(square, outputCode)) {
				printf("Generated raw square for %u blocks of length %u : %s\n", inNumBlocks, inMaxLength, pretty.c_str());
			}
		}

		std::vector<std::string> prettyRawSquares;

		asalib_VERBOSE(verboseOption, "Program completed successfully\n");
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