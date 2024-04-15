#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Affine_ciphers.hpp"

/**
 * \file Affine_ciphers.cpp
 *
 * This file contains affine ciphers encryption and decryption functions
 *
*/

/**
 * The function checks whether two numbers are mutually prime
 *
 * \param[in] a first number
 * \param[in] b second number
 *
 * \return Boolean true if numbers are mutual simple, boolean false if they don't
 * \throw 0 if some of input data values is not a digit
*/
bool mutual_simple(int a, int b){
    try{
        if (isdigit(a) && isdigit(b) == 0){
            throw 0;
        }
    }
    catch(int s){
        switch(s){
            case 0:
                std::cout << "Only numbers can be mutual simple. Please, try again";
                return 0;
        }
    }
    if (a > b){
        std::swap (a, b);
    }
    while (a * b != 0){
        b = b - a;
        if (a > b){
        std::swap (a, b);
        }
    }
    if (a + b == 1){
        return true;
    }
    else{
        return false;
    }
}

/**
 * The function checks whether replacement cipher data is valid
 *
 * \param[in] text is encrypted or decrypted text
 * \param[in] key is string of mixed alphabet symbols based on the order of which encryption and decryption are taking place
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Boolean true if if input data is valid, boolean false if it don't
 * \throw 0 if the key and the alphabet have different length
 * \throw 1 if alphabet contains two similar symbols
 * \throw 2 if key contains two similar symbols
 * \throw 3 if key contains symbol that not in the alphabet
 * \throw 4 if text contains symbol that not in the alphabet
*/
bool replacement_cipher_data_is_valid(std::string text, std::string key, std::string alphabet){
    try{
        if (key.size() != alphabet.size()){
            throw 0; //Key-alphabet size error
        }
        for (char c : alphabet){
            if (count(alphabet.begin(), alphabet.end(), c) > 1){
                throw 1; //Alphabet letter repeat error
            }
        }
        for (char c : key){
            if (count(key.begin(), key.end(), c) != 1){
                throw 2; //Key letter repeat error
            }
        }
        for (char c : alphabet){
            if (count(key.begin(), key.end(), c) != 1){
                throw 3; //Key symbol unknown
            }
        }

        for (char c : text){
            if (count(alphabet.begin(), alphabet.end(), c) < 1){
                throw 4; //Text symbol unknown
            }
        }
    }
    catch (int s){
        switch (s){
            case 0:
                std::cout << "Key and alphabet should have equal length. Please, try again" << "\n";
                return 0;
            case 1:
                std::cout << "There are similar letters in alphabet. Please, try again" << "\n";
                return 0;
            case 2:
                std::cout << "There is a letter in the key that is not in alphabet. Please, try again" << "\n";
                return 0;
            case 3:
                std::cout << "There is a letter in the key that is not in the alphabet. Please, try again" << "\n";
                return 0;
            case 4:
                std::cout << "There is a letter in the text that is not in alphabet. Please, try again" << "\n";
                return 0;
            default:
                return 1;
        }
    }
    return 1;
}

/**
 * The function checks whether affine cipher data is valid
 *
 * \param[in] text is encrypted or decrypted text
 * \param[in] key is two numbers, using during encryption and decryption
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Boolean true if input data is valid boolean false if it don't
 * \throw 0 if the key and the power of alphabet are not mutual simple
 * \throw 1 if  text contains symbol that not in the alphabet
 * \throw 2 if one or both of the keys are not digits
*/
bool affine_cipher_data_is_valid(std::string text, std::vector <int> key, std::string alphabet){
    int alphabet_power = alphabet.size();
    try{
        if (mutual_simple(key[0], alphabet_power) == 0){
            throw 0; //Mutual simple error
        }
        for (char c : text){
            if (count(alphabet.begin(), alphabet.end(), c) < 1){
                throw 1; //Unknown symbol error
            }
        }
    }
    catch (int s){
        switch (s){
            case 0:
                std::cout << "A-key and alphabet power are not mutual simple. Please, try again" << "\n";
                return 0;
            case 1:
                std::cout << "There is a letter in the text that is not in alphabet. Please, try again" << "\n";
                return 0;
            default:
                return 1;
        }
    }
    return 1;
}

