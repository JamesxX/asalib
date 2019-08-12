/// @file asalib2\public\types\exceptions\notImplemented.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the notImplemented exception class, thrown when
/// a call is made to a currently not implemented function.

#ifndef asalib2_public_types_exception_notImplemented_INCLUDEGUARD
#define asalib2_public_types_exception_notImplemented_INCLUDEGUARD
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

			class notImplemented : public _STD logic_error
			{
			public:
				inline notImplemented() : _STD logic_error{ "Feature not yet implemented." }
				{}
			};

		} // namespace exception

	} // namespace types

} // naemspace asalib2_ns

#endif // asalib2_public_types_exception_notImplemented_INCLUDEGUARD
