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

	CipherFactory();
	CipherFactory(const CipherFactory&);
	CipherFactory &operator=(const CipherFactory&);
public:
	static CipherFactoryPtr getInstance();
	virtual ~CipherFactory();

	CipherPtr createCipher(std::string keyword);
	CipherPtr createCipher(int a, int b);
};

#endif //CIPHERFACTORY_HPP
