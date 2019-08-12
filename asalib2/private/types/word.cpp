#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>
#include <asalib2\public\constants.hpp>

#include <asalib2\public\types\word.hpp>
#include <asalib2\public\types\parihkVector.hpp>
#include <asalib2\public\types\exception\badConstruction.hpp>

#include <asalib2\public\algorithms\analysis\stringContainsDigits.hpp>
#include <regex>
#include <algorithm>

namespace types = asalib2_ns::types;
using block = types::_word::block;

asalib block::block(char _character, types::length _blockLength) try :
	character{ _character }, blockLength{ _blockLength }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow


using word = types::_word::word;

asalib word::word() try
	: m_blocks{ }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib word::word(const word& copy) try
	: m_blocks{ copy.m_blocks }
{
	// noop
} asalib2_public_types_exception_badConstruction_rethrow

asalib word::word(word&& move) noexcept
	: m_blocks{std::move(move.m_blocks)}
{
	// noop
}

asalib word::word(_STD initializer_list<types::length> l) try
{
	bool even = false;
	for (const auto& blockLength : l)
	{
		m_blocks.emplace_back(
			constants::Alphabet[even],
			blockLength
		);
		even = !even;
	}
} asalib2_public_types_exception_badConstruction_rethrow

asalib word::word(char character, types::length length) try
{
	m_blocks.push_back({
		(char)toupper(character),
		length
	});
} asalib2_public_types_exception_badConstruction_rethrow

asalib word::word( _STD string input) try
{

	if (input.size() == 0)
	{
		return;
	}

	if (algorithms::analysis::stringContainsDigits(input))
	{
		const _STD regex pattern("(\\w)(\\d+)");

		auto words_begin = _STD sregex_iterator(input.begin(), input.end(), pattern);
		auto words_end = _STD sregex_iterator();

		if (_STD distance(words_begin, words_end) == 0) {
			throw new _STD invalid_argument("Call to " __FUNCTION__ " failed as argument 1 was not the correct format");
			return;
		}

		for (_STD sregex_iterator i = words_begin; i != words_end; ++i) {
			m_blocks.emplace_back(
				(char)toupper(i->str(1).c_str()[0]),
				(types::length)_STD stoi(i->str(2))
			);
		}
	}
	else
	{
		for (const char& character : input)
		{
			if (m_blocks.size() < 1)
			{
				m_blocks.emplace_back(
					(char)toupper(character),
					1
				);
				continue;
			}

			if (m_blocks.back().character == (char)toupper(character))
			{
				m_blocks.back().blockLength++;
			}
			else
			{
				m_blocks.emplace_back(
					(char)toupper(character),
					1
				);
			}
		}
	}

} asalib2_public_types_exception_badConstruction_rethrow

asalib word& word::operator=(const word& copy)
{
	m_blocks = copy.m_blocks;
	return *this;
}

asalib word& word::operator=(word&& move) noexcept
{
	m_blocks = _STD move(move.m_blocks);
	return *this;
}

asalib void word::generateParihkVector(types::parihkVector& out) const
{
	for (const block& current : m_blocks)
	{
		if ((char)toupper(current.character) == constants::Alphabet[0])
		{
			out.value.a += current.blockLength;
		}
		else
		{
			out.value.b += current.blockLength;
		}
	}
}

asalib word::operator std::string() const
{
	_STD string output;
	output.reserve(length());

	for (const block& current : m_blocks)
	{
		output.append(current.blockLength, current.character);
	}

	return output;
}

asalib _STD string word::toPretty() const
{
	double bufferSize = 0;
	for (const auto& block : m_blocks)
	{
		bufferSize += floor(1 + log10(block.blockLength));
	}
	std::string output;
	output.reserve(static_cast<size_t>(bufferSize));

	for (const auto& block : m_blocks)
	{
		output.append(1, block.character);
		output.append(_STD to_string(block.blockLength));
	}

	return output;
}

asalib types::boolean word::operator<(word const& b) const {

	if (m_blocks.size() != b.m_blocks.size())
	{
		return m_blocks.size() < b.m_blocks.size();
	}

	if (toupper(m_blocks.begin()->character) != toupper(b.m_blocks.begin()->character))
	{
		return toupper(m_blocks.begin()->character) < toupper(b.m_blocks.begin()->character);
	}

	for (size_t position = { 0 }; position < m_blocks.size(); position++)
	{
		if (m_blocks[position].blockLength != b.m_blocks[position].blockLength)
		{
			return (m_blocks[position].blockLength < b.m_blocks[position].blockLength);
		}
	}
	
	return false;
}

