#include "FileDecryptor.hpp"

#include <memory>
#include <iomanip>
#include <iostream>

FileDecryptor::FileDecryptor(const std::string &inputFilename,
							 const std::string &outputFilename,
							 CipherPtr cipher) {
	this->inputFileStream = std::ifstream(inputFilename);
	this->outputFileStream = std::ofstream(outputFilename);
	if (!this->inputFileStream.good())
		throw std::invalid_argument("Input file not found.");
	this->decryptor = std::make_unique<StringDecryptor>(std::move(cipher));
}

void FileDecryptor::decrypt(StringDecryptor::Mode mode) {
	std::unique_ptr<std::string> str_ptr = std::make_unique<std::string>("");
	char buf[1000];
	while (this->inputFileStream.good()) {
		this->inputFileStream.get(buf, 1000);
		str_ptr->append(buf);
		bzero(buf, 1000);
	}
	this->inputFileStream.close();
	this->decryptor->decrypt(*str_ptr, mode);
	while (!this->decryptor->ready())
		std::cout << "\r" <<std::setw(6) << std::setprecision(2) << this->decryptor->getProgress() << " % is complete.";
	std::cout << "\rDecryption is complete." << std::endl;
	this->outputFileStream << this->decryptor->getResult();
	this->outputFileStream.close();
}

FileDecryptor::FileDecryptor() {
}

FileDecryptor::FileDecryptor(const FileDecryptor&) {
}

FileDecryptor &FileDecryptor::operator=(const FileDecryptor &) {
	return *this;
}
