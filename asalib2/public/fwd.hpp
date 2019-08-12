/// @file asalib2\public\fwd.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Forward delcarations for all types used in the library, including internal types. 
/// Include this header after asalib2\public\library.hpp where required.

#ifndef asalib2_public_fwd_INCLUDEGUARD
#define asalib2_public_fwd_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <string>

namespace asalib2_ns
{

	namespace types
	{

		namespace exception
		{
			class badConstruction;
			class notImplemented;
		} // namespace exception

		inline namespace _primitives
		{
			typedef size_t size;
			typedef size length;
			typedef unsigned long int integer;
			typedef bool boolean;
			typedef char character;
		} // inline namespace _primitives

		inline namespace _morphism
		{
			class morphism;
		} // inline namespace _morphism

		inline namespace _parihkvector
		{
			class parihkVector;
		} // inline namespace _parihkVector

		inline namespace _word
		{
			struct block;
			class word;
		} // inline namespace _word

		inline namespace _generator
		{
			template<typename result_t> class generator;
		}

	} // namespace types

	namespace algorithms
	{
		
		namespace analysis
		{

			inline namespace _allSquares
			{
				struct square_info_t;
				struct squares_t;

				typedef bool(*haltingPredicate)(const square_info_t&);
			} // inline namespace _allSquares

			inline namespace _categoriseSquares
			{
				struct categorised_squares_t;
			} // inline namespace _categoriseSquares

		} // namespace analysis

		namespace generation
		{
			
			inline namespace _ALWOBCUL
			{
				struct ALWOBCUL_args_t;
			} // inline namespace _ALWOBCUL

		} // namespace generation

	} // namespace algorithms

} // namespace asalib2_ns

#endif // asalib2_public_fwd_INCLUDEGUARD
