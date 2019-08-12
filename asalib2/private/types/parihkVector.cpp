#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\types\parihkVector.hpp>

#include <asalib2\public\types\exception\badConstruction.hpp>

namespace types = asalib2_ns::types;
using parihkVector = types::_parihkvector::parihkVector;
using parihkVector_internal_t = parihkVector::parihkVector_internal_t;

asalib parihkVector_internal_t::parihkVector_internal_t
(parihkVector::quantity_t _a, parihkVector::quantity_t _b) try :
	a{_a},
	b{_b}
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib parihkVector_internal_t::parihkVector_internal_t
(const parihkVector_internal_t& copy) try :
	a{ copy.a },
	b{ copy.b }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib parihkVector_internal_t::parihkVector_internal_t
(parihkVector_internal_t&& move) noexcept :
	a{ _STD move(move.a) },
	b{ _STD move(move.b) }
{

}

asalib parihkVector_internal_t& parihkVector_internal_t::operator=
(const parihkVector_internal_t& copy)
{
	a = { copy.a };
	b = { copy.b };
	return *this;
}

asalib parihkVector_internal_t& parihkVector_internal_t::operator=
(parihkVector_internal_t&& move) noexcept
{
	a = { _STD move(move.a) };
	b = { _STD move(move.b) };
	return *this;
}

asalib bool parihkVector_internal_t::operator<
(const parihkVector_internal_t& other) const
{
	if (a != other.a)
	{
		return (a < other.a);
	}
	return (b < other.b);
}

asalib parihkVector::parihkVector
(parihkVector::quantity_t a, parihkVector::quantity_t b) try
	: m_parihkVector_internal { a , b }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib parihkVector::parihkVector
(const parihkVector& copy) try
	: m_parihkVector_internal { copy.m_parihkVector_internal }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib parihkVector::parihkVector
(parihkVector&& move) noexcept
	: m_parihkVector_internal{ _STD move(move.m_parihkVector_internal) }
{
	// noop
}

asalib parihkVector& parihkVector::operator=
(const parihkVector& copy)
{
	m_parihkVector_internal = copy.m_parihkVector_internal;
	return *this;
}

asalib parihkVector& parihkVector::operator=
(parihkVector&& move) noexcept
{
	m_parihkVector_internal = _STD move(move.m_parihkVector_internal);
	return *this;
}

asalib parihkVector::operator std::string
() const
{
	double size_a = m_parihkVector_internal.a > 0 ? (double)floor(log10(static_cast<double>(m_parihkVector_internal.a))) : 1;
	double size_b = m_parihkVector_internal.b > 0 ? (double)floor(log10(static_cast<double>(m_parihkVector_internal.b))) : 1;
	double bufferSize = 6 + size_a + size_b;

	_STD string output;
	output.reserve(static_cast<size_t>(bufferSize));

	output.append("(");
	output.append(_STD to_string(m_parihkVector_internal.a));
	output.append(", ");
	output.append(_STD to_string(m_parihkVector_internal.b));
	output.append(")^2");

	return output;
}

asalib types::boolean parihkVector::operator<
(const parihkVector& right) const
{
	return m_parihkVector_internal < right.m_parihkVector_internal;
}

asalib types::boolean parihkVector::isTrivial
() const
{
	return (
		(m_parihkVector_internal.a == 0 && m_parihkVector_internal.b != 0) || 
		(m_parihkVector_internal.a != 0 && m_parihkVector_internal.b == 0)
	);
}
