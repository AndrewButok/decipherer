#include <string>
#include "ICipher.hpp"
#include "StringDecryptor.hpp"

//void StringDecryptor::decrypt_thread(int begin, int thread_count, std::string &encoded) {
//	for (size_t i = begin; i < encoded.size(); i += thread_count) {
//		char c = encoded[i];
//		c = this->_cipher->decrypt(c, i);
//		{
//			std::lock_guard<std::mutex> lockGuard(this->_mutex);
//			this->_buffer.push_back(c);
//		}
//	}
//}
//
//void StringDecryptor::encrypt_thread(int begin, int thread_count, std::string &raw) {
//	for (size_t i = begin; i < raw.size(); i += thread_count) {
//		char c = raw[i];
//		c = this->_cipher->encrypt(c, i);
//		std::this_thread::sleep_for(std::chrono::nanoseconds(50000));
//		{
//			std::lock_guard<std::mutex> lockGuard(this->_mutex);
//			this->_buffer.push_back(c);
//		}
//	}
//}
std::string StringDecryptor::decrypt_thread(std::string encoded, size_t fpos, char (ICipher::*decrypt_fun)(char, size_t)) {
//	std::cout << std::this_thread::get_id() << std::endl;
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
//	return (this->_cipher.get()->*decrypt_fun)(c, pos);
}

void StringDecryptor::decrypt(std::string &encoded, Mode mode) {
//	for (std::string::iterator pos = encoded.begin(); pos != encoded.end(); pos++) {
//		if (!this->_cipher->isAlphabetChar(*pos)) {
//			pos--;
//			encoded.erase(pos + 1);
//		}
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
//	std::vector<std::thread> thread_vector(2);
//	for (int i = 0; i < 2; i++) {
//		if (mode == Mode::Normal)
//			thread_vector[i] = std::thread(&StringDecryptor::decrypt_thread,
//				this, i, 2, std::ref(encoded));
//		else if (mode == Mode::Reversed)
//			thread_vector[i] = std::thread(&StringDecryptor::encrypt_thread,
//				this, i, 2, std::ref(encoded));
//	}
//	for (std::thread &thr: thread_vector)
//		if (thr.joinable())
//			thr.join();
	encoded.clear();
	std::for_each(_buffer.begin(), _buffer.end(), [&encoded](std::future<std::string> &c) {
		encoded += c.get();
	});
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
