#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


/**
 * \file Affine_ciphers.hpp
 *
 * This file contains exception classes, and definition all of functions
 *
 */

/**
 *  \class exception is basic exception class created to inherit other exception classes from it
 *
 */
class exception
{
public:
    exception() noexcept;
    exception(const exception &) noexcept;
    exception &operator=(const exception &) noexcept;
    virtual ~exception();
    virtual const char *what() const noexcept;
};

/**
 * \class input_data_invalid is exception class to process exceptions caused by invalid input data
 *
 *
 */
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

bool mutual_simple(int a, int b);
void replacement_cipher_data_is_valid(const std::string &text, const std::string &key, const std::string &alphabet);
void affine_cipher_data_is_valid(const std::string &text, const std::vector<int> &key, const std::string &alphabet);
void affine_reccurent_cipher_data_is_valid(const std::string &text, const std::vector<int> &key, const std::string &alphabet);
std::string simple_replacement_encryption(const std::string &text, const std::string &key, const std::string &alphabet);
std::string simple_replacement_decryption(const std::string &ciphertext, const std::string &key, const std::string &alphabet);
std::string affine_encryption(const std::string &text, const std::vector<int> &key, const std::string &alphabet);
std::string affine_decryption(const std::string &ciphertext, const std::vector<int> &key, const std::string &alphabet);
std::string affine_reccurent_encryption(const std::string &text, const std::vector<int> &key, const std::string &alphabet);
std::string affine_reccurent_decryption(const std::string &ciphertext, const std::vector<int> &key, const std::string &alphabet);
