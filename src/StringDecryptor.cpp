#include <string>
#include "ICipher.hpp"
#include "StringDecryptor.hpp"

std::string StringDecryptor::decrypt_thread(std::string encoded, size_t fpos, char (ICipher::*decrypt_fun)(char, size_t)) {
	for (std::string::iterator position = encoded.begin(); position != encoded.end(); position++) {
		if (!this->_cipher->isAlphabetChar(*position)) {
			position--;
			encoded.erase(position + 1);
		}
	}
	for (size_t position = 0; position < encoded.size(); position++)
		encoded[position] = (this->_cipher.get()->*decrypt_fun)(
				encoded[position], position + fpos);
	return encoded;
}

void StringDecryptor::decrypt(std::string &encoded, Mode mode) {
	char (ICipher::*decrypt_fun)(char, size_t) = mode == Mode::Normal ?
			&ICipher::decrypt : &ICipher::encrypt;
	for (size_t pos = 0; pos < 4; pos++) {
		size_t	str_begin = (encoded.size() / 4) * pos,
				char_number = encoded.size() / 4 + (pos == 3 ? encoded.size() % 4 : 0);
		this->_buffer.push_back(
				std::async(std::launch::async,
					&StringDecryptor::decrypt_thread, this,
					std::move(encoded.substr(str_begin, char_number)), str_begin, decrypt_fun));
	}
	encoded.clear();
	std::for_each(_buffer.begin(), _buffer.end(), [&encoded](std::future<std::string> &c) {
		encoded += c.get();
	});
}


StringDecryptor::StringDecryptor(): _cipher(nullptr) {
}

StringDecryptor::StringDecryptor(CipherPtr cipher): _cipher(std::move(cipher)) {
}

StringDecryptor::StringDecryptor(const StringDecryptor &decipher): _cipher(nullptr) {

}

StringDecryptor &StringDecryptor::operator=(const StringDecryptor &decipher) {
	return *this;
}

StringDecryptor::~StringDecryptor() = default;
