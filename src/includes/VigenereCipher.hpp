#ifndef VIGENERECIPHER_HPP
#define VIGENERECIPHER_HPP

#include <vector>
#include "ACipher.hpp"

class VigenereCipher: public ACipher {
private:
	std::vector<long> _shifts;

	static void checkKey(const std::string &key, const std::string &alphabet);
	VigenereCipher();
public:
	VigenereCipher(const std::string &key, std::string alphabet, const std::string &key_alphabet="");
	VigenereCipher(const VigenereCipher &);
	VigenereCipher &operator=(const VigenereCipher&);
	~VigenereCipher() override;

	char encrypt(char in, size_t pos) override;

	char decrypt(char in, size_t pos) override;
};


#endif //VIGENERECIPHER_HPP