/**
 * The function checks whether reccurent affine cipher data is valid
 *
 * \param[in] text is encrypted or decrypted text
 * \param[in] key is four numbers, using during encryption and decryption
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Boolean true if input data is valid boolean false if it don't
 * \throw 0 if the key and the power of alphabet are not mutual simple
 * \throw 1 if  text contains symbol that not in the alphabet
*/
bool affine_reccurent_cipher_data_is_valid(std::string text, std::vector <int> key, std::string alphabet){
    int alphabet_power = alphabet.size();
    try{
        if ((mutual_simple(key[0], alphabet_power) && mutual_simple(key[1], alphabet_power)) == 0){
            throw 0; //Mutual simple error
        }
        for (char c : text){
            if (count(alphabet.begin(), alphabet.end(), c) < 1){
                throw 1; //Unknown symbol error
            }
        }
    }
    catch (int s){
        switch (s){
            case 0:
                std::cout << "One or both of a-keys and alphabet power are not mutual simple. Please, try again\n";
                return 0;
            case 1:
                std::cout << "There is a letter in the text that is not in alphabet. Please, try again\n";
                return 0;
            default:

                return 1;
        }
    }
    return 1;
}

/**
 * The function is doing simple replacement encryption of the text. The encryption algorithm is as follows:
 * function accepts alphabet and mixed alphabet named key. During encryption we find the position of every text
 * symbol in alphabet and replace every letter with symbol, which is located on the same position in the key
 *
 * \param[in] text is encrypted text
 * \param[in] key is string of mixed alphabet symbols based on the order of which encryption and decryption are taking place
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Encrypted text, nothing if error occured
*/
std::string simple_replacement_encryption(std::string text, std::string key, std::string alphabet){
    if (replacement_cipher_data_is_valid(text, key, alphabet) == 0){
        return 0;
    }
    std::string ciphertext = "";
    for (char c : text){
            ciphertext += key[alphabet.find(c)];
    }
    return ciphertext;
}

/**
 * The function is doing simple replacement decryption of the text. The decryption algorithm is as follows:
 * function accepts alphabet and mixed alphabet named key. During encryption we find the position of every text
 * symbol in key and replace every letter with symbol, which is located on the same position in the alphabet
 *
 * \param[in] text is decrypted text
 * \param[in] key is string of mixed alphabet symbols based on the order of which encryption and decryption are taking place
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Decrypted text, nothing if error occured
*/
std::string simple_replacement_decryption(std::string ciphertext, std::string key, std::string alphabet){
    if (replacement_cipher_data_is_valid(ciphertext, key, alphabet) == 0){
        return 0;
    }
    std::string text = "";
    for (char c : ciphertext){
            text += alphabet[key.find(c)];
    }
    return text;
}

/**
 * The function is doing affine encryption of the text. The encryption algorithm is as follows:
 * function accepts text and two numbers, a-key and b-key. After that we find the position of every text
 * symbol in alphabet, multiply this number by a-key and adding up with b-key. If result is larger then
 * alphabet power we replace result with it's remainder of the division by alphabet power. After that we
 * replace every text symbol with symbol, that is located in the alphabet position, which we found after calculations
 *
 *
 * \param[in] text is encrypted text
 * \param[in] key is pair of integer numbers inside a vector
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Encrypted text, nothing if error occured
*/
std::string affine_encryption(std::string text, std::vector <int> key, std::string alphabet){ // Key look like [a, b]
    if (affine_cipher_data_is_valid(text, key, alphabet) == 0){
        return 0;
    }
    std::string ciphertext = "";
    for (char c : text){
        int index = alphabet.find(c);
        ciphertext += alphabet[(index * key[0] + key[1]) % alphabet.size()];
    }
    return ciphertext;
}

/**
 * The function is doing affine decryption of the text. The encryption algorithm is as follows:
 * function accepts text and two numbers, a-key and b-key. After that we are finding values of reversed a-key for every
 * a-key. The remainder of dividing the product of the key a and the inverse key a by the power of the alphabet must be
 * equal to one. After that we find position of every symbol of the text in alphabet, substract b-key from it and multiply
 * it by inverse key a. After that we replace every text symbol with symbol, that is located in the alphabet position,
 * which we found after calculations
 *
 *
 * \param[in] text is encrypted text
 * \param[in] key is pair of integer numbers inside a vector
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Encrypted text, nothing if error occured
*/
std::string affine_decryption(std::string ciphertext, std::vector <int> key, std::string alphabet){ // Key look like [a, b]
    if (affine_cipher_data_is_valid(ciphertext, key, alphabet) == 0){
        return 0;
    }
    std::string text = "";
    int inverse_alpha = 0;
    int alphabet_power = alphabet.size();
    for (int i = 0; i < alphabet_power; i++){
        if ((key[0] * i) % alphabet_power == 1){
            inverse_alpha = i;
        }
    }
    for (char c : ciphertext){
        int index = alphabet.find(c);
        text += alphabet[(((index - key[1]) * inverse_alpha) % alphabet_power + alphabet_power) % alphabet_power];
    }
    return text;
}

