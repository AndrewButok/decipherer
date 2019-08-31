#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include "ICipher.hpp"
#include "StringDecryptor.hpp"

void StringDecryptor::decrypt_thread(int begin, int thread_count, std::string &encoded) {
	for (size_t i = begin; i < encoded.size(); i += thread_count) {
		std::lock_guard<std::mutex> lockGuard(this->_mutex);
		encoded[i] = this->_cipher->decrypt(encoded[i], i);
	}
}

void StringDecryptor::encrypt_thread(int begin, int thread_count, std::string &raw) {
	for (size_t i = begin; i < raw.size(); i += thread_count) {
		std::lock_guard<std::mutex> lockGuard(this->_mutex);
		raw[i] = this->_cipher->encrypt(raw[i], i);
	}
}

void StringDecryptor::decrypt(std::string &encoded, Mode mode) {
	for (std::string::iterator pos = encoded.begin(); pos != encoded.end(); pos++) {
		if (!this->_cipher->isAlphabetChar(*pos)) {
			pos--;
			encoded.erase(pos + 1);
		}
	}
	std::vector<std::thread> thread_vector(4);
	for (int i = 0; i < 4; i++) {
		if (mode == Mode::Normal)
			thread_vector[i] = std::thread(&StringDecryptor::decrypt_thread,
				this, i, 4, std::ref(encoded));
		else if (mode == Mode::Reversed)
			thread_vector[i] = std::thread(&StringDecryptor::encrypt_thread,
										   this, i, 4, std::ref(encoded));
	}
	for (std::thread &thr: thread_vector)
		thr.join();
}


StringDecryptor::StringDecryptor(): _cipher(nullptr), _mutex() {
}

StringDecryptor::StringDecryptor(CipherPtr cipher): _cipher(std::move(cipher)), _mutex(){
}

StringDecryptor::StringDecryptor(const StringDecryptor &decipher): _cipher(nullptr), _mutex() {

}

StringDecryptor &StringDecryptor::operator=(const StringDecryptor &decipher) {
	return *this;
}

StringDecryptor::~StringDecryptor() = default;
