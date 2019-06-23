/// @file library.h
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, declaring important preprocessor directives.
/// This header includes information of when the library was built, allowing restrictions on library versions.

#pragma once

#include <iostream>
#define asalib_wait_always()\
{\
	printf("Press any key to continue . . .\n");\
	char x;\
	std::cin >> x;\
}
#ifdef _DEBUG
#define asalib_wait_debug() asalib_wait_always()
#else
#define asalib_wait_debug()
#endif

#if defined _WIN32 || defined __CYGWIN__
#ifdef ASALIB_COMPILE
#ifdef __GNUC__
#define asalib __attribute__ ((dllexport))
#else
#define asalib __declspec(dllexport)
#endif
#else
#ifdef __GNUC__
#define asalib __attribute__ ((dllimport))
#else
#define asalib __declspec(dllimport)
#endif
#endif
#define asalib_local
#else
#if __GNUC__ >= 4
#define asalib __attribute__ ((visibility ("default")))
#define asalib_local  __attribute__ ((visibility ("hidden")))
#else
#define asalib
#define asalib_local
#endif
#endif

namespace AbelianSquaresAnalysis {
	
	/// Build version of library.
	extern asalib const char* BUILD;
}