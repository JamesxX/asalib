#ifndef asalib2_public_algorithms_generation_allWordsOfBlockCountUntilLength_INCLUDEGUARD
#define asalib2_public_algorithms_generation_allWordsOfBlockCountUntilLength_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <asalib2\public\types\word.hpp>
#include <vector>

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace generation
		{

			inline namespace _ALWOBCUL
			{

				struct ALWOBCUL_args_t {
					types::length _blockCount;
					types::length _length;
					bool positionAlphabet = false;
				};

				asalib _STD vector<types::word> allWordsOfBlockCountUntilLength(ALWOBCUL_args_t input);

			} // inline namespace _ALWOBCUL

		} // namespace generation

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_generation_allWordsOfBlockCountUntilLength_INCLUDEGUARD
