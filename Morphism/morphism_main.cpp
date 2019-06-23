/*
	morphism/morphism_main.cpp
	Entry point for morphism program (program 1)

	Morphism.exe  -i <string> [-o <string>] [-r] [-v] [--] [--version] [-h]
*/

#include <asalib/public/library.h>
#include <asalib/public/morphism.hpp>
#include <asalib/public/utility.hpp>
#include <common/json.hpp>
#include <common/tclap/CmdLine.h>
#include <iostream>

using namespace AbelianSquaresAnalysis;

#define asalib_VERBOSE(v,...) if (v) printf(##__VA_ARGS__)


int main(int argc, char* argv[]) {

	try {
		// Setup command line interface
		TCLAP::CmdLine cmd("Generate prefixes from a list of morphisms", ' ', AbelianSquaresAnalysis::BUILD);
		TCLAP::SwitchArg cmd_verbose("v", "verbose", "Verbose program output", cmd, false);
		TCLAP::SwitchArg cmd_outputRelativity("r", "relative", "Set output directory relative to input file", cmd, false);
		TCLAP::ValueArg<std::string> cmd_outDir("o", "outdir", "Output directory", false, "output", "string", cmd);
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
		morphism::morphismInput input_cpp = utility::LoadClassFromFile<morphism::morphismInput>(input_file);

		// Run morphism!
		asalib_VERBOSE(verboseOption, "Running morphisms . . .\n");
		std::vector<morphism::morphismOutput> output = morphism::RunMorphisms(input_cpp);
#ifdef _WIN64
		asalib_VERBOSE(verboseOption, "%llu morphisms iterated\n", output.size());
#else
		asalib_VERBOSE(verboseOption, "%u morphisms iterated\n", output.size());
#endif

		// Prepare output directory
		asalib_VERBOSE(verboseOption, "Preparing output directory\n");
		std::string parent_directory = utility::GetParentDirectory(input_file);
		if (outputRelativityOption) {
			asalib_VERBOSE(verboseOption, "Output is relative to executable\n");
			parent_directory = utility::CurrentExecutablePath();
		}
		std::string outputDirectory = utility::PrepareSubdirectory(parent_directory, output_directory);

		// for each generated prefix
		for (const auto& output_entry : output) {

			// Output to file
			std::string file_location = outputDirectory + "\\" + output_entry.input.morphismName + output_entry.input.startWord + ".out";
			asalib_VERBOSE(verboseOption, "Generating output file \"%s\"\n", file_location.c_str());
			utility::SaveClassToFile<morphism::morphismOutput>(file_location, output_entry);

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