#include <iostream>
#include <string>
#include "EnglishCipherFactory.hpp"
#include "FileDecryptor.hpp"
#include "StringDecryptor.hpp"
#define USAGE R"(usage: ./decipherer input-file output-file cipher[vig/aff/vigr/affr] parameters[vig_key/aff_a_b])"

int main(int argc, char **argv) {
	if ((argc != 5 && argc != 6) ||
		(argc == 6 && (strcmp(argv[3], "vig") == 0 || strcmp(argv[3], "vigr") == 0)) ||
		(argc == 5 && (strcmp(argv[3], "aff") == 0 || strcmp(argv[3], "affr") == 0))) {
		std::cout << USAGE << std::endl;
		return -1;
	}
	std::string cipher_name(argv[3]);
	CipherFactoryPtr cipherFactory = EnglishCipherFactory::getInstance();
	try {
		CipherPtr cipher;
		if (cipher_name == "vig" || cipher_name == "vigr")
			cipher = cipherFactory->createVigenereCipher(argv[4]);
		else if (cipher_name == "aff" || cipher_name == "affr")
			cipher = cipherFactory->createAffineCipher(argv[4], argv[5]);
		else {
			std::cout << "Unknown cipher name." << std::endl;
			return -1;
		}
		StringDecryptor::Mode mode =
				cipher_name.find('r') != std::string::npos ?
				StringDecryptor::Mode::Reversed : StringDecryptor::Mode::Normal;
		FileDecryptorPtr fileDecryptor{
				new FileDecryptor(argv[1], argv[2], std::move(cipher))};
		fileDecryptor->decrypt(mode);
	} catch (std::invalid_argument &ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}