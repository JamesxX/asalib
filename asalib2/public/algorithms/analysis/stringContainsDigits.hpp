#ifndef asalib2_public_algorithms_analysis_SCD_INCLUDEGUARD
#define asalib2_public_algorithms_analysis_SCD_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <string>

namespace asalib2_ns
{

	namespace algorithms
	{

		namespace analysis
		{

			asalib inline bool stringContainsDigits
			(const _STD string& subject)
			{
				return subject.find_first_of("0123456789") != _STD string::npos;
			}

		} // namespace analysis

	} // namespace algorithms

}

#endif // asalib2_public_algorithms_analysis_SCD_INCLUDEGUARD
