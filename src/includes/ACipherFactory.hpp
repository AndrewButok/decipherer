#ifndef DECIPHERER_ACIPHERFACTORY_HPP
#define DECIPHERER_ACIPHERFACTORY_HPP

#include <memory>

class ACipherFactory {
public:
    ACipherFactory() = default;
    ACipherFactory(const ACipherFactory&) = delete;
    ACipherFactory &operator=(const ACipherFactory&) = delete;
    virtual ~ACipherFactory() = default;

    virtual CipherPtr createVigenereCipher(const std::string &keyword) = 0;
    virtual CipherPtr createAffineCipher(const std::string &a, const std::string &b) = 0;
};

using CipherFactoryPtr = std::shared_ptr<ACipherFactory>;

#endif //DECIPHERER_ACIPHERFACTORY_HPP
