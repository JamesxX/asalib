/// @file prefix.cpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Implement prefix functionality in library.

#include <asalib/public/library.h>
#include <asalib/public/prefix.hpp>
#include <asalib/public/thread_pool.hpp>

#include <algorithm>
#include <common/json.hpp>

using namespace AbelianSquaresAnalysis;

asalib AbelianSquaresAnalysis::prefix::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base)
	: morphism::morphismOutput(base)
{
	// Copy construct prefixAnalysisOutput
}

asalib AbelianSquaresAnalysis::prefix::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base, const prefix::AnalysePrefixOutput& base2)
	: morphism::morphismOutput(base), prefix::AnalysePrefixOutput(base2)
{
	// Copy construct prefixAnalysisOutput
}

#define asalib_prefixanalysis_output_category(name, info)\
			{name, { \
				{"total", info.nontrivial + info.trivial},\
				{"trivial", info.trivial},\
				{"nontrivial", info.nontrivial}\
			}}

void asalib AbelianSquaresAnalysis::prefix::to_json(nlohmann::json& j, const prefixAnalysisOutput& data) {
	j = {
		{"morphismName", data.input.morphismName},
		{"morphism", data.input.morphism},
		{"prolongable",data.morphismAnalysis.prolongable},
		{"k_uniform", data.morphismAnalysis.k_uniform},
		{"success", data.morphismSuccess},
		{"startWord", data.input.startWord},
		{"lengthBound", data.input.lengthBound},
		{"generatedPrefix", data.generatedPrefix},
		{"generatedPrefixLength", data.generatedPrefixLength},
		{"generatedPrefixRuns", data.runs},
		{"prefixAnalysis",{
			asalib_prefixanalysis_output_category("totalSquares", data.total),
			asalib_prefixanalysis_output_category("distinctSquares", data.distinct),
			asalib_prefixanalysis_output_category("nonequivalentSquares", data.nonequivalent),
			{"totalN_less_than_length_over_four", (data.nonequivalent.trivial + data.nonequivalent.nontrivial) < floor(data.generatedPrefixLength / 4)}
		}}
	};
}

#define asalib_prefix_substringanalysis_count_occurence(str, needle) std::count(str.begin(), str.end(), needle);

prefix::substringAnalysisOutput asalib AbelianSquaresAnalysis::prefix::AnalyseSubstring(substringAnalysisInput input) {
	
	// Setup return information
	prefix::substringAnalysisOutput output;

	// odd length substrings are not squares
	if (input.word.length() % 2 != 0) {
		return output; // isSqaure defaults to false
	}

	// Count first half
	types::parihkVector firstHalf;
	std::string firstHalfSubString = input.word.substr(0, input.length / 2);
	firstHalf.a = asalib_prefix_substringanalysis_count_occurence(firstHalfSubString, 'a');
	firstHalf.b = asalib_prefix_substringanalysis_count_occurence(firstHalfSubString, 'b');
	//types::parihkVector firstHalf = substring.substr(0, substring.length() / 2).countOccurences();

	// Count second half
	types::parihkVector secondHalf;
	std::string secondHalfSubString = input.word.substr(input.length / 2, std::string::npos);
	secondHalf.a = asalib_prefix_substringanalysis_count_occurence(secondHalfSubString, 'a');
	secondHalf.b = asalib_prefix_substringanalysis_count_occurence(secondHalfSubString, 'b');
	//types::parihkVector secondHalf = substring.substr(substring.length() / 2).countOccurences();

	// substring is square if vectors for each side are equal
	if (firstHalf.a == secondHalf.a && firstHalf.b == secondHalf.b) {
		output.isSquare = true;
		output.vector.a = firstHalf.a;
		output.vector.b = firstHalf.b;

		if (firstHalf.a == 0 || firstHalf.b == 0) {
			output.isTrivial = true;
		}

		output.word = input.word;
		output.position = input.position;
		output.length = input.length;
	}

	return output;
}

prefix::prefixAnalysisOutput asalib AbelianSquaresAnalysis::prefix::AnalysePrefix(morphism::morphismOutput morphismOutput) {
	prefix::prefixAnalysisOutput prefixOutput(morphismOutput);
	prefix::AnalysePrefix(prefixOutput.generatedPrefix, prefixOutput);
	return prefixOutput;
}


