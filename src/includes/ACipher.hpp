#ifndef ACIPHER_HPP
#define ACIPHER_HPP

#include <string>
#include "ICipher.hpp"

class ACipher: public ICipher {
protected:
	std::string _alphabet;

	static bool _isAlphabetValid(const std::string &alphabet);

	ACipher();
	ACipher(const ACipher&);
	ACipher &operator=(const ACipher &);
	explicit ACipher(std::string alphabet);
public:

	~ACipher() override;
};


#endif //ACIPHER_HPP
