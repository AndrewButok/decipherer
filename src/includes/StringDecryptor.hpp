#ifndef DECHIPER_HPP
#define DECHIPER_HPP

#include <memory>
#include <mutex>
#include <vector>
#include <future>
#include "ICipher.hpp"

class StringDecryptor {
public:
	enum class Mode: unsigned char {
		Normal = 0,
		Reversed = 1
	};
private:
	CipherPtr								_cipher;
	std::vector<std::future<std::string>>	_buffer;
	std::mutex								_mutex;

	StringDecryptor();
	StringDecryptor(const StringDecryptor &);
	StringDecryptor &operator=(const StringDecryptor &);

//	void decrypt_thread(int begin, int thread_count, std::string &encoded);
//	void encrypt_thread(int begin, int thread_count, std::string &raw);
	std::string decrypt_thread(std::string encoded, size_t pos, char (ICipher::*decrypt_fun)(char, size_t));
public:
	explicit StringDecryptor(CipherPtr cipher);
	~StringDecryptor();

	void decrypt(std::string &encoded, Mode mode);
};

using StringDecryptorPtr = std::unique_ptr<StringDecryptor>;

#endif //DECHIPER_HPP
