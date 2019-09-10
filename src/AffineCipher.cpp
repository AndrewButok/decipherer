#include <cstdlib>
#include <stdexcept>
#include "AffineCipher.hpp"


char AffineCipher::encrypt(char in, size_t) {
	long long char_pos = this->_alphabet.find(in);
	if (char_pos == std::string::npos)
		return ' ';
	char_pos *= this->_a;
	char_pos += this->_b;
	char_pos %= static_cast<long long>(this->_alphabet.size());
	if (char_pos < 0)
		char_pos = static_cast<long long>(this->_alphabet.size()) - char_pos;
	return this->_alphabet[char_pos];
}

char AffineCipher::decrypt(char in, size_t) {
	long long char_pos = this->_alphabet.find(in);
	if (char_pos == std::string::npos)
		return ' ';
	char_pos -= this->_b;
	char_pos *= this->_a;
	char_pos %= static_cast<long long>(this->_alphabet.size());
	if (char_pos < 0)
		char_pos = static_cast<long long>(this->_alphabet.size()) + char_pos;
	return this->_alphabet[char_pos];
}

AffineCipher::AffineCipher(int a, int b, std::string alphabet): ACipher(std::move(alphabet)) {
	if (!isCoprime(a, _alphabet.size()))
		throw std::invalid_argument("Invalid Affine cipher's a key value: must be coprime with alphabet size");
	this->_a = a;
	this->_b = b;
}

AffineCipher::AffineCipher(const AffineCipher &affineCipher): ACipher(affineCipher._alphabet), _a(affineCipher._a), _b(affineCipher._b) {

}

AffineCipher::~AffineCipher() = default;

bool AffineCipher::isCoprime(int a, int b) {
	if (a == b) {
		return a == 1;
	}
	if (a > b)
		return isCoprime(a - b, b);
	else
		return isCoprime(b - a, a);
}

AffineCipher &AffineCipher::operator=(const AffineCipher &affineCipher) {
	(this->ACipher::operator=)(affineCipher);
	this->_a = affineCipher._a;
	this->_b = affineCipher._b;
	return *this;
}

