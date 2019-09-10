#include <VigenereCipher.hpp>
#include <AffineCipher.hpp>
#include "CipherFactory.hpp"

CipherFactoryPtr CipherFactory::_instance = CipherFactoryPtr {nullptr};

CipherPtr CipherFactory::createCipher(const std::string &keyword) {
	return CipherPtr {new VigenereCipher(keyword, "abcdefghijklmnopqrstuvwxyz")};
}

CipherPtr CipherFactory::createCipher(const std::string &a, const std::string &b) {
	try {
		int ai = std::stoi(a), bi = std::stoi(b);
		return CipherPtr {new AffineCipher(ai, bi, "abcdefghijklmnopqrstuvwxyz")};
	} catch (std::invalid_argument &ex) {
		throw std::invalid_argument("One or more illegal key value.");
	}

}

CipherFactoryPtr CipherFactory::getInstance() {
	if (!CipherFactory::_instance)
		CipherFactory::_instance = CipherFactoryPtr {new CipherFactory()};
	return CipherFactory::_instance;
}
