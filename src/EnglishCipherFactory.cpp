#include <VigenereCipher.hpp>
#include <AffineCipher.hpp>
#include "EnglishCipherFactory.hpp"

CipherFactoryPtr EnglishCipherFactory::_instance = CipherFactoryPtr {nullptr};

CipherPtr EnglishCipherFactory::createVigenereCipher(const std::string &keyword) {
	return CipherPtr {new VigenereCipher(keyword, "abcdefghijklmnopqrstuvwxyz")};
}

CipherPtr EnglishCipherFactory::createAffineCipher(const std::string &a, const std::string &b) {
	try {
		int ai = std::stoi(a), bi = std::stoi(b);
		return CipherPtr {new AffineCipher(ai, bi, "abcdefghijklmnopqrstuvwxyz")};
	} catch (std::invalid_argument &ex) {
		throw std::invalid_argument("One or more illegal key value.");
	}

}

CipherFactoryPtr EnglishCipherFactory::getInstance() {
	if (!EnglishCipherFactory::_instance)
		EnglishCipherFactory::_instance = CipherFactoryPtr {new EnglishCipherFactory()};
	return EnglishCipherFactory::_instance;
}