/**
 * The function is doing recurrent affine encryption of the text. The encryption algorithm is as follows:
 * function accepts text and four numbers, two a-keys and two b-keys. After that we are making two vectors of keys,
 * which have the same length as the text. In a-keys vector each subsequent key is a product of the previous two.
 * In b-keys vector each subsequent key is the amount of the previous two.
 * After that we find the position of every text symbol in alphabet, multiply this number by a-key in the appropriate position and adding
 * up with b-key in the appropriate vector position. If result is larger then alphabet power we replace result
 * with it's remainder of the division by alphabet power. After that we
 * replace every text symbol with symbol, that is located in the alphabet position, which we found after calculations
 *
 *
 * \param[in] text is encrypted text
 * \param[in] key is two pairs of integer numbers inside a vector
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Encrypted text, nothing if error occured
*/
std::string affine_reccurent_encryption(std::string text, std::vector <int> key, std::string alphabet){ // Key look like a1, a2, b1, b2
    if (affine_reccurent_cipher_data_is_valid(text, key, alphabet) == 0){
        return 0;
    }
    std::string ciphertext = "";
    int text_size = text.size();
    int alphabet_power = alphabet.size();
    std::vector <int> a_keys{key[0], key[1]};
    std::vector <int> b_keys{key[2], key[3]};
    for (int i{1}; i <= text_size - 2; i++){
        a_keys.push_back((a_keys[i-1] * a_keys[i]) % alphabet_power);
        b_keys.push_back((b_keys[i-1] + b_keys[i]) % alphabet_power);
    }
    for (int i{0}; i < text_size; i++){
        int index = alphabet.find(text[i]);
        ciphertext += alphabet[((index * a_keys[i] + b_keys[i]) % alphabet_power + alphabet_power) % alphabet_power];
    }
    return ciphertext;
}

/**
 * The function is doing affine recurrent decryption of the text. The decryption algorithm is as follows:
 * function accepts text and four numbers, two a-keys and two b-keys.After that we are making two vectors of keys,
 * which have the same length as the text. In a-keys vector each subsequent key is a product of the previous two.
 * In b-keys vector each subsequent key is the amount of the previous two. After that we are finding values of reversed a-key for every
 * a-key. The remainder of dividing the product of the key a and the inverse key a by the power of the alphabet must be
 * equal to one. After that we find position of every symbol of the text in alphabet, substract b-key in the appropriate
 * vector position from it and multiply it by inverse a-key in the appropriate vector position. After that we replace every
 * text symbol with symbol, that is located in the alphabet position, which we found after calculations
 *
 *
 * \param[in] text is decrypted text
 * \param[in] key is two pairs of integer numbers inside a vector
 * \param[in] alphabet is string, that contains all symbols, which can be used in input text
 *
 * \return Encrypted text, nothing if error occured
*/
std::string affine_reccurent_decryption(std::string ciphertext, std::vector <int> key, std::string alphabet){ // Key look like a1, a2, b1, b2
    if (affine_reccurent_cipher_data_is_valid(ciphertext, key, alphabet) == 0){
        return 0;
    }
    std::string text = "";
    int ciphertext_size = ciphertext.size();
    int alphabet_power = alphabet.size();
    std::vector <int> a_keys{key[0], key[1]};
    std::vector <int> b_keys{key[2], key[3]};
    std::vector <int> a_inverse_keys;
    for (int i{1}; i <= ciphertext_size; i++){
        a_keys.push_back((a_keys[i-1] * a_keys[i]) % alphabet_power);
        b_keys.push_back((b_keys[i-1] + b_keys[i]) % alphabet_power);
    }
    for (int n : a_keys){
        for (int i{0}; i < alphabet_power; i++){
            if ((i * n) % alphabet_power == 1){
                a_inverse_keys.push_back(i);
                break;
            }
        }
    }
    for (int i{0}; i < ciphertext_size; i++){
        int index = alphabet.find(ciphertext[i]);
        text += alphabet[(((index - b_keys[i]) * a_inverse_keys[i]) % alphabet_power + alphabet_power) % alphabet_power];
    }
    return text;
}

