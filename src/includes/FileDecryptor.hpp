#ifndef FILEDECRYPTOR_HPP
#define FILEDECRYPTOR_HPP

#include <fstream>
#include "StringDecryptor.hpp"

class FileDecryptor {
private:
	std::ifstream			inputFileStream;
	std::ofstream			outputFileStream;
	StringDecryptorPtr		decryptor;
	
	FileDecryptor();
	FileDecryptor(const FileDecryptor&);
	FileDecryptor &operator=(const FileDecryptor&);
public:
	FileDecryptor(std::string inputFilename, std::string outputFilename, CipherPtr decryptor);

	void decrypt(StringDecryptor::Mode mode);
};

using FileDecryptorPtr = std::unique_ptr<FileDecryptor>;

#endif //FILEDECRYPTOR_HPP
