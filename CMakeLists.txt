cmake_minimum_required(VERSION 3.14)
project(decipherer)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/src/includes)
add_executable(decipherer src/main.cpp
        src/StringDecryptor.cpp
        src/AffineCipher.cpp
        src/ACipher.cpp
        src/VigenereCipher.cpp src/FileDecryptor.cpp src/includes/FileDecryptor.hpp src/CipherFactory.cpp src/includes/CipherFactory.hpp)