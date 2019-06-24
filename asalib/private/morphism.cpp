/// @file morphism.cpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Implement morphism analysis functionality in library.

#include <asalib/public/library.h>
#include <asalib/public/types.hpp>
#include <asalib/public/morphism.hpp>
#include <asalib/public/thread_pool.hpp>

#include <common/json.hpp>

using namespace AbelianSquaresAnalysis::morphism;

void asalib AbelianSquaresAnalysis::morphism::from_json(const nlohmann::json& j, morphismInput& data) {
	j.at("morphisms").get_to(data.morphisms);
	j.at("settings").at("lengthBound").get_to(data.settings.lengthBound);
	j.at("settings").at("startWords").get_to(data.settings.startWords);
}

void asalib AbelianSquaresAnalysis::morphism::to_json(nlohmann::json& j, const morphismOutput& data) {
	j = {
		{"morphismName", data.input.morphismName},
		{"morphism", data.input.morphism},
		{"prolongable", data.morphismAnalysis.prolongable},
		{"k_uniform", data.morphismAnalysis.k_uniform},
		{"success", data.morphismSuccess},
		{"startWord", data.input.startWord},
		{"lengthBound", data.input.lengthBound},
		{"generatedPrefix", data.generatedPrefix},
		{"generatedPrefixLength", data.generatedPrefixLength},
		{"generatedPrefixRuns", data.runs}
	};
}

void asalib AbelianSquaresAnalysis::morphism::from_json(const nlohmann::json& j, morphismOutput& data) {
	j.at("morphismName").get_to(data.input.morphismName);
	j.at("morphism").get_to(data.input.morphism);
	j.at("prolongable").get_to(data.morphismAnalysis.prolongable);
	j.at("k_uniform").get_to(data.morphismAnalysis.k_uniform);
	j.at("success").get_to(data.morphismSuccess);
	j.at("startWord").get_to(data.input.startWord);
	j.at("lengthBound").get_to(data.input.lengthBound);
	j.at("generatedPrefix").get_to(data.generatedPrefix);
	j.at("generatedPrefixLength").get_to(data.generatedPrefixLength);
	j.at("generatedPrefixRuns").get_to(data.runs);
}


asalib std::vector<morphismOutput> AbelianSquaresAnalysis::morphism::RunMorphisms(morphismInput input) {
	// Prepare thread pool
	AbelianSquaresAnalysis::ThreadPool<morphismOutput::inputSettings, morphismOutput> pool;

	// for each morphism
	for (auto morphism : input.morphisms) {

		// for each starting word
		for (const auto& startingWord : input.settings.startWords) {

			// Prepare thread callable arguments
			morphismOutput::inputSettings RunMorphismSingle_input;
			RunMorphismSingle_input.morphismName = morphism.first;
			RunMorphismSingle_input.morphism = morphism.second;
			RunMorphismSingle_input.startWord = startingWord;
			RunMorphismSingle_input.lengthBound = input.settings.lengthBound;

			// Add task into pool
			pool.AddTask(AbelianSquaresAnalysis::morphism::RunMorphismSingle, RunMorphismSingle_input);
		}

	}

	// Block main thread until tasks are complete
	pool.WaitForTasks();

	// Once all tasks complete, return results
	return pool.GetResults();
}

/// @warning Undefined behaviour if a morphism is missing a mapping for a character to which it is applied. E.g if there is no mapping for 'C', yet 'C' appears in either the start word or a generated prefix.
/// @warning Currently '0' represents mortal, however the '0' character may appear in final prefix. Consider using an empty string to represent mortal.
asalib morphismOutput AbelianSquaresAnalysis::morphism::RunMorphismSingle(morphismOutput::inputSettings input) {

	// Prepare output struct
	morphismOutput output;
	output.input = input;

	// Analyse the morphism
	size_t k_length = 0;
	bool k_uniform = true;
	for (auto& morphismPair : input.morphism) {

		// Check for prolongables (sanitized to lower)
		if (tolower(morphismPair.first.front()) == tolower(morphismPair.second.front())) {
			output.morphismAnalysis.prolongable.push_back(morphismPair.first);
		}

		// Check for k-uniformity
		if (!k_uniform) continue; // Don't continue these checks if it isn't k-uniform
		if (k_length == 0) {
			k_length = morphismPair.second.length(); // set the comparison variable to length of arbitrary transformation;
			continue;
		}
		if (k_length != morphismPair.second.length()) k_uniform = false; // Only need one not to be equal
	}
	if (k_uniform) output.morphismAnalysis.k_uniform = k_length;

	// Prepare morphism itteration
	output.generatedPrefix = AbelianSquaresAnalysis::types::word(input.startWord);

	// iterate the following until length is greater than input.settings.lengthBound
	// If the number of runs exceeds twice the length bound, the morphism is considered to have failed
	// This restriction will need further developement on the implementation of mortals
	while (output.generatedPrefix.length() < output.input.lengthBound && output.runs < 2 * output.input.lengthBound) {
		// copy generated
		std::string _iterationOutput = "";

		for (auto character : output.generatedPrefix) {
			// No check will be done if the prefix contains a character that is not part of a morphism
			_iterationOutput += output.input.morphism.at(std::string(1, character));
		}
		output.generatedPrefix = _iterationOutput;
		output.runs++;
	}


	if (output.runs < 2 * output.input.lengthBound) output.morphismSuccess = true;
	output.generatedPrefixLength = output.generatedPrefix.length();

	return output;
}
