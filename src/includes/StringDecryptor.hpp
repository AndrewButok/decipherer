#ifndef DECHIPER_HPP
#define DECHIPER_HPP

#include <memory>
#include <mutex>
#include "ICipher.hpp"

class StringDecryptor {
private:
	CipherPtr					_cipher;
	std::mutex					_mutex;

	StringDecryptor();
	StringDecryptor(const StringDecryptor &);
	StringDecryptor &operator=(const StringDecryptor &);

	void decrypt_thread(int begin, int thread_count, std::string &encoded);
	void encrypt_thread(int begin, int thread_count, std::string &raw);
public:
	explicit StringDecryptor(CipherPtr cipher);
	~StringDecryptor();

	enum class Mode: unsigned char {
		Normal = 0,
		Reversed = 1
	};
	void decrypt(std::string &encoded, Mode mode);
};

using StringDecryptorPtr = std::unique_ptr<StringDecryptor>;

#endif //DECHIPER_HPP
