#ifndef asalib2_public_algorithms_generation_applyMorphismUntilLength_INCLUDEGUARD
#define asalib2_public_algorithms_generation_applyMorphismUntilLength_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\constants.hpp>

#include <asalib2\public\types\word.hpp>
#include <asalib2\public\types\morphism.hpp>

#ifndef asalib2_public_algorithms_generatin_applyMorphismUntilLength_MaxItterations
#define asalib2_public_algorithms_generatin_applyMorphismUntilLength_MaxItterations 15
#endif

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace generation
		{

			inline types::word applyMorphismUntilLength
			(const types::word& input, const types::morphism& morphism, types::size minimumLength)
			{
				types::word output(input);
				types::word temp;

				unsigned int nIteration = 0;

				while (morphism.applyMorphism(output, temp) < minimumLength
					&& nIteration < asalib2_public_algorithms_generatin_applyMorphismUntilLength_MaxItterations)
				{
					output = temp;
					nIteration++;

				}

				return output;
			}

		} // namespace generation

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_generation_applyMorphismUntilLength_INCLUDEGUARD
