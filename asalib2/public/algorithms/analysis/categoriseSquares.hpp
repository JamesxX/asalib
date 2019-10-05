#ifndef asalib2_public_algorithms_analysis_categoriseSquares_INCLUDEGUARD
#define asalib2_public_algorithms_analysis_categoriseSquares_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\algorithms\analysis\allSquares.hpp>

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace analysis
		{

			inline namespace _categoriseSquares
			{

				struct categorised_squares_t
				{
					squares_t m_All;
					squares_t m_Distinct;
					squares_t m_Nonequivalent;
				};

				asalib bool DistinctSort(const square_info_t& left, const square_info_t& right);
				asalib bool DistinctComp(const square_info_t& left, const square_info_t& right);
				asalib bool NonequivalentSort(const square_info_t& left, const square_info_t& right);
				asalib bool NonequivalentComp(const square_info_t& left, const square_info_t& right);

				asalib2_likely
				asalib
				void generateSubset(squares_t& src, squares_t& dst, binaryPredicateCategorise_t sort, binaryPredicateCategorise_t comp);

				asalib2_likely
				asalib categorised_squares_t categoriseSquares(const _allSquares::squares_t& squares);

			} // inline namespace _categoriseSquares

		} // namespace analysis

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_analysis_categoriseSquares_INCLUDEGUARD
