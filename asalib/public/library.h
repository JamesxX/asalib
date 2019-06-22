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

#ifdef ASALIB_COMPILE
#define asalib __declspec(dllexport) 
#else
#define asalib __declspec(dllimport) 
#endif

namespace AbelianSquaresAnalysis {
	
	/// Build version of library.
	extern asalib const char* BUILD;
}