/// @file asalib2\public\types\morphism.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the morphism class, a less commonly used class describing 
/// a mapping of character to characters.

#ifndef asalib2_public_types_morphism_INCLUDEGUARD
#define asalib2_public_types_morphism_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\constants.hpp>

#include <asalib2\public\types\word.hpp>

namespace asalib2_ns
{

	namespace types
	{

		inline namespace _morphism
		{
			class morphism
			{
			public:

				struct morphism_internal_t
				{
				public:
					word a;
					word b;

				public:
					asalib morphism_internal_t(word a = word("A"), word b = word("B"));
					asalib morphism_internal_t(const morphism_internal_t& copy);
					asalib morphism_internal_t(morphism_internal_t&& move) noexcept;

					asalib morphism_internal_t& operator=(const morphism_internal_t& copy);
					asalib morphism_internal_t& operator=(morphism_internal_t&& move) noexcept;

#if asalib2_cpp_20
					auto operator<=>(const morphism_internal_t&) const = default;
#else
					asalib types::boolean operator<(morphism_internal_t const& b) const;

					asalib inline types::boolean operator> (morphism_internal_t const& b) const 
					{ return b < *this; }

					asalib inline types::boolean operator==(morphism_internal_t const& b) const 
					{ return !(*this < b || *this > b); }

					asalib inline types::boolean operator!=(morphism_internal_t const& b) const 
					{ return (*this < b || *this > b); }

					asalib inline types::boolean operator<=(morphism_internal_t const& b) const 
					{ return !(b < *this); }

					asalib inline types::boolean operator>=(morphism_internal_t const& b) const 
					{ return !(*this < b); }
#endif
				} m_morphism_internal;

			public:
				asalib morphism(word a = word("A"), word b = word("B"));
				asalib morphism(const morphism& copy);
				asalib morphism(morphism&& move) noexcept;

				asalib morphism& operator=(const morphism& copy);
				asalib morphism& operator=(morphism&& move) noexcept;

#if asalib2_cpp_20
				auto operator<=>(const morphism&) const = default;
#else
				asalib types::boolean operator<(morphism const& b) const;

				asalib inline types::boolean operator> (morphism const& b) const 
				{ return b < *this; }

				asalib inline types::boolean operator==(morphism const& b) const 
				{ return !(*this < b || *this > b); }

				asalib inline types::boolean operator!=(morphism const& b) const 
				{ return (*this < b || *this > b); }

				asalib inline types::boolean operator<=(morphism const& b) const 
				{ return !(b < *this); }

				asalib inline types::boolean operator>=(morphism const& b) const 
				{ return !(*this < b); }
#endif

				asalib types::size applyMorphism(const word& input, word& output) const;
			};
		}

	} // namespace types

} // namespace asalib2_ns

#endif // asalib2_public_types_morphism_INCLUDEGUARD
