#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\constants.hpp>

#include <asalib2\public\types\morphism.hpp>
#include <asalib2\public\types\exception\badConstruction.hpp>

namespace types = asalib2_ns::types;
using morphism = types::_morphism::morphism;
using morphism_internal_t = morphism::morphism_internal_t;

#pragma region morphism_internal_t
asalib morphism_internal_t::morphism_internal_t
(types::word _a, types::word _b) try :
	a{_a},
	b{_b}
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib morphism_internal_t::morphism_internal_t
(const morphism_internal_t& copy) try :
	a{copy.a},
	b{copy.b}
{

} asalib2_public_types_exception_badConstruction_rethrow

asalib morphism_internal_t::morphism_internal_t
(morphism_internal_t&& move) noexcept :
	a{ _STD move(move.a)},
	b{ _STD move(move.b)}
{
	// noop
}

asalib morphism_internal_t& morphism_internal_t::operator=
(const morphism_internal_t& copy)
{
	a = copy.a;
	b = copy.b;
	return *this;
}

asalib morphism_internal_t& morphism_internal_t::operator=
(morphism_internal_t&& move) noexcept
{
	a = _STD move(move.a);
	b = _STD move(move.b);
	return *this;
}

asalib types::boolean morphism_internal_t::operator<
(const morphism_internal_t& other) const
{
	if (a < other.a) {
		return true;
	}
	return (b < other.b);
}
#pragma endregion

#pragma region morphism
asalib morphism::morphism
(types::word a, types::word b) try :
	m_morphism_internal{a, b}
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib morphism::morphism
(const morphism& copy) try :
	m_morphism_internal{copy.m_morphism_internal}
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib morphism::morphism
(morphism&& move) noexcept :
	m_morphism_internal{ _STD move(move.m_morphism_internal)}
{
	// noop
}

asalib morphism& morphism::operator=
(const morphism& copy)
{
	m_morphism_internal = copy.m_morphism_internal;
	return *this;
}

asalib morphism& morphism::operator=
(morphism&& move) noexcept
{
	m_morphism_internal = _STD move(move.m_morphism_internal);
	return *this;
}

asalib bool morphism::operator<
(const morphism& other) const
{
	return m_morphism_internal < other.m_morphism_internal;
}

asalib types::size morphism::applyMorphism
(const types::word& input, types::word& output) const
{
	types::size outputLength = { 0 };
	types::size lengthA = m_morphism_internal.a.length();
	types::size lengthB = m_morphism_internal.b.length();

	for (const auto& block : input.m_blocks) {
		if (block.character == constants::Alphabet[0])
		{
			outputLength += lengthA * block.blockLength;
			for (types::length counter = 0; counter < block.blockLength; counter++) {
				output += m_morphism_internal.a;
			}
		}
		else 
		{
			outputLength += lengthB * block.blockLength;
			for (types::length counter = 0; counter < block.blockLength; counter++) {
				output += m_morphism_internal.b;
			}
		}
	}

	return outputLength;
}
#pragma endregion
