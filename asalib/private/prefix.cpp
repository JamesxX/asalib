/// @file prefix.cpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Implement prefix functionality in library.

#include <asalib/public/library.h>
#include <asalib/public/prefix.hpp>
#include <asalib/public/thread_pool.hpp>

#include <algorithm>
#include <common/json.hpp>

#define asalib_prefix_MULTITHREAD

using namespace AbelianSquaresAnalysis;

asalib  AbelianSquaresAnalysis::prefix::substringAnalysisOutput::substringAnalysisOutput()
	: vector()
{
}

asalib  AbelianSquaresAnalysis::prefix::substringAnalysisOutput::substringAnalysisOutput(const prefix::substringAnalysisInput& base)
	: prefix::substringAnalysisInput(base), vector()
{
}

asalib AbelianSquaresAnalysis::prefix::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base)
	: morphism::morphismOutput(base)
{
}

asalib AbelianSquaresAnalysis::prefix::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base, const prefix::AnalysePrefixOutput& base2)
	: morphism::morphismOutput(base), prefix::AnalysePrefixOutput(base2)
{
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
		{"generatedPrefix",data.generatedPrefix},
		{"generatedPrefixLength", data.generatedPrefixLength},
		{"generatedPrefixRuns", data.runs},
		{"prefixAnalysis",{
			asalib_prefixanalysis_output_category("totalSquares", data.total),
			asalib_prefixanalysis_output_category("distinctSquares", data.distinct),
			asalib_prefixanalysis_output_category("nonequivalentSquares", data.nonequivalent),
			{"totalN_less_than_length_over_four", ((long)data.nonequivalent.trivial + (long)data.nonequivalent.nontrivial) < floor((long)data.generatedPrefixLength / 4)}
		}}
	};
}

#define asalib_prefix_substringanalysis_count_occurence(str, needle) std::count(str.begin(), str.end(), needle);

prefix::substringAnalysisOutput asalib AbelianSquaresAnalysis::prefix::AnalyseSubstring(substringAnalysisInput input) {
	
	// Setup return information
	prefix::substringAnalysisOutput output = (prefix::substringAnalysisOutput) input;

	// odd length substrings are not squares
	if (input.word.length() % 2 != 0) {
		return output; // isSqaure defaults to false
	}

	// Count first half
	types::parihkVector firstHalf = input.alphabet; // copy construct
	input.word.countOccurences(0, input.length / 2, firstHalf);

	// Count second half
	types::parihkVector secondHalf = input.alphabet; // copy construct
	input.word.countOccurences(input.length / 2, std::string::npos, secondHalf);

	if (firstHalf == secondHalf) {
		output.isSquare = true;
		output.vector = firstHalf;
		output.isTrivial = firstHalf.isTrivial();
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
#ifdef asalib_prefix_MULTITHREAD
	AbelianSquaresAnalysis::ThreadPool<prefix::substringAnalysisInput, prefix::substringAnalysisOutput> pool;
#endif

	types::parihkVector alphabet = input.countAlphabetSize();

	// For every even word length
	for (unsigned int len = 2; len <= input.length(); len += 2) {
		// for every valid start position
		for (unsigned int pos = 0; pos < (input.length() - len + 1); pos++) {
			prefix::substringAnalysisInput AnalysisInput;
			AnalysisInput.word = input.substr(pos, len);
			AnalysisInput.length = len;
			AnalysisInput.position = pos;
			AnalysisInput.alphabet = alphabet;

#ifdef asalib_prefix_MULTITHREAD
			pool.AddTask(prefix::AnalyseSubstring, AnalysisInput);
#else
			prefix::substringAnalysisOutput computation_output  = prefix::AnalyseSubstring(AnalysisInput);
			if (computation_output.isSquare)
				output.total.list.push_back(computation_output);
#endif
		}
	}

#ifdef asalib_prefix_MULTITHREAD
	pool.WaitForTasks();

	for (auto& computation_output : pool.GetResults()) {
		if (computation_output.isSquare)
			output.total.list.push_back(computation_output);
	}
#endif

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
	return (left.vector == right.vector);
}

bool asalib AbelianSquaresAnalysis::prefix::SquaresSortNoneqPredicate
(prefix::substringAnalysisOutput left, prefix::substringAnalysisOutput right) {
	return (left.vector > right.vector);
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