#ifndef CIPHERFACTORY_HPP
#define CIPHERFACTORY_HPP

#include <memory>
#include <string>
#include "ICipher.hpp"

class CipherFactory;

using CipherFactoryPtr = std::shared_ptr<CipherFactory>;

class CipherFactory {
private:
	static CipherFactoryPtr _instance;

	CipherFactory() = default;
public:
    CipherFactory(const CipherFactory&) = delete;
    CipherFactory &operator=(const CipherFactory&) = delete;
	static CipherFactoryPtr getInstance();
	virtual ~CipherFactory() = default;

	CipherPtr createCipher(const std::string &keyword);
	CipherPtr createCipher(const std::string &a, const std::string &b);
};



#endif //CIPHERFACTORY_HPP
