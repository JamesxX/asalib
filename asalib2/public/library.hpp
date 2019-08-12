/// @file asalib2\public\library.hpp
/// @author James R Swift
/// @date 10/08/2019
/// @brief Important preprocessor definitions critical to the functioning of asalib2. 
/// This header includes the declaration for the build variable, allowing for future compatibility. 
/// Include this header first when using the library.

#ifndef asalib2_public_library_INCLUDEGUARD
#define asalib2_public_library_INCLUDEGUARD
#pragma once

#pragma region asalib2_dll_interface
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
#pragma endregion

#define asalib2_cpp_20 _HAS_CXX20

#if asalib2_cpp_20
#define asalib2_likely [[likely]]
#else
#define asalib2_likely
#endif // asalib2_cpp_20

#define asalib2_ns asalib2

namespace asalib2_ns {

	/// Build version of the library
	extern asalib const char* build;

} // namespace asalib2_ns

#ifndef _STD
#define _STD ::std::
#endif // _STD

#endif // asalib2_public_library_INCLUDEGUARD
