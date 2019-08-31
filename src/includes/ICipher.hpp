#ifndef ICIPHER_HPP
#define ICIPHER_HPP

class ICipher {
public:
	virtual char encrypt(char in, size_t pos) = 0;
	virtual char decrypt(char in, size_t pos) = 0;
	virtual ~ICipher() {};
};

using CipherPtr = std::unique_ptr<ICipher>;

#endif //ICIPHER_HPP
