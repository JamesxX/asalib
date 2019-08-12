/// @file asalib2\public\types\parihkVector.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the parihkVector class, a core class used throughout the library 
/// to standardise abelian square operations. 


#ifndef asalib2_public_types_parihkvector_INCLUDEGUARD
#define asalib2_public_types_parihkvector_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <string>

namespace asalib2_ns
{

	namespace types
	{

		inline namespace _parihkvector
		{

			class parihkVector
			{
			private:
				
				typedef types::size quantity_t;

				static constexpr quantity_t defaultValue = 0;
				static constexpr unsigned int toStringBufferSize = 10;
				static constexpr const char* toStringFormat = "(%zd,%zd)^2";
				
			public:
				struct parihkVector_internal_t
				{
				public:
					quantity_t a = defaultValue;
					quantity_t b = defaultValue;

				public:
					asalib parihkVector_internal_t(parihkVector::quantity_t a = 0, parihkVector::quantity_t b = 0);
					asalib parihkVector_internal_t(const parihkVector_internal_t& copy);
					asalib parihkVector_internal_t(parihkVector_internal_t&& move) noexcept;

					asalib parihkVector_internal_t& operator=(const parihkVector_internal_t& copy);
					asalib parihkVector_internal_t& operator=(parihkVector_internal_t&& move) noexcept;

#if asalib2_cpp_20
					auto operator<=>(const parihkVector_internal_t&) const = default;
#else
					asalib types::boolean operator<(parihkVector_internal_t const& b) const;

					asalib inline types::boolean operator> (parihkVector_internal_t const& b) const
					{ return b < *this; }

					asalib inline types::boolean operator==(parihkVector_internal_t const& b) const
					{ return !(*this < b || *this > b); }

					asalib inline types::boolean operator!=(parihkVector_internal_t const& b) const
					{ return (*this < b || *this > b); }

					asalib inline types::boolean operator<=(parihkVector_internal_t const& b) const
					{ return !(b < *this); }

					asalib inline types::boolean operator>=(parihkVector_internal_t const& b) const
					{ return !(*this < b); }
#endif

				} m_parihkVector_internal;

				asalib parihkVector(quantity_t a = defaultValue, quantity_t b = defaultValue);
				asalib parihkVector(const parihkVector& copy);
				asalib parihkVector(parihkVector&& move) noexcept;

				asalib parihkVector& operator=(const parihkVector& copy);
				asalib parihkVector& operator=(parihkVector&& move) noexcept;

				asalib operator std::string() const;

#if asalib2_cpp_20
				auto operator<=>(const parihkVector&) const = default;
#else
				asalib types::boolean operator<(parihkVector const& b) const;

				asalib inline types::boolean operator> (parihkVector const& b) const
				{ return b < *this; }

				asalib inline types::boolean operator==(parihkVector const& b) const
				{ return !(*this < b || *this > b); }

				asalib inline types::boolean operator!=(parihkVector const& b) const
				{ return (*this < b || *this > b); }

				asalib inline types::boolean operator<=(parihkVector const& b) const
				{ return !(b < *this); }

				asalib inline types::boolean operator>=(parihkVector const& b) const
				{ return !(*this < b); }
#endif

				asalib types::boolean isTrivial() const;

				parihkVector_internal_t& value = m_parihkVector_internal;

			}; // class parihkVector

		} // inline namespace _parihkVector

	} // namespace types

} // namespace asalib2_ns

#endif // asalib2_public_types_parihkvector_INCLUDEGUARD
