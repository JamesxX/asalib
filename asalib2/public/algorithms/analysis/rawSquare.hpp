#ifndef asalib2_public_algorithms_analysis_rawSquare_INCLUDEGUARD
#define asalib2_public_algorithms_analysis_rawSquare_INCLUDEGUARD
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
			asalib types::boolean isRawSquare(const types::word& input);
		} // namespace analysis

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_algorithms_analysis_rawSquare_INCLUDEGUARD
