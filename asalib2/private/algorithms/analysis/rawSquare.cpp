#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <asalib2\public\algorithms\analysis\rawSquare.hpp>
#include <asalib2\public\algorithms\analysis\allSquares.hpp>


namespace types = asalib2_ns::types;
namespace analysis = asalib2_ns::algorithms::analysis;

asalib types::boolean analysis::isRawSquare
(const types::word& input)
{
	if (input.length() % 2 != 0)
	{
		return false;
	}

	types::parihkVector dummy;

	if (!input.isAbelianSquare(dummy))
	{
		return false;
	}

	if (dummy.isTrivial())
	{
		return false;
	}

	// CHANGE BELOW
	if (analysis::allSquares(input, [](const square_info_t& info) {return info.m_Vector.isTrivial();}).m_NonTrivial.count != 1)
	{
		return false;
	}

	return true;
}
