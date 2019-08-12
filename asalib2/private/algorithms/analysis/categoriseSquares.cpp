#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\algorithms\analysis\categoriseSquares.hpp>

#include <functional>
#include <algorithm>

namespace types = asalib2_ns::types;
namespace allSquares_ns = asalib2_ns::algorithms::analysis::_allSquares;
namespace categoriseSquares_ns = asalib2_ns::algorithms::analysis::_categoriseSquares;

namespace
{

#pragma region binaryPredicates
#define asalib2_private_algorithms_categorise_binaryPredicate(name, left, right) \
bool name(const allSquares_ns::square_info_t& left, const allSquares_ns::square_info_t& right)

	typedef asalib2_private_algorithms_categorise_binaryPredicate((*binaryPredicateCategorise_t), , );

	asalib2_likely
	asalib2_private_algorithms_categorise_binaryPredicate(DistinctSort, left, right)
	{
		return left.m_Word < right.m_Word;
	}

	asalib2_likely
	asalib2_private_algorithms_categorise_binaryPredicate(DistinctComp, left, right)
	{
		return left.m_Word == right.m_Word;
	}

	asalib2_likely
	asalib2_private_algorithms_categorise_binaryPredicate(NonequivalentSort, left, right)
	{
		return left.m_Vector < right.m_Vector;
	}

	asalib2_likely
	asalib2_private_algorithms_categorise_binaryPredicate(NonequivalentComp, left, right)
	{
		return left.m_Vector == right.m_Vector;
	}

#undef asalib2_private_algorithms_categorise_binaryPredicate
#pragma endregion // binaryPredicates
	
	struct categorisesquares_sortcomp_work_ARGS_t
	{
		_STD vector<allSquares_ns::square_info_t>* in;
		_STD vector<allSquares_ns::square_info_t>* out;
		binaryPredicateCategorise_t sort;
		binaryPredicateCategorise_t comp;
	};

	asalib2_likely
	inline void categorisesquares_sortcomp_work
	(categorisesquares_sortcomp_work_ARGS_t& args)
	{
		*args.out = *args.in; // Copy
		_STD sort(args.out->begin(), args.out->end(), args.sort);
		auto last_dist = _STD unique(args.out->begin(), args.out->end(), args.comp);
		args.out->erase(last_dist, args.out->end());
	}

	asalib2_likely
	inline void categorisesquares_sortcomp(
		allSquares_ns::squares_t& src,
		allSquares_ns::squares_t& dst,
		binaryPredicateCategorise_t sort,
		binaryPredicateCategorise_t comp
	)
	{

		categorisesquares_sortcomp_work_ARGS_t Arguments;
		Arguments.sort = sort;
		Arguments.comp = comp;

		// Nontrivial
		{
			Arguments.in = &(src.m_NonTrivial.list);
			Arguments.out = &(dst.m_NonTrivial.list);
			categorisesquares_sortcomp_work(Arguments);
		}

		// Trivial
		{
			Arguments.in = &(src.m_Trivial.list);
			Arguments.out = &(dst.m_Trivial.list);
			categorisesquares_sortcomp_work(Arguments);
		}

		dst.m_NonTrivial.count = dst.m_NonTrivial.list.size();
		dst.m_Trivial.count = dst.m_Trivial.list.size();
		dst.count = dst.m_NonTrivial.count + dst.m_Trivial.count;
	}

}

asalib2_likely
asalib categoriseSquares_ns::categorised_squares_t categoriseSquares_ns::categoriseSquares
(const allSquares_ns::squares_t& squares)
{
	categoriseSquares_ns::categorised_squares_t output;
	output.m_All = squares;

	categorisesquares_sortcomp(
		output.m_All, //src
		output.m_Distinct, //dst
		DistinctSort, // sort
		DistinctComp// comp
	);

	categorisesquares_sortcomp(
		output.m_Distinct, //src
		output.m_Nonequivalent, //dst
		NonequivalentSort, // sort
		NonequivalentComp // comp
	);

	return output;
}