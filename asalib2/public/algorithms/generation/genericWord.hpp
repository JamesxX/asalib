#ifndef asalib2_public_algorithms_generation_genericWord_INCLUDEGUARD
#define asalib2_public_algorithms_generation_genericWord_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\constants.hpp>

#include <asalib2\public\types\word.hpp>

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace generation
		{

			asalib inline types::word genericWord
			(types::length nBlocks)
			{
				types::word output("A");
				for (unsigned int position = 1; position < nBlocks; position++)
				{
					output += types::word(constants::Alphabet[position % 2], 1);
				}
				return output;
			}

		} // namespace generation

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_generation_genericWord_INCLUDEGUARD
