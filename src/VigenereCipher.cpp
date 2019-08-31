#include "VigenereCipher.hpp"

char VigenereCipher::encrypt(char in, size_t pos) {
	long long char_pos = this->_alphabet.find(in);
	if (char_pos == std::string::npos)
		throw std::invalid_argument(
				static_cast<std::string>("Character ") + in + " is not present in alphabet");
	char_pos += _shifts[pos % _shifts.size()];
	char_pos %= static_cast<long long>(_alphabet.size());
	if (char_pos < 0)
		char_pos = static_cast<long long>(this->_alphabet.size()) - char_pos;
	return _alphabet[char_pos];
}

char VigenereCipher::decrypt(char in, size_t pos) {
	long long char_pos = this->_alphabet.find(in);
	if (char_pos == std::string::npos)
		throw std::invalid_argument(
				static_cast<std::string>("Character ") + in + " is not present in alphabet");
	char_pos += static_cast<long long>(_alphabet.size());
	char_pos -= _shifts[pos % _shifts.size()];
	char_pos %= static_cast<long long>(_alphabet.size());
	if (char_pos < 0)
		char_pos = static_cast<long long>(this->_alphabet.size()) - char_pos;
	return _alphabet[char_pos];
};

VigenereCipher::VigenereCipher(const std::string &key, std::string alphabet,
							const std::string &key_alphabet):
	ACipher(std::move(alphabet)) {
	if (!key_alphabet.empty()){
		if (!_isAlphabetValid(key_alphabet))
			throw std::invalid_argument("Wrong key alphabet.");
		for (char keychar: key){
			size_t pos = key_alphabet.find(keychar);
			if (pos == std::string::npos)
				throw std::invalid_argument("Wrong key.");
			_shifts.push_back(static_cast<long>(pos));
		}
	}
	else {
		for (char keychar: key){
			size_t pos = this->_alphabet.find(keychar);
			if (pos == std::string::npos)
				throw std::invalid_argument("Wrong key.");
			_shifts.push_back(static_cast<long>(pos));
		}
	}
}

VigenereCipher::VigenereCipher():
	ACipher(), _shifts() {

}

VigenereCipher::VigenereCipher(const VigenereCipher &vigenereCipher):
	ACipher(vigenereCipher), _shifts(vigenereCipher._shifts) {

}

VigenereCipher &VigenereCipher::operator=(const VigenereCipher &vigenereCipher){
	(this->ACipher::operator=)(vigenereCipher);
	this->_shifts = vigenereCipher._shifts;
	return *this;
}

VigenereCipher::~VigenereCipher() = default;