#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\types\word.hpp>

#include <asalib2\public\algorithms\analysis\allSquares.hpp>
#include <asalib2\public\algorithms\analysis\categoriseSquares.hpp>
#include <asalib2\public\algorithms\generation\allWordsOfBlockCountUntilLength.hpp>

#include <common\tclap\CmdLine.h>

void categoricalOutput(const char* name, const asalib2_ns::algorithms::analysis::squares_t& info, bool detail = false, bool verbose = false)
{
	printf("\tFound %zu %s squares:\n", info.count, name);
	printf("\t\tOf which %zu trivial and %zu non-trivial.\n", info.m_Trivial.count, info.m_NonTrivial.count);

	if (detail)
	{
		printf("\t\tOutputing detailed information . . .\n");

		printf("\t\t\tTrivial squares:\n");
		for (const auto& square : info.m_Trivial.list)
		{
			printf("\t\t\t\t\"%s\" at position %zu, %s\n", 
				verbose ? ((std::string)square.m_Word).c_str() : square.m_Word.toPretty().c_str(),
				square.m_Position, 
				((std::string)square.m_Vector).c_str());
		}

		printf("\t\t\tNon-trivial squares:\n");
		for (const auto& square : info.m_NonTrivial.list)
		{
			printf("\t\t\t\t\"%s\" at position %zu, %s\n", 
				verbose ? ((std::string)square.m_Word).c_str() : square.m_Word.toPretty().c_str(),
				square.m_Position, 
				((std::string)square.m_Vector).c_str());
		}
		printf("-------------------------------------------\n");
	}
}

void computationalResults(
	const asalib2_ns::algorithms::analysis::categorised_squares_t& output, 
	const asalib2_ns::types::size length, 
	bool detailedOption = false, 
	bool verboseOption = false)
{
	printf("\tComputational results:\n");
	printf("\t\tTotal a-squares against length : %zu / %zu = %f\n", output.m_All.count, length, ((float) output.m_All.count) / length);
	printf("\t\tDistinct a-squares against length : %zu / %zu = %f\n", output.m_Distinct.count, length, ((float)output.m_Distinct.count) / length);
	printf("\t\tNon-equivalent a-squares against length : %zu / %zu = %f\n", output.m_Nonequivalent.count, length, ((float)output.m_Nonequivalent.count) / length);
	printf("-------------------------------------------\n");
}

void categoricalSummary(
	const asalib2_ns::algorithms::analysis::categorised_squares_t& output, 
	const asalib2_ns::types::length length,
	bool detailedOption = false,
	bool verboseOption = false)
{
	categoricalOutput("total", output.m_All, detailedOption, verboseOption);
	categoricalOutput("distinct", output.m_Distinct, detailedOption, verboseOption);
	categoricalOutput("non-equivalent", output.m_Nonequivalent, detailedOption, verboseOption);
	computationalResults(output, length, detailedOption, verboseOption);
	printf("-------------------------------------------\n");
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
		std::vector<std::string> inputWords = cmd_inputWords.getValue();

		// For every input word
		for (const auto& word_raw : inputWords) 
		{
			asalib2_ns::types::word input(word_raw);

			printf("Analysing \"%s\" . . .\n", ((std::string)input).c_str());

			auto analysisOutput = asalib2_ns::algorithms::analysis::categoriseSquares(
				asalib2_ns::algorithms::analysis::allSquares(input)
			);

			categoricalSummary(analysisOutput, input.length(), detailedOption, verboseOption);
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