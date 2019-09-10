#include "ACipher.hpp"

bool ACipher::_isAlphabetValid(const std::string &alphabet) {
	if (alphabet.empty())
		return false;
	for (size_t i = 0; i < alphabet.size(); i++) {
		if (alphabet.find(alphabet[i], i + 1) != std::string::npos)
			return false;
	}
	return true;
}

ACipher::ACipher(std::string alphabet) {
	if (!_isAlphabetValid(alphabet))
		throw std::invalid_argument("Invalid alphabet.");
	this->_alphabet = std::move(alphabet);
}

ACipher &ACipher::operator=(const ACipher &cipher) {
	this->_alphabet = cipher._alphabet;
	return *this;
}

bool ACipher::isAlphabetChar(char ch) {
	return this->_alphabet.find(ch) != std::string::npos;
}

ACipher::~ACipher() = default;



