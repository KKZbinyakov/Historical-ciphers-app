
/**
 * \file Affine_ciphers.hpp
 *
 * This file contains exception class, and definition all of functions
 *
*/

class exception
{
public:
    exception() noexcept;
    exception(const exception&) noexcept;
    exception& operator=(const exception&) noexcept;
    virtual ~exception();
    virtual const char* what() const noexcept;
};

class input_data_invalid: public std::exception
{
public:
    std::string message;
    input_data_invalid(const std::string& _message){
        message = _message;
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

bool mutual_simple(int a, int b);
void replacement_cipher_data_is_valid(std::string text, std::string key, std::string alphabet);
void affine_cipher_data_is_valid(std::string text, std::vector <int> key, std::string alphabet);
void affine_reccurent_cipher_data_is_valid(std::string text, std::vector <int> key, std::string alphabet);
std::string simple_replacement_encryption(std::string text, std::string key, std::string alphabet);
std::string simple_replacement_decryption(std::string ciphertext, std::string key, std::string alphabet);
std::string affine_encryption(std::string text, std::vector <int> key, std::string alphabet);
std::string affine_decryption(std::string ciphertext, std::vector <int> key, std::string alphabet);
std::string affine_reccurent_encryption(std::string text, std::vector <int> key, std::string alphabet);
std::string affine_reccurent_decryption(std::string ciphertext, std::vector <int> key, std::string alphabet);
