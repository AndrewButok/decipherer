#ifndef STRINGDECHIPER_HPP
#define STRINGDECHIPER_HPP

#include <memory>
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
	std::mutex								_m_chars;
	size_t									_charsProcessed;
	size_t									_taskSize;

	std::string decrypt_thread(std::string encoded, size_t pos, char (ICipher::*decrypt_fun)(char, size_t));
public:
    StringDecryptor() = delete;
    StringDecryptor(const StringDecryptor &) = delete;
    StringDecryptor &operator=(const StringDecryptor &) = delete;
	explicit StringDecryptor(CipherPtr cipher);
	~StringDecryptor();

	void decrypt(const std::string &encoded, Mode mode);
	std::string getResult();
	bool ready();
	double getProgress();
};

using StringDecryptorPtr = std::unique_ptr<StringDecryptor>;

#endif //STRINGDECHIPER_HPP
