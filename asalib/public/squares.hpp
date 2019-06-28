/// @file squares.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, declaring important classes and functions pertaining to prefix analysis.

#pragma once
#include "library.h"
#include "types.hpp"
#include "morphism.hpp"

#include <vector>
#include <functional>
#include <common/json.hpp>
#include <string_view>

namespace AbelianSquaresAnalysis {

	namespace squares {

		/// @brief Input structure for AbelianSquaresAnalysis::squares::AnalyseSubstring
		struct substringAnalysisInput {
			//types::word word; ///< substring to analyse.
			std::string_view word;
			size_t length = 0; ///< length of substring.
			size_t position = 0; ///< Start position of string in parent prefix.
			types::parihkVector alphabet; ///< Alphabet of parent prefix.
		};

		/// @brief Structure containing information for a substring of a prefix. This is currently only used internally.
		struct substringAnalysisOutput : public substringAnalysisInput {

			/// @brief Default constructor for substringAnalysisOutput.
			asalib substringAnalysisOutput();

			/// @brief Constructor for substringAnalysisOutput deriving from substringAnalysisInput.
			/// @param[in] base substringAnalysisInput base.
			asalib substringAnalysisOutput(const substringAnalysisInput& base);

			types::boolean isSquare = false; ///< If the substring is an abelian square. If false, other members may not be set.
			types::boolean isTrivial = false; ///< If the substring is a trivial abelian square.
			types::parihkVector vector; ///< Parihk vector of the abelian square.
			types::word square;
		};

		/// @brief Structure containing information on a type of AB sqaure (total, distinct, non-equivalent).
		struct AnalysisOutputSquareType {
			types::integer trivial = 0; ///< Number of trivial abelian squares of the given type.
			types::integer nontrivial = 0; ///< Number of non-trivial abelian squares of the given type.
			std::vector<substringAnalysisOutput> list; ///< List of abelian squares of the given type.
		};

		/// @brief Structure containing information on abelian squares in a word.
		struct AnalysisOutput {
			AnalysisOutputSquareType total; ///< List and information on the number of total abelian squares.
			AnalysisOutputSquareType distinct; ///< List and information on the number of distinct abelian squares.
			AnalysisOutputSquareType nonequivalent; ///< List and information on the number of non-equivalent abelian squares.
		};

		/// @brief Structure containing output of a prefix analysis, derived from AbelianSquaresAnalysis::morphism::morphismOutput.
		/// Information on a morphism output contained in analysis output is dependant on correct information entry, as this is not checked.
		/// @see AbelianSquaresAnalysis::morphism::morphismOutput
		struct prefixAnalysisOutput : morphism::morphismOutput, squares::AnalysisOutput {

			/// @brief Constructor of class from base AbelianSquaresAnalysis::morphism::morphismOutput.
			/// @param[in] base Reference to parent morphismOutput. This will copy of data on the generated of the prefix on which the analysis is performed.
			asalib prefixAnalysisOutput(const morphism::morphismOutput& base);

			/// @brief Constructor of class from base AbelianSquaresAnalysis::morphism::morphismOutput.
			/// @param[in] base Reference to parent morphismOutput. This will copy of data on the generated of the prefix on which the analysis is performed.
			/// @param[in] base2 Reference to parent AnalysisOutput, included for backwards compatibility.
			asalib prefixAnalysisOutput(const morphism::morphismOutput& base, const squares::AnalysisOutput& base2);
		};

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::prefix::prefixAnalysisOutput to JSON.
		/// @param[out] j JSON object.
		/// @param[in] data input AbelianSquaresAnalysis::squares::prefixAnalysisOutput.
		/// @see AbelianSquaresAnalysis::squares::prefixAnalysisOutput
		void asalib to_json(nlohmann::json& j, const prefixAnalysisOutput& data);

