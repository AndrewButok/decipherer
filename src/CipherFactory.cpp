#include <VigenereCipher.hpp>
#include <AffineCipher.hpp>
#include "CipherFactory.hpp"

CipherFactoryPtr CipherFactory::_instance = CipherFactoryPtr {nullptr};

CipherPtr CipherFactory::createCipher(std::string keyword) {
	return CipherPtr {new VigenereCipher(keyword, "abcdefghijklmnopqrstuvwxyz")};
}

CipherPtr CipherFactory::createCipher(int a, int b) {
	return CipherPtr {new AffineCipher(a, b, "abcdefghijklmnopqrstuvwxyz")};
}

CipherFactoryPtr CipherFactory::getInstance() {
	if (!CipherFactory::_instance)
		CipherFactory::_instance =CipherFactoryPtr {new CipherFactory()};
	return CipherFactory::_instance;
}

CipherFactory::CipherFactory() {

}

CipherFactory::CipherFactory(const CipherFactory&){

}

CipherFactory &CipherFactory::operator=(const CipherFactory&){
	return *this;
}

CipherFactory::~CipherFactory() {
}
