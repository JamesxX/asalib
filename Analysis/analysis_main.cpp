/*
	analysis/analysis_main.cpp
	Entry point for analysis program (program 2)

	Analysis.exe  -i <string> [-o <string>] [-r] [-v] [--] [--version] [-h]
*/

#include <asalib/public/library.h>
#include <asalib/public/squares.hpp>
#include <asalib/public/utility.hpp>
#include <common/tclap/CmdLine.h>

using namespace AbelianSquaresAnalysis;

int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Analyse abelian squares in a given prefix", ' ', AbelianSquaresAnalysis::BUILD);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_outputRelativity("r", "relative", "Set output directory relative to input file", cmd, false);
		TCLAP::ValueArg<std::string> cmd_outDir("o", "outdir", "Output directory", false, "analysis", "string", cmd);
		TCLAP::ValueArg<std::string> cmd_inFile("i", "input", "Input morphism file", true, "nonInput", "string", cmd);
		cmd.parse(argc, argv);

		// Get values from command line
		std::string input_file = cmd_inFile.getValue();
		std::string output_directory = cmd_outDir.getValue();
		bool verboseOption = cmd_verbose.getValue();
		bool outputRelativityOption = cmd_outputRelativity.getValue();

		// Notify of verbose option
		//asalib_VERBOSE(verboseOption, "Verbose program output enabled.\n");

		// Load input from json
		asalib_VERBOSE(verboseOption, "Loading into program from file \"%s\"\n", input_file.c_str());
		morphism::morphismOutput input_cpp = utility::LoadClassFromFile<morphism::morphismOutput>(input_file);

		// Analyse prefix
		asalib_VERBOSE(verboseOption, "Analysing prefix . . .\n");
		squares::prefixAnalysisOutput analysisOutput(input_cpp);
		squares::AnalyseWord(analysisOutput.generatedPrefix, analysisOutput);
		asalib_VERBOSE(verboseOption, "Analysis complete!\n");

		// Prepare output directory
		asalib_VERBOSE(verboseOption, "Preparing output directory\n");
		std::string parent_directory = utility::GetParentDirectory(input_file);
		if (outputRelativityOption) {
			asalib_VERBOSE(verboseOption, "Output is relative to executable\n");
			parent_directory = utility::CurrentExecutablePath();
		}
		std::string outputDirectory = utility::PrepareSubdirectory(parent_directory, output_directory);

		// Output to file
		std::string file_location = outputDirectory + "\\" + analysisOutput.input.morphismName + analysisOutput.input.startWord + ".json";
		printf("Generating output file \"%s\"\n", file_location.c_str());
		utility::SaveClassToFile<squares::prefixAnalysisOutput>(file_location, analysisOutput);

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
