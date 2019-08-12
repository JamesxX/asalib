/// @file asalib2\public\types\generator.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the generator base template class. This is currently seldom used 
/// in the library as few generation algorithms have been implemented

#ifndef asalib2_public_types_generator_INCLUDEGUARD
#define asalib2_public_types_generator_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

namespace asalib2_ns
{

	namespace types
	{

		inline namespace _generator
		{

			template<typename result_t>
			class generator
			{
			private:
				typedef result_t result_t;
			public:
				virtual result_t operator()() = 0;
			}; // class generator<result_t>

		} // inline namespace _generator
		
	} // namespace types

} // namespace asalib2_ns

#endif // asalib2_public_types_generator_INCLUDEGUARD
