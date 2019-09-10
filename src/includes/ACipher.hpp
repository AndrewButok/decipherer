#ifndef ACIPHER_HPP
#define ACIPHER_HPP

#include <string>
#include "ICipher.hpp"

class ACipher: public ICipher {
protected:
	std::string _alphabet;

	static bool _isAlphabetValid(const std::string &alphabet);

	ACipher &operator=(const ACipher &);
	explicit ACipher(std::string alphabet);
public:
    ACipher() = delete;
    ACipher(const ACipher&) = delete;

	virtual bool isAlphabetChar(char ch) override;
	virtual ~ACipher() override;
};


#endif //ACIPHER_HPP
