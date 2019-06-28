/// @file morphism.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, declaring important classes and functions pertaining to morphism analysis.

#pragma once
#include "library.h"
#include "types.hpp"

#include <vector>
#include <map>
#include <string>
#include <common/json.hpp>

namespace AbelianSquaresAnalysis {

	namespace morphism {

		/// @brief C++ structure representing input MORPH file.
		struct  morphismInput {
			bool parseSuccess = false; ///< Whether MORPH file was successfully loaded.
			std::map<std::string, AbelianSquaresAnalysis::types::mapping> morphisms; ///< Vector of morphisms.
			struct MorphismInputSettings {
				unsigned int lengthBound = 1000; ///< Minimum length of generated prefix.
				std::vector<AbelianSquaresAnalysis::types::word> startWords; ///< Vector of start words upon which to apply the morphisms.
			} settings; ///< Settings applied to every listed morphism.
		};


		/// @brief Function designed for use by nlohmann::json to convert MORPH file to morphismInput
		/// Called internally.
		/// @param[in] j JSON object being read.
		/// @param[out] data AbelianSquaresAnalysis::morphism::morphismInput type.
		void asalib from_json(const nlohmann::json& j, morphismInput& data);

		/// @brief C++ structure representing output of AbelianSquaresAnalysis.morphism.RunMorphismSingle.
		/// @see AbelianSquaresAnalysis::morphism::RunMorphismSingle
		struct morphismOutput {
			bool morphismSuccess = false; ///< True of number of iterations of morphism to achieve minimum length of lengthBound is less than twice the lengthBound.
			struct inputSettings {
				std::string morphismName; ///< Name of the applied morphism.
				AbelianSquaresAnalysis::types::mapping morphism; ///< Mappings of applied morphism.
				AbelianSquaresAnalysis::types::word startWord; ///< Start word to which morphism was applied
				AbelianSquaresAnalysis::types::length lengthBound = 0; ///< Requested minimum length when generating prefix.
			} input; ///< Settings given to morphism iterator.
			struct morphismAnalysis {
				std::vector<std::string> prolongable; ///< Vector of mappings which are prolongable.
				size_t k_uniform = 0; ///< k-uniformity of morphism, where 0 is no uniformity.
			} morphismAnalysis; ///< Results of analysis on morphism itself.
			AbelianSquaresAnalysis::types::word generatedPrefix; ///< Prefix generated from application of morphism onto startword for a number of iterations so as to provide a prefix of atleast lengthBound length.
			size_t generatedPrefixLength = 0; ///< Length of generated prefix. Equal or greater than lengthBound where morphismSuccess is true.
			AbelianSquaresAnalysis::types::length runs = 0; ///< Number of iterations required to achieve length greater of equal to lengthBound.
		};

		/// @brief Function designed for use by nlohmann::json to convert AbelianSquaresAnalysis::morphism::morphismOutput to JSON.
		/// Called internally.
		/// @param[out] j JSON object.
		/// @param[in] data AbelianSquaresAnalysis::morphism::morphismOutput.
		void asalib to_json(nlohmann::json& j, const morphismOutput& data);

		/// @brief Function designed for use by nlohmann::json to convert JSON to AbelianSquaresAnalysis::morphism::morphismOutput.
		/// Called internally.
		/// @param[in] j JSON object.
		/// @param[out] data AbelianSquaresAnalysis::morphism::morphismOutput.
		void asalib from_json(const nlohmann::json& j, morphismOutput& data);

		/// @brief RunsAbelianSquaresAnalysis::morphism::RunMorphismSingle for every input morphism and start word.
		/// @param[in] input Settings and morphisms to iterate.
		/// @return A vector (ordered by morphism input and start word) of morphism itteration outputs.
		asalib std::vector<morphismOutput> RunMorphisms(morphismInput input);

		/// @brief Itterates a morphism over a start word until the generated prefix's length exceeds lengthBound.
		/// Should the number of iterations exceed twice the defined lengthBound, the result is considered unsucessful.
		/// @param[in] input Structure of a single morphism, start word and length bound.
		/// @return Generated prefix and associated information in AbelianSquaresAnalysis::morphism::morphismOutput type.
		/// @see AbelianSquaresAnalysis::morphism::morphismOutput
		asalib morphismOutput RunMorphismSingle(morphismOutput::inputSettings input);

	} // namespace morphism

} // namespace AbelianSquaresAnalysis
