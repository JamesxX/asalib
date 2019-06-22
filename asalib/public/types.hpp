/// @file types.hpp
/// @author James R Swift
/// @date 20/06/2019
/// @brief Common header for library, defining commonly used types.

#pragma once
#include <string>
#include <map>

//#include <common/iterator_tpl.h>

namespace AbelianSquaresAnalysis {

	namespace types {

		typedef bool boolean; ///< Internally used type for consistency between builds.
		typedef std::string word; ///< Type containing words, substrings and prefixes.
		typedef std::map<types::word, types::word> mapping; ///< Type containing morphism information.
		typedef std::map<std::string, mapping> morphism_list; ///< Type containing a list of morphisms.

#ifdef _WIN64
		typedef unsigned int length; ///< Internally used type for consistency between builds.
		typedef unsigned long long int integer; ///< Internally used type for consistency between builds.
#else
		typedef unsigned int length; ///< Internally used type for consistency between builds.
		typedef unsigned long int integer; ///< Internally used type for consistency between builds.
#endif

		/// @brief Structure used to store information about a given substring, currently limited to alphabets of size 2.
		/// @todo Allow greater alphabet sizes.
		struct parihkVector {
			types::integer a = 0; ///< Counter of instances of first alphabet letter.
			types::integer b = 0; ///< Counter of instances of second alphabet letter.
		};

		//typedef std::map<char,unsigned int> characterCount;
		/*typedef parihkVector characterCount;

		class word {
		private:
			size_t _length = 0;
			char* _c_str;
			void initialize_c_str(const char* s);
			void initialize_c_str(const char* s, size_t length);
		public:

			word(const char* s = "");
			word(const char* s, size_t length);
			word(const types::word& other); // copy constructor
			word(const std::string& other);
			~word();

			types::length length() const;
			types::word substr(types::length position);
			types::word substr(types::length position, size_t length);
			types::characterCount countOccurences();
			char at(size_t position) const;

			inline bool operator==(const types::word& right) const;
			inline bool operator!=(const types::word& right) const;
			inline bool operator<(const types::word& right) const;
			inline bool operator>(const types::word& right) const;
			inline bool operator<=(const types::word& right) const;
			inline bool operator>=(const types::word& right) const;

			inline operator std::string();

			inline types::word& operator=(const types::word& other); // coppy assingment

			STL_TYPEDEFS(char);

			struct iterator_state {
				int pos;
				inline void next(const types::word* ref);
				inline void prev(const types::word* ref);
				inline void begin(const types::word* ref);
				inline void end(const types::word* ref);
				inline char& get(types::word* ref);
				inline const char& get(const types::word* ref);
				inline bool cmp(const iterator_state& s) const;
			};
			
			// Mutable Iterator:
			typedef iterator_tpl::iterator<types::word, char&, iterator_state> iterator;
			iterator begin();
			iterator end();

			// Const Iterator:
			typedef iterator_tpl::const_iterator<types::word, char&, iterator_state> const_iterator;
			const_iterator begin() const;
			const_iterator end() const;

			// Reverse `iterator_state`:
			struct reverse_iterator_state : public iterator_state {
				inline void next(const types::word* ref);
				inline void prev(const types::word* ref);
				inline void begin(const types::word* ref);
				inline void end(const types::word* ref);
			};

			// Mutable Reverse Iterator:
			typedef iterator_tpl::iterator<types::word, char&, reverse_iterator_state> reverse_iterator;
			reverse_iterator rbegin();
			reverse_iterator rend();

			// Const Reverse Iterator:
			typedef iterator_tpl::const_iterator<types::word, char&, reverse_iterator_state> const_reverse_iterator;
			const_reverse_iterator rbegin() const;
			const_reverse_iterator rend() const;
		};*/
	}

}