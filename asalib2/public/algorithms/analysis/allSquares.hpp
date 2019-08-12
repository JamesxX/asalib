#ifndef asalib2_public_algorithms_analysis_allSquares_INCLUDEGUARD
#define asalib2_public_algorithms_analysis_allSquares_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <asalib2\public\types\word.hpp>
#include <asalib2\public\types\parihkVector.hpp>
#include <vector>

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace analysis
		{

			inline namespace _allSquares
			{

				struct square_info_t
				{
					types::parihkVector m_Vector;
					types::word m_Word;
					types::size m_Position;
					types::size m_Length;
				};

				struct squares_t 
				{

					struct squares_type_t
					{
						types::size count = 0;
						_STD vector<square_info_t> list;
					} m_Trivial, m_NonTrivial;

					types::size count = 0;
				};

				asalib2_likely
				asalib squares_t allSquares(const types::word& input, haltingPredicate = nullptr);

			} // inline namespace _allSquares

		} // namespace generation

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_analysis_allSquares_INCLUDEGUARD]
