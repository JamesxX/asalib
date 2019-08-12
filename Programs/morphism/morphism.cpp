#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\types\word.hpp>
#include <asalib2\public\algorithms\generation\applyMorphismUntilLength.hpp>
#include <asalib2\public\algorithms\analysis\allSquares.hpp>
#include <asalib2\public\algorithms\analysis\categoriseSquares.hpp>

#include <common\tclap\CmdLine.h>

void categoricalOutput(const char* name, const asalib2_ns::algorithms::analysis::squares_t& info, bool detail = false, bool verbose = false)
{
	printf("\tFound %zu %s squares:\n", info.count, name);
	printf("\t\tOf which %zu trivial and %zu non-trivial.\n", info.m_Trivial.count, info.m_NonTrivial.count);

	if (verbose)
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
	printf("\t\tTotal non-trivial squares against length : %zu / %zu = %f\n", output.m_All.m_NonTrivial.count, length, ((float)output.m_All.m_NonTrivial.count) / length);
	printf("\t\tDistinct non-trivial squares against length : %zu / %zu = %f\n", output.m_Distinct.m_NonTrivial.count, length, ((float)output.m_Distinct.m_NonTrivial.count) / length);
	printf("\t\tNon-equivalent non-trivial squares against length : %zu / %zu = %f\n", output.m_Nonequivalent.m_NonTrivial.count, length, ((float)output.m_Nonequivalent.m_NonTrivial.count) / length);
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
		TCLAP::CmdLine cmd("Apply a given morphism to a word until a minimum length. 0 is a special mapping meaning mortal.", ' ', asalib2_ns::build);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_detailed("d", "detailed", "Output detailed information generation of words", cmd, false);
		TCLAP::ValueArg<_STD string> inAMapping("a", "A-Mapping", "String to which occuences of A map", false, "a", "string", cmd);
		TCLAP::ValueArg<_STD string> inBMapping("b", "B-Mapping", "String to which occuences of B map", false, "b", "string", cmd);
		TCLAP::ValueArg<asalib2_ns::types::length> cmd_inMaxLength("l", "nLength", "Maximum length of generated words", false, 50, "number", cmd);
		//TCLAP::ValueArg<asalib2_ns::types::length> cmd_inMaxIterations("l", "nLength", "Maximum length of generated words", false, 50, "number", cmd);
		TCLAP::UnlabeledMultiArg<std::string> cmd_inputWords("words", "List of words to upon which to apply the morphism", true, "string", cmd, false);

		cmd.parse(argc, argv);

		// Get values from command line
		bool verboseOption = cmd_verbose.getValue();
		bool detailedOption = cmd_detailed.getValue();
		asalib2_ns::types::word AMapping;
		asalib2_ns::types::word BMapping;
		asalib2_ns::types::length nLength = cmd_inMaxLength.getValue();
		std::vector<std::string> inputWords = cmd_inputWords.getValue();

		if (inAMapping.getValue() != "0")
		{
			AMapping = asalib2_ns::types::word(inAMapping.getValue());
		}
		
		if (inBMapping.getValue() != "0")
		{
			BMapping = asalib2_ns::types::word(inBMapping.getValue());
		}

		printf("-------------------------------------------\n");
		printf("The following morphism is currently being used: \n");
		printf("\t A -> %s\n", inAMapping.getValue().c_str());
		printf("\t B -> %s\n", inBMapping.getValue().c_str());

		printf("\nMinimum length a word must achieve is %zu in %u iterations\n", nLength, asalib2_public_algorithms_generatin_applyMorphismUntilLength_MaxItterations);
		printf("-------------------------------------------\n");

		asalib2_ns::types::morphism morphism(AMapping, BMapping);

		for (const auto& input : inputWords)
		{
			asalib2_ns::types::word inputWord(input);
			printf("Analysing the following word: %s . . .\n", verboseOption ? ((_STD string)inputWord).c_str() : inputWord.toPretty().c_str());

			asalib2_ns::types::word outputWord = asalib2_ns::algorithms::generation::applyMorphismUntilLength(inputWord, morphism, nLength);
			printf("Generated word: %s\n", verboseOption ? ((_STD string)outputWord).c_str() : outputWord.toPretty().c_str());

			printf("Running allSquares algorithm . . .\n");

			auto analysisOutput = asalib2_ns::algorithms::analysis::categoriseSquares(
				asalib2_ns::algorithms::analysis::allSquares(outputWord)
			);

			categoricalSummary(analysisOutput, outputWord.length(), detailedOption, verboseOption);
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