void asalib AbelianSquaresAnalysis::prefix::AnalysePrefix(types::word input, prefix::AnalysePrefixOutput& output) {

	// Prepare thread pool
	AbelianSquaresAnalysis::ThreadPool<prefix::substringAnalysisInput, prefix::substringAnalysisOutput> pool;

	// Sanitize input
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);

	// For every even word length
	for (unsigned int len = 2; len <= input.length(); len += 2) {
		// for every valid start position
		for (unsigned int pos = 0; pos < (input.length() - len + 1); pos++) {
			prefix::substringAnalysisInput AnalysisInput;
			AnalysisInput.word = input.substr(pos, len);
			AnalysisInput.length = len;
			AnalysisInput.position = pos;

			pool.AddTask(prefix::AnalyseSubstring, AnalysisInput);
		}
	}

	pool.WaitForTasks();

	for (auto& computation_output : pool.GetResults()) {
		if (computation_output.isSquare)
			output.total.list.push_back(computation_output);
	}

	prefix::SquaresCountTrivials(output.total);

	// Distinct
	prefix::SquaresCategoriseInput distinctCategoriseInput(output.total.list, output.distinct.list);
	distinctCategoriseInput.sort = prefix::SquaresSortDistinctPredicate;
	distinctCategoriseInput.comparison = prefix::SquaresComparisonDistinctPredicate;
	prefix::SquaresCategorise(distinctCategoriseInput);
	prefix::SquaresCountTrivials(output.distinct);

	// Non-equivalent
	prefix::SquaresCategoriseInput nonequivalentCategoriseInput(output.distinct.list, output.nonequivalent.list);
	nonequivalentCategoriseInput.sort = prefix::SquaresSortNoneqPredicate;
	nonequivalentCategoriseInput.comparison = prefix::SquaresComparisonNoneqPredicate;
	prefix::SquaresCategorise(nonequivalentCategoriseInput);
	prefix::SquaresCountTrivials(output.nonequivalent);
}

bool asalib AbelianSquaresAnalysis::prefix::SquaresComparisonDistinctPredicate
(prefix::substringAnalysisOutput left, prefix::substringAnalysisOutput right) {
	return left.word == right.word;
}

bool asalib AbelianSquaresAnalysis::prefix::SquaresSortDistinctPredicate
(prefix::substringAnalysisOutput left, prefix::substringAnalysisOutput right) {
	return left.word < right.word;
}

bool asalib AbelianSquaresAnalysis::prefix::SquaresComparisonNoneqPredicate
(prefix::substringAnalysisOutput left, prefix::substringAnalysisOutput right) {
	return (left.vector.a == right.vector.a && left.vector.b == right.vector.b);
}

bool asalib AbelianSquaresAnalysis::prefix::SquaresSortNoneqPredicate
(prefix::substringAnalysisOutput left, prefix::substringAnalysisOutput right) {
	if (left.vector.a != right.vector.a) {
		return left.vector.a > right.vector.a;
	}
	return left.vector.b > right.vector.b;
}

asalib AbelianSquaresAnalysis::prefix::SquaresCategoriseInput::SquaresCategoriseInput(std::vector<substringAnalysisOutput>& in, std::vector<substringAnalysisOutput>& out):
	_in(in), _out(out)
{
	// constructor
}

void asalib AbelianSquaresAnalysis::prefix::SquaresCategorise(prefix::SquaresCategoriseInput input) {
	input._out = input._in;
	std::sort(input._out.begin(), input._out.end(), input.sort);
	auto last_dist = std::unique(input._out.begin(), input._out.end(), input.comparison);
	input._out.erase(last_dist, input._out.end());
}

void asalib  AbelianSquaresAnalysis::prefix::SquaresCountTrivials(prefix::prefixAnalysisOutputSquareType& input) {
	for (auto& square : input.list) {
		if (square.isTrivial) {
			input.trivial++;
		}
		else {
			input.nontrivial++;
		}
	}
}