asalib word word::operator+(const word& other) const
{
	types::word copy(*this);
	copy += other;
	return copy;
}

asalib word& word::operator+=(const word& other)
{

	if (m_blocks.size() < 1)
	{
		m_blocks = other.m_blocks;
		return *this;
	}

	auto it = other.m_blocks.begin();
	
	// special case: the end of *this is the same character block as begining of other
	if (m_blocks.back().character == it->character)
	{
		m_blocks.back().blockLength += it->blockLength;
		it++;
	}

	for (; it != other.m_blocks.end(); it++)
	{
		m_blocks.emplace_back(*it);
	}

	return *this;
}

asalib types::length word::length() const
{
	types::length outputLength = { 0 };
	for (const block& current : m_blocks)
	{
		outputLength += (types::length)current.blockLength;
	}
	return outputLength;
}

asalib char word::operator[](types::size location) const
{
	types::size traversed = 0;
	for (const block& current : m_blocks)
	{
		if (traversed < location && location < (traversed + current.blockLength))
		{
			return current.character;
		}
		traversed += current.blockLength;
	}
	
	throw new _STD range_error("Call to " __FUNCTION__ " failed as argument 1 was greater than length of word");
	return NULL;
}

asalib word word::subword(types::size beginpos, types::size desiredLength) const
{
	word output;

	auto positionInWord_begin = getPosition(beginpos);
	auto positionInWord_end = getPosition(beginpos + desiredLength - 1);

	// Special case 1: positionInWord_begin and positionInWord_end are in same block
	if (positionInWord_begin.first == positionInWord_end.first)
	{
		output.m_blocks.emplace_back(
			m_blocks[positionInWord_begin.first].character,
			positionInWord_end.second - positionInWord_begin.second + 1
		);
	}

	// Normal case: positionInWord_begin and positionInWord_end are in different blocks
	else
	{
		// First block
		output.m_blocks.emplace_back(
			m_blocks[positionInWord_begin.first].character,
			m_blocks[positionInWord_begin.first].blockLength - positionInWord_begin.second
		);

		// Middle blocks
		for (types::size it = positionInWord_begin.first + 1; it < positionInWord_end.first; it++)
		{
			output.m_blocks.push_back(m_blocks[it]);
		}

		// End block
		output.m_blocks.emplace_back(
			m_blocks[positionInWord_end.first].character,
			positionInWord_end.second + 1
		);
	}

	if (output.length() < desiredLength)
	{
		throw new _STD range_error(__FUNCTION__ ": beginpos + desiredLength exceed length of parent word!");
	}

	return output;
}

asalib types::boolean word::isAbelianSquare(types::parihkVector& output) const
{

	if (length() <= 1)
	{
		return false;
	}

	if (length() % 2 != 0)
	{
		return false;
	}

	types::parihkVector firstHalf_temp;
	types::parihkVector secondHalf_temp;

	firstHalf().generateParihkVector(firstHalf_temp);
	secondHalf().generateParihkVector(secondHalf_temp);

	if (firstHalf_temp == secondHalf_temp)
	{
		output = firstHalf_temp;
		return true;
	}

	return false;

}

asalib word word::firstHalf() const
{
	return subword(0, (types::size)ceil(length() / 2));
}

asalib word word::secondHalf() const
{
	return subword((types::size)floor(length() / 2), (types::size)ceil(length() / 2));
}

asalib _STD pair<types::size, types::size> word::getPosition(types::size position) const
{
	types::size blockCount = { 0 };
	types::size traversed = { 0 };
	for (const auto& block : m_blocks)
	{
		if (traversed <= position && position < (traversed + block.blockLength))
		{
			return _STD pair<types::size, types::size>(blockCount, position - traversed);
		}
		blockCount++;
		traversed += block.blockLength;
	}

	throw new _STD range_error(__FUNCTION__ ": Out of bounds!");
	return _STD pair<types::size, types::size>(0,0);
}