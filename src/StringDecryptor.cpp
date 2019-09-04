#include <string>
#include "ICipher.hpp"
#include "StringDecryptor.hpp"

std::string StringDecryptor::decrypt_thread(std::string encoded, size_t fpos, char (ICipher::*decrypt_fun)(char, size_t)) {
	for (std::string::iterator iter = encoded.begin(); iter != encoded.end(); iter++) {
		if (!this->_cipher->isAlphabetChar(*iter)) {
			iter--;
			encoded.erase(iter + 1);
		}
	}
	for (size_t position = 0; position < encoded.size(); position++)
		encoded[position] = (this->_cipher.get()->*decrypt_fun)(
				encoded[position], position + fpos);
	return encoded;
}

void StringDecryptor::decrypt(const std::string &encoded, Mode mode) {
	this->_buffer.clear();
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
}

std::string StringDecryptor::getResult() {
	std::string ret_val;
	for (std::future<std::string> &result: this->_buffer){
		if (result.wait_for(std::chrono::nanoseconds(1)) == std::future_status::ready)
			ret_val += result.get();
	}
	return ret_val;
}

bool StringDecryptor::ready() {
	for (std::future<std::string> &result: this->_buffer){
		if (result.wait_for(std::chrono::nanoseconds(1)) != std::future_status::ready)
			return false;
	}
	return true;
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
