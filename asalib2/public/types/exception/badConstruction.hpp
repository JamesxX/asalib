/// @file asalib2\public\types\exceptions\badConstruction.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the badConstruction exception class, thrown when
/// a class constructor throws an unexpected exception.

#ifndef asalib2_public_types_exception_badConstruction_INCLUDEGUARD
#define asalib2_public_types_exception_badConstruction_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <stdexcept>

namespace asalib2_ns
{

	namespace types
	{

		namespace exception
		{

			class badConstruction : public _STD runtime_error
			{
			public:
				using _STD runtime_error::runtime_error;
			};

#define asalib2_public_types_exception_badConstruction_rethrow catch( _STD exception& err ){ \
			throw new asalib2_ns::types::exception::badConstruction(_STD string("Error in construction with " __FUNCTION__ " : ") + err.what()); \
			}

		} // namespace exception

	} // namespace types

} // naemspace asalib2_ns

#endif // asalib2_public_types_exception_badConstruction_INCLUDEGUARD
