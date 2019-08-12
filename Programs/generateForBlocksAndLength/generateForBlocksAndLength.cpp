#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\types\word.hpp>
#include <asalib2\public\algorithms\generation\allWordsOfBlockCountUntilLength.hpp>

#include <common\tclap\CmdLine.h>

void printOutput(asalib2_ns::types::length nBlocks, asalib2_ns::types::length nLength, _STD vector<asalib2_ns::types::word> results, bool verbose = false)
{
	printf("-------------------------------------------\n");
	for (const auto& generatedWord : results)
	{
		printf("%s\n", verbose ? ((_STD string)generatedWord).c_str() : generatedWord.toPretty().c_str());
	}
	printf("-------------------------------------------\n");
}

int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Generated words for a given number of blocks and a maximum length", ' ', asalib2_ns::build);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information generation of words", cmd, false);
		TCLAP::ValueArg<asalib2_ns::types::length> cmd_inNumBlocks("b", "nBlocks", "Number of blocks in each generated word", false, 3, "number", cmd);
		TCLAP::ValueArg<asalib2_ns::types::length> cmd_inMaxLength("l", "nLength", "Maximum length of generated words", false, 50, "number", cmd);
		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();
		asalib2_ns::types::length nBlocks = cmd_inNumBlocks.getValue();
		asalib2_ns::types::length nLength = cmd_inMaxLength.getValue();

		printf("Generating all words of length %zu having %zu blocks . . .\n", nLength, nBlocks);

		auto generatedWords = asalib2_ns::algorithms::generation::allWordsOfBlockCountUntilLength({
			nBlocks,
			nLength
			});

		printf("Generated %zu words!\n", generatedWords.size());

		if (detailedOption)
		{
			printOutput(nBlocks, nLength, generatedWords, verboseOption);
		}

		printf("Program ended successfully!\n");
		return 0;

	}
	catch (TCLAP::ArgException& e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return -1;
}