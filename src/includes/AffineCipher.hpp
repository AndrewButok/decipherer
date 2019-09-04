#ifndef AFFINECIPHER_HPP
#define AFFINECIPHER_HPP

#include <cstddef>
#include <string>
#include "ACipher.hpp"

class AffineCipher: public ACipher {
private:
	int			_a;
	int			_b;

	AffineCipher();
	static bool isCoprime(int a, int b);
public:
	AffineCipher(int a, int b, std::string alphabet);
	AffineCipher(const AffineCipher&);
	AffineCipher &operator=(const AffineCipher&);
	virtual ~AffineCipher() override;

	virtual char encrypt(char in, size_t pos) override;
	virtual char decrypt(char in, size_t pos) override;
};


#endif //AFFINECIPHER_HPP
