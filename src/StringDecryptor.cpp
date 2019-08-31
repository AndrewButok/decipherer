#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include "ICipher.hpp"
#include "StringDecryptor.hpp"

void StringDecryptor::decrypt_thread(int begin, int thread_count, std::string &encoded,
									 std::vector<size_t> &to_del) {
	for (size_t i = begin; i < encoded.size(); i += thread_count) {
		std::lock_guard<std::mutex> lockGuard(this->_mutex);
		try {
			encoded[i] = this->_cipher->decrypt(encoded[i], i);
		} catch (std::invalid_argument &ex) {
			to_del.push_back(i);
		}
	}
}

void StringDecryptor::encrypt_thread(int begin, int thread_count, std::string &raw,
									 std::vector<size_t> &to_del) {
	for (size_t i = begin; i < raw.size(); i += thread_count) {
		std::lock_guard<std::mutex> lockGuard(this->_mutex);
		try {
			raw[i] = this->_cipher->encrypt(raw[i], i);
		} catch (std::invalid_argument &ex) {
			to_del.push_back(i);
		}
	}
}

void StringDecryptor::decrypt(std::string &encoded, Mode mode) {
	std::vector<std::thread> thread_vector(4);
	std::vector<size_t> bad_char_positions;
	for (int i = 0; i < 4; i++) {
		if (mode == Mode::Normal)
			thread_vector[i] = std::thread(&StringDecryptor::decrypt_thread,
				this, i, 4, std::ref(encoded), std::ref(bad_char_positions));
		else if (mode == Mode::Reversed)
			thread_vector[i] = std::thread(&StringDecryptor::encrypt_thread,
										   this, i, 4, std::ref(encoded), std::ref(bad_char_positions));
	}
	for (std::thread &thr: thread_vector)
		thr.join();
	for (size_t pos: bad_char_positions)
		encoded.erase(pos, 1);
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
