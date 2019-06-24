/// @file word.cpp
/// @author James R Swift
/// @date 23/06/2019
/// @brief Implements common functionality word words and parihk vectors

#include <asalib/public/types.hpp>
#include <algorithm>

AbelianSquaresAnalysis::types::parihkVector::parihkVector() 
	: std::map<char, types::integer>()
{
}

bool asalib AbelianSquaresAnalysis::types::parihkVector::isTrivial() const {
	unsigned int count = 0;
	for (const auto& entry : *this) {
		if (entry.second != 0) count++;
	}
	return count == 1; // if a parihk vector of ([0,]*)^2 is tested, isTrivial returns false;
}

void asalib AbelianSquaresAnalysis::types::to_json(nlohmann::json& j, const AbelianSquaresAnalysis::types::parihkVector& data) {
	j = (std::map<char, types::integer>)data;
}

void asalib AbelianSquaresAnalysis::types::from_json(const nlohmann::json& j, AbelianSquaresAnalysis::types::parihkVector& data) {
	j.get_to<std::map<char, types::integer>>(data);
}

AbelianSquaresAnalysis::types::parihkVector asalib AbelianSquaresAnalysis::types::word::countAlphabetSize() {
	types::parihkVector out;
	for (auto character : *this) {
		if (out.find(character) == out.end()) {
			out.insert(std::pair<char,types::integer>(character, 0));
		}
	}
	return out;
}

void AbelianSquaresAnalysis::types::word::countOccurences(size_t offset, size_t count, AbelianSquaresAnalysis::types::parihkVector& out) {
	//std::string substr = this->substr(offset, count);
	for (auto& alphabetCharacter : out) {
		//alphabetCharacter.second = std::count(substr.begin(), substr.end(), alphabetCharacter.first);
		alphabetCharacter.second = std::count(this->begin()+offset, this->begin()+offset+count, alphabetCharacter.first);
	}
}

void asalib AbelianSquaresAnalysis::types::to_json(nlohmann::json& j, const AbelianSquaresAnalysis::types::word& data) {
	j = (std::string)data;
}

void asalib AbelianSquaresAnalysis::types::from_json(const nlohmann::json& j, AbelianSquaresAnalysis::types::word& data) {
	j.get_to<std::string>(data);
}