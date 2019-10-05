#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\types\word.hpp>

#include <asalib2\public\algorithms\analysis\allSquares.hpp>
#include <asalib2\public\algorithms\analysis\categoriseSquares.hpp>

#include <common\tclap\CmdLine.h>

asalib2_ns::types::word 
constructByBlockIt
(const asalib2_ns::types::word& input, asalib2_ns::types::word::blocks_representation_t::const_iterator begin, asalib2_ns::types::word::blocks_representation_t::const_iterator end)
{
	asalib2_ns::types::word output;
	output.m_blocks.assign(begin, end);
	return output;
}

asalib2_ns::types::boolean 
isWordDNTEqauivalent
(const asalib2_ns::types::word& input)
{

	asalib2_ns::types::word firstHalf;
	asalib2_ns::types::word secondHalf;

	// Depends on number of blocks:
	if (input.m_blocks.size() % 2 == 0) // even number of blocks
	{

	}
	else // odd number of blocks
	{

	}
}

int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Analyse abelian squares in a given word", ' ', asalib2_ns::build);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information on found squares", cmd, false);
		TCLAP::UnlabeledMultiArg<std::string> cmd_inputWords("words", "List of words to analyse", true, "string", cmd, false);
		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();


		
		printf("Program ended successfully!\n");
		return 0;

	}
	catch (TCLAP::ArgException& e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return -1;
}