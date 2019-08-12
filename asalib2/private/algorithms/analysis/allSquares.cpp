/// @file asalib2\private\algorithms\allSquares.cpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Algorithm definition for the analysis of abelian squares in binary words

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <asalib2\public\algorithms\analysis\allSquares.hpp>

namespace types = asalib2_ns::types;
namespace allSquares_ns = asalib2_ns::algorithms::analysis::_allSquares;

asalib2_likely
asalib allSquares_ns::squares_t allSquares_ns::allSquares
(const types::word& input, allSquares_ns::haltingPredicate haltingFn)
{
	types::length inputLength = input.length();
	allSquares_ns::squares_t output;

	types::parihkVector temporaryVector;

	for (types::size position = 0; position < (inputLength - 2); position++)
	{
		for (types::size length = 2; length <= (inputLength - position); length += 2)
		{

			types::word subword = input.subword(position, length);

			if (subword.isAbelianSquare(temporaryVector))
			{

				square_info_t info = {
					temporaryVector, // Copy
					subword, // Copy
					position,
					length
				};

				if (haltingFn != nullptr)
				{
					if (haltingFn(info))
					{

					}
				}

				if (temporaryVector.isTrivial())
				{

					output.m_Trivial.list.push_back({
						temporaryVector, // Copy
						subword, // Copy
						position,
						length
					});

					output.m_Trivial.count++;
				}
				else
				{
					output.m_NonTrivial.list.push_back({
						temporaryVector, // Copy
						subword, // Copy
						position,
						length
					});

					output.m_NonTrivial.count++;
				}
				output.count++;
			}
		}
	}

	return output;
}
