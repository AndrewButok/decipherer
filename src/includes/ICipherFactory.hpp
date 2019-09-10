#ifndef DECIPHERER_ICIPHERFACTORY_HPP
#define DECIPHERER_ICIPHERFACTORY_HPP

#include <memory>

class ICipherFactory {
public:
    virtual ~ICipherFactory() = default;

    virtual CipherPtr createVigenereCipher(const std::string &keyword) = 0;
    virtual CipherPtr createAffineCipher(const std::string &a, const std::string &b) = 0;
};

using CipherFactoryPtr = std::shared_ptr<ICipherFactory>;

#endif //DECIPHERER_ICIPHERFACTORY_HPP
