#ifndef FILEDECRYPTOR_HPP
#define FILEDECRYPTOR_HPP

#include <fstream>
#include "StringDecryptor.hpp"

class FileDecryptor {
private:
	std::ifstream			inputFileStream;
	std::ofstream			outputFileStream;
	StringDecryptorPtr		decryptor;
	

public:
    FileDecryptor() = delete;
    FileDecryptor(const FileDecryptor&) = delete;
    FileDecryptor &operator=(const FileDecryptor&) = delete;
	FileDecryptor(const std::string &inputFilename, const std::string &outputFilename, CipherPtr decryptor);

	void decrypt(StringDecryptor::Mode mode);
};

using FileDecryptorPtr = std::unique_ptr<FileDecryptor>;

#endif //FILEDECRYPTOR_HPP
