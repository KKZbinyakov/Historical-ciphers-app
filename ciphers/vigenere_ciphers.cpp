#include "vigenere_ciphers.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

/**
 * \file vigenere_ciphers.cpp
 * 
 * In that file we describe the functions of 3 types of vigenere cipherings and decipherings, namely short key gamma, self key from opentext and self key from ciphertext, and the validation function for them.
*/



/**
 * The validation function for Vigenere ciphers.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \throw input_data_invalid with the suitable message in case of wrong alphabet, wrong key or wrong text.
*/
void vigenere_data_is_valid(const std::string &text, const std::string &key, const std::string &alphabet)
{
    for (char c : alphabet)
    {
        if (count(alphabet.begin(), alphabet.end(), c) > 1)
        {
            throw input_data_invalid("Alphabet letter repeat error");
        }
    }
    for (char c : key)
    {
        if (count(alphabet.begin(), alphabet.end(), c) < 1)
        {
            throw input_data_invalid("Unknown key symbol");
        }
    }
    long long coun{0};
    for (char c : alphabet)
    {
        coun += count(text.begin(), text.end(), c);
    }
    if (coun < text.size())
    {
        throw input_data_invalid("Unknown text symbol");
    }
}

/**
 * The function of Vigenere ciphering with gamma formed with repeating short key.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string repeat_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet)
{
    try{
        vigenere_data_is_valid(text, key, alphabet);
        std::string cipher{""};
        long long len_alph{alphabet.size()};
        for (int i = 0; i < text.size(); i++)
        {
            int point = std::find(alphabet.begin(), alphabet.end(), text[i]) - alphabet.begin();
            int gam = std::find(alphabet.begin(), alphabet.end(), key[i % key.size()]) - alphabet.begin();
            cipher += alphabet[(point + gam) % len_alph];
        }
        return cipher;

    }
    catch (input_data_invalid error)
    {
        return error.message;
    }   
}


/**
 * The function of Vigenere ciphering with gamma formed with repeating short key.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string repeat_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet)
{
    try
    {
        vigenere_data_is_valid(ciphertext, key, alphabet);
        std::string decipher{""};
        long long len_alph{alphabet.size()};
        for (int i = 0; i < ciphertext.size(); i++)
        {
            int point = std::find(alphabet.begin(), alphabet.end(), ciphertext[i]) - alphabet.begin();
            int gam = std::find(alphabet.begin(), alphabet.end(), key[i % (key.size())]) - alphabet.begin();
            decipher += alphabet[((point - gam) % len_alph + len_alph) % len_alph];
        }
        return decipher;
    }
    catch(input_data_invalid error)
    {
        return error.message;
    }
}


/**
 * The function of Vigenere ciphering with gamma formed with selfkey from opentext.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string self_open_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet)
{
    try
    {
        vigenere_data_is_valid(text, key, alphabet);
        std::string cipher{""};
        unsigned long long len_alph{alphabet.size()};
        std::string gam = key + text;
        for (int i = 0; i < text.size(); i++)
        {
            int first_point = std::find(alphabet.begin(), alphabet.end(), text[i]) - alphabet.begin();
            int sec_point = std::find(alphabet.begin(), alphabet.end(), gam[i]) - alphabet.begin();
            cipher += alphabet[(first_point + sec_point) % len_alph];
        }
        return cipher;
    }
    catch(input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * The function of Vigenere deciphering with gamma formed with selfkey from with opentext.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string self_open_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet)
{
    try
    {
        vigenere_data_is_valid(ciphertext, key, alphabet);
        std::string decipher{""};
        long long len_alph{alphabet.size()};
        std::string gam = key;
        for (int i = 0; i < ciphertext.size(); i++)
        {
            int first_point = std::find(alphabet.begin(), alphabet.end(), ciphertext[i]) - alphabet.begin();
            int sec_point = std::find(alphabet.begin(), alphabet.end(), gam[i]) - alphabet.begin();
            decipher += alphabet[((first_point - sec_point) % len_alph + len_alph) % len_alph];
            gam += alphabet[((first_point - sec_point) % len_alph + len_alph) % len_alph];
        }
        return decipher;
    }
    catch(input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * The function of Vigenere ciphering with gamma formed with selfkey from with ciphertext.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string self_cipher_key_ciphering(const std::string &text, const std::string &key, const std::string &alphabet)
{
    try
    {
        vigenere_data_is_valid(text, key, alphabet);
        std::string cipher{""};
        unsigned long long len_alph{alphabet.size()};
        std::string gam = key;
        for (int i = 0; i < text.size(); i++)
        {
            int first_point = std::find(alphabet.begin(), alphabet.end(), text[i]) - alphabet.begin();
            int sec_point = std::find(alphabet.begin(), alphabet.end(), gam[i]) - alphabet.begin();
            cipher += alphabet[(first_point + sec_point) % len_alph];
            gam += alphabet[(first_point + sec_point) % len_alph];
        }
        return cipher;
    }
    catch(input_data_invalid error)
    {
        return error.message;
    }
}

/**
 * The function of Vigenere deciphering with gamma formed with selfkey from the ciphertext.
 * 
 * \param[in] text The text we want to encrypt or decrypt with some of Vigenere ciphers.
 * \param[in] key The key for Vigenere ciphering.
 * \param[in] alphabet The alphabet of Vigenere ciphering.
 * 
 * \return ciphertext for that input data if data is correct.
 * \return error message if data is incorrect.
*/
std::string self_cipher_key_deciphering(const std::string &ciphertext, const std::string &key, const std::string &alphabet)
{
    try
    {
        vigenere_data_is_valid(ciphertext, key, alphabet);
        std::string decipher{""};
        long long len_alph{alphabet.size()};
        std::string gam = key + ciphertext;
        for (int i = 0; i < ciphertext.size(); i++)
        {
            int first_point = std::find(alphabet.begin(), alphabet.end(), ciphertext[i]) - alphabet.begin();
            int sec_point = std::find(alphabet.begin(), alphabet.end(), gam[i]) - alphabet.begin();
            decipher += alphabet[(first_point - sec_point + len_alph) % len_alph];
        }
        return decipher;
    }
    catch(input_data_invalid error)
    {
        return error.message;
    }
}