		/// @brief Check if a substring is an ablian square over its entire length.
		/// @param[in] input Substring to check. Members length and position are optional, and are only included so as to be passed on to other functions.
		/// @return Information on whether the substring is an abelian square, including its parihk vector and whether it is trivial.
		substringAnalysisOutput asalib AnalyseSubstring(substringAnalysisInput input);

		/// @brief Find every abelian square for the given morphism output.
		/// @warning This function is expensive!
		/// @param[in] morphismOutput Prefix to analyse. Other information is included within the structure for the purpose of passing this information onto other functions.
		/// @return Information on abelian squares within word.
		/// @deprecated This function is only included for backwards compatibility.
		prefixAnalysisOutput asalib AnalysePrefix(morphism::morphismOutput morphismOutput);

		/// @brief Find every abelian square for the input prefix.
		/// @warning This function is expensive!
		/// @param[in] input Word to be analysed.
		/// @param[out] output Struct contianing information on all types of abelian squares.
		void asalib AnalyseWord(types::word input, squares::AnalysisOutput& output);

		/// @brief Internal function called to remove duplicate substrings in total abelian square lists to calculate a list of distinct squares.
		/// @param[in] left Analysis to compare against.
		/// @param[in] right Analysis to compare with.
		/// @return Are these two analyses equal.
		bool asalib SquaresComparisonDistinctPredicate(substringAnalysisOutput left, substringAnalysisOutput right);
		
		/// @brief Internal function called to sort substrings in total abelian square lists to calculate a list of distinct squares.
		/// @param[in] left Analysis to compare against.
		/// @param[in] right Analysis to compare with.
		/// @return Are these two analyses equal.
		bool asalib SquaresSortDistinctPredicate(substringAnalysisOutput left, substringAnalysisOutput right);

		/// @brief Internal function called to remove duplicate parihk vectors in distinct abelian square lists to calculate a list of non-equivalent squares.
		/// @param[in] left Analysis to compare against.
		/// @param[in] right Analysis to compare with.
		/// @return Are these two analyses equal.
		bool asalib SquaresComparisonNoneqPredicate(substringAnalysisOutput left, substringAnalysisOutput right);
		
		/// @brief Internal function called to sort substrings in distinct abelian square lists to calculate a list of non-equivalent squares.
		/// @param[in] left Analysis to compare against.
		/// @param[in] right Analysis to compare with.
		/// @return Are these two analyses equal.
		bool asalib SquaresSortNoneqPredicate(substringAnalysisOutput left, substringAnalysisOutput right);
		
		/// @brief Input structure for AbelianSquaresAnalysis::prefix::SquaresCategorise for speed purposes.
		struct SquaresCategoriseInput {

			/// @brief Constructor for class
			/// @param[in] in Reference to input list of abelian square analysis output structures
			/// @param[out] out Reference to output list of abelian square analysis output structures
			asalib SquaresCategoriseInput(std::vector<substringAnalysisOutput>& in, std::vector<substringAnalysisOutput>& out);
			
			std::vector<substringAnalysisOutput>& _in; ///< List from which entries are gathered.
			std::vector<substringAnalysisOutput>& _out; ///< List into which sorted and equality-erased entries are output.
			std::function<bool(substringAnalysisOutput, substringAnalysisOutput)> sort; ///< Function with which entries are sorted.
			std::function<bool(substringAnalysisOutput, substringAnalysisOutput)> comparison; ///< Function with which entries are compared for erasure.
		};

		/// @brief Categorise squares given input options. Used to calculated distinct and non-equivalent square lists.
		/// @param[in] input Options given to functions.
		/// @see AbelianSquaresAnalysis::prefix::SquaresCategoriseInput
		void asalib SquaresCategorise(SquaresCategoriseInput input);

		/// @brief Used internally to count trivial and non-trivial squares for a given list.
		/// @param[in] input Structure for list of squares containing counters.
		void asalib SquaresCountTrivials(AnalysisOutputSquareType& input);

	} // namespace squares

} // namespace AbelianSquaresAnalysis
