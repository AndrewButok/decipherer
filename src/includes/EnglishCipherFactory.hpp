#ifndef CIPHERFACTORY_HPP
#define CIPHERFACTORY_HPP

#include <string>
#include "ICipher.hpp"
#include "ICipherFactory.hpp"

class EnglishCipherFactory: public ICipherFactory {
private:
	static CipherFactoryPtr _instance;

	EnglishCipherFactory() = default;
public:
    EnglishCipherFactory(const ICipherFactory&) = delete;
    EnglishCipherFactory &operator=(const EnglishCipherFactory&) = delete;
	static CipherFactoryPtr getInstance();
	virtual ~EnglishCipherFactory() override = default;

	virtual CipherPtr createVigenereCipher(const std::string &keyword) override ;
	virtual CipherPtr createAffineCipher(const std::string &a, const std::string &b) override ;
};



#endif //CIPHERFACTORY_HPP
