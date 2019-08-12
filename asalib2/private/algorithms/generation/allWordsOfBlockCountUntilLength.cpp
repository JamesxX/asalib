#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <asalib2\public\algorithms\generation\allWordsOfBlockCountUntilLength.hpp>
#include <asalib2\public\algorithms\generation\genericWord.hpp>

#include <math.h>
#include <stdexcept>

namespace types = asalib2_ns::types;
namespace _ALWOBCUL = asalib2_ns::algorithms::generation::_ALWOBCUL;

inline unsigned long long 
factorial
(unsigned long long x)
{
	if (x == 0) return 1;
	if (x == 1) return 1;
	
	unsigned long long output;
	for (unsigned long long it = 1; it <= x; it++)
	{
		output *= it;
	}

	return output;
}

inline unsigned long long
nCr
(unsigned long long n, unsigned long long r)
{
	if (r > n) return 0;
	if (r * 2 > n) return n - r;
	if (n == r) return 1;
	if (r == 0 && n != 0) return 1;

	unsigned long long result = n;
	for (unsigned long long i = 2; i <= r; ++i)
	{
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}

asalib _STD vector<types::word>
_ALWOBCUL::allWordsOfBlockCountUntilLength
(ALWOBCUL_args_t input)
{

	_STD vector<types::word> output;
	output.reserve(static_cast<size_t>(nCr(input._length - 1, input._blockCount - 1)));

	if (input._blockCount == 2) // End of recursion
	{
		for (types::length i = 1; i < input._length; i++)
		{
			output.push_back(
				types::word(constants::Alphabet[input.positionAlphabet], i) +
				types::word(constants::Alphabet[!input.positionAlphabet], input._length - i)
			);
		}
	}
	else
	{
		for (unsigned int i = 1; i < (input._length ); i++)
		{
			ALWOBCUL_args_t recursionArgs = {
				input._blockCount - 1,
				input._length - i,
				!input.positionAlphabet
			};

			for (const auto& entry : _ALWOBCUL::allWordsOfBlockCountUntilLength(recursionArgs))
			{
				output.push_back(types::word(constants::Alphabet[input.positionAlphabet], i) + entry);
			}
		}
	}

	return output;

}