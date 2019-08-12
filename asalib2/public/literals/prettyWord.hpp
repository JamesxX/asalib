/// @file asalib2\public\types\literals\prettyWord.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Definitions for the asalib_pw_MACRO literal function, which
/// will expand a pretty-formatted word into its verbose form.

#ifndef asalib2_public_types_literals_pw_INCLUDEGUARD
#define asalib2_public_types_literals_pw_INCLUDEGUARD
#pragma once

#include <asalib2\public\library.hpp>
#include <asalib2\public\fwd.hpp>

#include <string>
#include <regex>

#define asalib_pw_MACRO _asalibpw

namespace asalib2_ns
{

	namespace literals
	{

		namespace
		{

			inline void invalid_argument_error(std::string input)
			{
				throw new std::invalid_argument(
					"Error when using _asalibpw literal! Invalid Argument \'"
					+ input
					+ "\'");
			}

		} // hidden namespace

		inline std::string prettyWord(std::string input)
		{
			std::string wordFull;
			const std::regex pattern("(\\w)(\\d+)");

			auto words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
			auto words_end = std::sregex_iterator();

			if (std::distance(words_begin, words_end) == 0) {
				invalid_argument_error(input);
				return "";
			}

			for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
				std::smatch match = *i;
				wordFull += std::string(std::stoi(match.str(2)), match.str(1).c_str()[0]);
			}

			return wordFull;
		}

		inline std::string operator "" asalib_pw_MACRO(const char* ptr) {
			return prettyWord(ptr);
		}

		//inline std::string operator "" asalib_pw_MACRO(unsigned long long int) 

		//inline std::string operator "" asalib_pw_MACRO(long double) 

		inline std::string operator "" asalib_pw_MACRO(char input)
		{
			return std::string(1, input);
		}

		//inline std::string operator "" asalib_pw_MACRO(wchar_t input)

#if asalib2_cpp_20
		inline std::string operator "" asalib_pw_MACRO(char8_t input)
		{
			return std::string(1, (char)input);
		}
#endif // asalib2_cpp_20

		//inline std::string operator "" asalib_pw_MACRO(char16_t input)

		//inline std::string operator "" asalib_pw_MACRO(char32_t input)

		inline std::string operator "" asalib_pw_MACRO(const char* ptr, std::size_t size) {
			return prettyWord(ptr);
		}

		// inline std::string operator "" asalib_pw_MACRO(const wchar_t* ptr, std::size_t size) 

#if asalib2_cpp_20
		inline std::string operator "" asalib_pw_MACRO(const char8_t* ptr, std::size_t size) {
			return prettyWord((char)ptr);
		}
#endif // asalib2_cpp_20

		// inline std::string operator "" asalib_pw_MACRO(const char16_t* ptr, std::size_t size)

		//inline std::string operator "" asalib_pw_MACRO(const char32_t* ptr, std::size_t size)


	} // namespace literals

} // namespace asalib2_ns

#endif // asalib2_public_types_literals_pw_INCLUDEGUARD
