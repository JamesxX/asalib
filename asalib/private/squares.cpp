/// @file squares.cpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Implement prefix functionality in library.

#include <asalib/public/library.h>
#include <asalib/public/squares.hpp>
#include <asalib/public/thread_pool.hpp>

#include <algorithm>
#include <common/json.hpp>

#define asalib_prefix_MULTITHREAD

using namespace AbelianSquaresAnalysis;

asalib AbelianSquaresAnalysis::squares::substringAnalysisOutput::substringAnalysisOutput()
	: vector()
{
}

asalib AbelianSquaresAnalysis::squares::substringAnalysisOutput::substringAnalysisOutput(const squares::substringAnalysisInput& base)
	: squares::substringAnalysisInput(base), vector()
{
}

asalib AbelianSquaresAnalysis::squares::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base)
	: morphism::morphismOutput(base)
{
}

asalib AbelianSquaresAnalysis::squares::prefixAnalysisOutput::prefixAnalysisOutput(const morphism::morphismOutput& base, const squares::AnalysisOutput& base2)
	: morphism::morphismOutput(base), squares::AnalysisOutput(base2)
{
}

#define asalib_prefixanalysis_output_category(name, info)\
			{name, { \
				{"total", info.nontrivial + info.trivial},\
				{"trivial", info.trivial},\
				{"nontrivial", info.nontrivial}\
			}}

void asalib AbelianSquaresAnalysis::squares::to_json(nlohmann::json& j, const prefixAnalysisOutput& data) {
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

squares::substringAnalysisOutput asalib AbelianSquaresAnalysis::squares::AnalyseSubstring(substringAnalysisInput input) {
	
	// Setup return information
	squares::substringAnalysisOutput output = (squares::substringAnalysisOutput) input;

	// odd length substrings are not squares
	if (input.length % 2 != 0) {
		return output; // isSqaure defaults to false
	}

	// Count first half
	types::parihkVector firstHalf = input.alphabet; // copy construct
	std::string_view firstHalfView = input.word.substr(input.position, input.length / 2);
	for (auto& alphabetCharacter : firstHalf) {
		alphabetCharacter.second = std::count(firstHalfView.begin(), firstHalfView.end(), alphabetCharacter.first);
	}

	// Count second half
	types::parihkVector secondHalf = input.alphabet; // copy construct
	std::string_view secondHalfView = input.word.substr(input.position + input.length / 2, input.length / 2);
	for (auto& alphabetCharacter : secondHalf) {
		alphabetCharacter.second = std::count(secondHalfView.begin(), secondHalfView.end(), alphabetCharacter.first);
	}

	if (firstHalf == secondHalf) {
		output.isSquare = true;
		output.vector = firstHalf;
		output.isTrivial = firstHalf.isTrivial();
		output.square = types::word(std::string(input.word.substr(input.position, input.length)));
	}

	return output;
}

squares::prefixAnalysisOutput asalib AbelianSquaresAnalysis::squares::AnalysePrefix(morphism::morphismOutput morphismOutput) {
	squares::prefixAnalysisOutput prefixOutput(morphismOutput);
	squares::AnalyseWord(prefixOutput.generatedPrefix, prefixOutput);
	return prefixOutput;
}


void asalib AbelianSquaresAnalysis::squares::AnalyseWord(types::word input, squares::AnalysisOutput& output) {

	// Prepare thread pool
#ifdef asalib_prefix_MULTITHREAD
	AbelianSquaresAnalysis::ThreadPool<squares::substringAnalysisInput, squares::substringAnalysisOutput> pool;
#endif

	types::parihkVector alphabet = input.countAlphabetSize();
	std::string_view inputView(input);

	// For every even word length
	for (unsigned int len = 2; len <= input.length(); len += 2) {
		// for every valid start position
		for (unsigned int pos = 0; pos < (input.length() - len + 1); pos++) {
			squares::substringAnalysisInput AnalysisInput;
			AnalysisInput.word = inputView;
			AnalysisInput.length = len;
			AnalysisInput.position = pos;
			AnalysisInput.alphabet = alphabet;

#ifdef asalib_prefix_MULTITHREAD
			pool.AddTask(squares::AnalyseSubstring, AnalysisInput);
#else
			squares::substringAnalysisOutput computation_output  = squares::AnalyseSubstring(AnalysisInput);
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

	squares::SquaresCountTrivials(output.total);

	// Distinct
	squares::SquaresCategoriseInput distinctCategoriseInput(output.total.list, output.distinct.list);
	distinctCategoriseInput.sort = squares::SquaresSortDistinctPredicate;
	distinctCategoriseInput.comparison = squares::SquaresComparisonDistinctPredicate;
	squares::SquaresCategorise(distinctCategoriseInput);
	squares::SquaresCountTrivials(output.distinct);

	// Non-equivalent
	squares::SquaresCategoriseInput nonequivalentCategoriseInput(output.distinct.list, output.nonequivalent.list);
	nonequivalentCategoriseInput.sort = squares::SquaresSortNoneqPredicate;
	nonequivalentCategoriseInput.comparison = squares::SquaresComparisonNoneqPredicate;
	squares::SquaresCategorise(nonequivalentCategoriseInput);
	squares::SquaresCountTrivials(output.nonequivalent);
}

bool asalib AbelianSquaresAnalysis::squares::SquaresComparisonDistinctPredicate
(squares::substringAnalysisOutput left, squares::substringAnalysisOutput right) {
	return left.square == right.square;
}

bool asalib AbelianSquaresAnalysis::squares::SquaresSortDistinctPredicate
(squares::substringAnalysisOutput left, squares::substringAnalysisOutput right) {
	return left.square < right.square;
}

bool asalib AbelianSquaresAnalysis::squares::SquaresComparisonNoneqPredicate
(squares::substringAnalysisOutput left, squares::substringAnalysisOutput right) {
	return (left.vector == right.vector);
}

bool asalib AbelianSquaresAnalysis::squares::SquaresSortNoneqPredicate
(squares::substringAnalysisOutput left, squares::substringAnalysisOutput right) {
	return (left.vector > right.vector);
}

asalib AbelianSquaresAnalysis::squares::SquaresCategoriseInput::SquaresCategoriseInput(std::vector<substringAnalysisOutput>& in, std::vector<substringAnalysisOutput>& out):
	_in(in), _out(out)
{
	// constructor
}

void asalib AbelianSquaresAnalysis::squares::SquaresCategorise(squares::SquaresCategoriseInput input) {
	input._out = input._in;
	std::sort(input._out.begin(), input._out.end(), input.sort);
	auto last_dist = std::unique(input._out.begin(), input._out.end(), input.comparison);
	input._out.erase(last_dist, input._out.end());
}

void asalib  AbelianSquaresAnalysis::squares::SquaresCountTrivials(squares::AnalysisOutputSquareType& input) {
	for (auto& square : input.list) {
		if (square.isTrivial) {
			input.trivial++;
		}
		/*else {
			input.nontrivial++;
		}*/
	}
	input.nontrivial = input.list.size() - input.trivial;
}