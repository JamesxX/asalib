/*#include "types.hpp"

using namespace AbelianSquaresAnalysis;

types::word::word(const char* s = "") { // constructor
	initialize_c_str(s);
}

types::word::word(const char* s = "", size_t length) { // constructor
	initialize_c_str(s, length);
}

types::word::word(const types::word& other) { // copy constructor
	initialize_c_str(other._c_str);
}

types::word::word(const std::string& other) :
	word(other.c_str())
{

}

types::word::~word() { //destructor
	delete[] _c_str;
}

void types::word::initialize_c_str(const char* s, size_t _length) {
	_c_str = new char[_length];
	std::memcpy(_c_str, s, _length);
}

void types::word::initialize_c_str(const char* s) {
	_length = std::strlen(s) + 1;
	_c_str = new char[_length];
	std::memcpy(_c_str, s, _length);
}

types::length types::word::length() const {
	return _length;
}

types::word types::word::substr(types::length position) {
	char* substring = _c_str + position;
	return types::word(substring);
}

types::word types::word::substr(types::length position, size_t length) {
	char* substring = _c_str + position;
	return types::word(substring, length);
}

types::characterCount types::word::countOccurences() {
	types::characterCount counter;
	for (char character : *this) {
		if (character = 'a') counter.a++;
		if (character = 'b') counter.b++;
	}
	return counter;
}

char types::word::at(size_t position) const {
	return *(_c_str + position); // Beware of out of range!
}

inline bool types::word::operator==(const types::word& right) const {
	return strcmp(this->_c_str, right._c_str) == 0;
}

inline bool types::word::operator!=(const types::word& right) const {
	return strcmp(this->_c_str, right._c_str) != 0;
}
inline bool types::word::operator<(const types::word& right) const {
	strcmp(this->_c_str, right._c_str) < 0;
}

inline bool types::word::operator>(const types::word& right) const {
	strcmp(this->_c_str, right._c_str) > 0;
}

inline bool types::word::operator<=(const types::word& right) const {
	strcmp(this->_c_str, right._c_str) <= 0;
}

inline bool types::word::operator>=(const types::word& right) const {
	strcmp(this->_c_str, right._c_str) >= 0;
}

inline types::word::operator std::string() {
	return std::string(_c_str);
}

inline types::word& types::word::operator=(const types::word& other) { // copy assingment
	// IMPLEMENT
}

inline void types::word::iterator_state::next(const types::word* ref) { ++pos; }
inline void types::word::iterator_state::prev(const types::word* ref) { --pos; }
inline void types::word::iterator_state::begin(const types::word* ref) { pos = 0; }
inline void types::word::iterator_state::end(const types::word* ref) { pos = ref->length(); }
inline char& types::word::iterator_state::get(types::word* ref) { return ref->_c_str[pos]; }
inline const char& types::word::iterator_state::get(const types::word* ref) { return ref->_c_str[pos]; }
inline bool types::word::iterator_state::cmp(const types::word::iterator_state& s) const { return pos != s.pos; }

types::word::iterator types::word::begin() { return  types::word::iterator::begin(this); }
types::word::iterator types::word::end() { return  types::word::iterator::end(this); }

types::word::const_iterator types::word::begin() const { return  types::word::const_iterator::begin(this); }
types::word::const_iterator types::word::end() const { return  types::word::const_iterator::end(this); }

inline void types::word::reverse_iterator_state::next(const types::word* ref) { types::word::iterator_state::prev(ref); }
inline void types::word::reverse_iterator_state::prev(const types::word* ref) { types::word::iterator_state::next(ref); }
inline void types::word::reverse_iterator_state::begin(const types::word* ref) { types::word::iterator_state::end(ref);  types::word::iterator_state::prev(ref); }
inline void types::word::reverse_iterator_state::end(const types::word* ref) { types::word::iterator_state::begin(ref);  types::word::iterator_state::prev(ref); }

types::word::reverse_iterator types::word::rbegin() { return  types::word::reverse_iterator::begin(this); }
types::word::reverse_iterator types::word::rend() { return types::word::reverse_iterator::end(this); }

types::word::const_reverse_iterator types::word::rbegin() const {
	return  types::word::const_reverse_iterator::begin(this);
}
types::word::const_reverse_iterator types::word::rend() const {
	return  types::word::const_reverse_iterator::end(this);
}*/