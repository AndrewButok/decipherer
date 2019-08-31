//
// Created by Андрій Буток on 8/31/19.
//

#include "FileDecryptor.hpp"

#include <memory>

FileDecryptor::FileDecryptor(std::string inputFilename,
							 std::string outputFilename,
							 CipherPtr cipher) {
	this->inputFileStream = std::ifstream(inputFilename);
	this->outputFileStream = std::ofstream(outputFilename);
	if (!this->inputFileStream.good())
		throw std::invalid_argument("Input file not found.");
	this->decryptor = std::make_unique<StringDecryptor>(std::move(cipher));
}

void FileDecryptor::decrypt(StringDecryptor::Mode mode) {
	auto str_ptr = std::make_unique<std::string>("");
	char buf[1000];
	while (this->inputFileStream.good()) {
		this->inputFileStream.get(buf, 1000);
		str_ptr->append(buf);
		bzero(buf, 1000);
	}
	this->inputFileStream.close();
	this->decryptor->decrypt(*str_ptr, mode);
	this->outputFileStream << *str_ptr;
	this->outputFileStream.close();
}

FileDecryptor::FileDecryptor() {
}

FileDecryptor::FileDecryptor(const FileDecryptor&) {
}

FileDecryptor &FileDecryptor::operator=(const FileDecryptor &) {
	return *this;
}
