#ifndef VIGENERE_CIPHERS_HPP
#define VIGENERE_CIPHERS_HPP

#include <iostream>
#include <string>
#include <algorithm>

class exception
{
public:
    exception() noexcept;
    exception(const exception &) noexcept;
    exception &operator=(const exception &) noexcept;
    virtual ~exception();
    virtual const char *what() const noexcept;
};

class input_data_invalid : public std::exception
{
public:
    std::string message;
    input_data_invalid(const std::string &_message)
    {
        message = _message;
    }
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

void vigenere_data_is_valid(const std::string &text, const std::string &key, const std::string &alphabet);
std::string repeat_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string repeat_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);
std::string self_open_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string self_open_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);
std::string self_cipher_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet);
std::string self_cipher_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet);

#endif