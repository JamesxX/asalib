/// @file asalib2\public\types\word.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Delcaration for the word class, a core class used throughout the library 
/// to standardise word operations.

#ifndef asalib2_public_types_word_INCLUDEGUARD
#define asalib2_public_types_word_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <string>
#include <deque>
#include <initializer_list>

namespace asalib2_ns
{

	namespace types
	{

		inline namespace _word
		{

			struct block
			{
				asalib block(char _character = (char)NULL, types::length _blockLength = 0);
				//asalib block(const block& copy) = default;
				//asalib block(block&& move) noexcept = default;

				char character;
				types::length blockLength = 0;
			}; // struct block

			class word
			{
				friend types::morphism;
			public:
				using blockValue_t = block;
				typedef _STD deque<blockValue_t> blocks_representation_t;

			public:
				blocks_representation_t m_blocks;

			public:
				asalib word();
				asalib word(const word& copy);
				asalib word(word&& move) noexcept;
				asalib word(_STD initializer_list<types::length> l);
				asalib word(char character, types::length length); // 1 block of length
				asalib word(_STD string input);

				asalib word& operator=(const word& copy);
				asalib word& operator=(word&& move) noexcept ;

				asalib void generateParihkVector(types::parihkVector& out) const;
				asalib operator std::string() const;
				asalib _STD string toPretty() const;

#if asalib2_cpp_20
				auto operator<=>(const word&) const = default;
#else
				asalib types::boolean operator<(word const& b) const;

				asalib inline types::boolean operator> (word const& b) const 
				{ return b < *this;}

				asalib inline types::boolean operator==(word const& b) const 
				{ return !(*this < b || *this > b);}

				asalib inline types::boolean operator!=(word const& b) const 
				{ return (*this < b || *this > b);}

				asalib inline types::boolean operator<=(word const& b) const 
				{ return !(b < *this);}

				asalib inline types::boolean operator>=(word const& b) const 
				{ return !(*this < b);}
#endif

				asalib word operator+(const word& other) const;
				asalib word& operator+=(const word& other);

				asalib types::length length() const;
				asalib char operator[](types::size location) const;
				asalib word subword(types::size beginpos, types::size length) const;

				asalib types::boolean isAbelianSquare(types::parihkVector& output) const;

			private:
				asalib word firstHalf() const;
				asalib word secondHalf() const;
				asalib _STD pair<types::size, types::size> getPosition(types::size position) const;
			}; // class word

		} // inline namespace _word

	} // namespace types

} // namespace asalib2_ns

#endif // asalib2_public_types_word_INCLUDEGUARD
