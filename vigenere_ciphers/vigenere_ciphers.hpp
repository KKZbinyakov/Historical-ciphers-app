#ifndef VIGENERE_CIPHERS_HPP
#define VIGENERE_CIPHERS_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include "exceptions.hpp"

void vigenere_data_is_valid(const std::string &text, const std::string &key, const std::string &alphabet);
std::string repeat_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string repeat_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);
std::string self_open_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string self_open_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);
std::string self_cipher_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string self_cipher_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);

#endif