#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>
#include "magma_cipher.hpp"

/**
 * \file magma_cipher.cpp
 *
 * This file contains encryption and decryption functions of all magma cipher types and data validation functions
 *
*/

/**
 * The function checks whether magma simple replacement data is valid
 *
 * \param[in] data is potential input data in the format of a vector of numbers of type uint8
 * \param[in] key is potential input key in the format of a vector of numbers of type uint8
 *
 * \throw input_data_invalid if length of the data contains not integer number of encrypted blocks or if the key not consist of thirty-two eight-bit numbers
*/
void magmaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    if (key.size() != 32) throw input_data_invalid("The key must consist of thirty two eight-bit numbers");
    if (data.size() % 8 != 0) throw input_data_invalid("The data must contain an integer number of encrypted blocks");
}

/**
 * The function checks whether magma simple replacement data is valid
 *
 * \param[in] data is potential input data in the format of a vector of numbers of type uint8
 * \param[in] key is potential input key in the format of a vector of numbers of type uint8
 * \param[in] synchroLink is potential input key analog in the format of a vector of numbers of type uint8
 *
 * \throw input_data_invalid if length of the data contains not integer number of encrypted blocks (contains a number of numbers not exceeding eight)
 * or if the synchroLink not consist of eight eight-bit numbers or if the key not consist of thirty-two eight-bit numbers
*/
void magmaGammaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    if (key.size() != 32) throw input_data_invalid("The key must consist of thirty two eight-bit numbers");
    if (data.size() % 8 != 0) throw input_data_invalid("The data must contain an integer number of encrypted blocks");
    if (synchroLink.size() != 8) throw input_data_invalid("Synchrolink should be same as data block");
}

/**
 * The function performs encryption using a simple replacement algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, thirdly it calls a "encrypt" method of the magma class to enñrypt input data.
 * Handles exceptions relevant to this type of encryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 *
 * \return Encrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    try {
    magmaCipherDataIsValid(data, key);
    std::array<uint8_t, 32> _key;
    for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
    Magma magma(_key);
    return magma.encrypt(data);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

/**
 * The function performs decryption using a simple replacement algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, thirdly it calls a "decrypt" method of the magma class to deñrypt input data.
 * Handles exceptions relevant to this type of encryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 *
 * \return Decrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    try {
    magmaCipherDataIsValid(data, key);
    std::array<uint8_t, 32> _key;
    for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
    Magma magma(_key);
    return magma.decrypt(data);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

/**
 * The function performs encryption using a gamming algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, after that it transforms
 * synchrolink from vector to array. It calls a "gammaAlgorithm" method of the magma class to enñrypt input data.
 * Handles exceptions relevant to this type of encryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 * \param[in] synchroLink is input key analog in the format of a vector of numbers of type uint8. It's length is eight numbers
 *
 * \return Encrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaGammaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    try {
    magmaGammaCipherDataIsValid(data, key, synchroLink);
    std::array<uint8_t, 32> _key;
    for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
    std::array<uint8_t, 8> _synchroLink;
    for (size_t i = 0; i < synchroLink.size(); ++i) _synchroLink[i] = synchroLink[i];
    Magma magma(_key);
    return magma.gammaAlgorithm(data, _synchroLink);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

/**
 * The function performs decryption using a gamming algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, after that it transforms
 * synchrolink from vector to array. It calls a "gammaAlgorithm" method of the magma class to deñrypt input data.
 * Handles exceptions relevant to this type of decryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 * \param[in] synchroLink is input key analog in the format of a vector of numbers of type uint8. It's length is eight numbers
 *
 * \return Decrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaGammaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    try {
    magmaGammaCipherDataIsValid(data, key, synchroLink);
    std::array<uint8_t, 32> _key;
    for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
    std::array<uint8_t, 8> _synchroLink;
    for (size_t i = 0; i < synchroLink.size(); ++i) _synchroLink[i] = synchroLink[i];
    Magma magma(_key);
    return magma.gammaAlgorithm(data, _synchroLink);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

/**
 * The function performs encryption using a feedback gamming algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, after that it transforms
 * synchrolink from vector to array. It calls a "feedbackGammaAlgorithm" method of the magma class to enñrypt input data.
 * Handles exceptions relevant to this type of encryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 * \param[in] synchroLink is input key analog in the format of a vector of numbers of type uint8. It's length is eight numbers
 *
 * \return Encrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaFeedbackGammaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    try {
        magmaGammaCipherDataIsValid(data, key, synchroLink);
        std::array<uint8_t, 32> _key;
        for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
        std::array<uint8_t, 8> _synchroLink;
        for (size_t i = 0; i < synchroLink.size(); ++i) _synchroLink[i] = synchroLink[i];
        Magma magma(_key);
        return magma.feedbackGammaAlgorithm(data, _synchroLink);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

/**
 * The function performs decryption using a feedback gamming algorithm. Firstly it checks validity of input data, secondly it
 * transforms input key data into a class object, before that, by converting the vector to an array, after that it transforms
 * synchrolink from vector to array. It calls a "feedbackGammaAlgorithm" method of the magma class to deñrypt input data.
 * Handles exceptions relevant to this type of decryption
 *
 * \param[in] data is input data in the format of a vector of numbers of type uint8. The length of the vector is a multiple of eight
 * \param[in] key is input key in the format of a vector of numbers of type uint8. The length of the key is thirty-two numbers
 * \param[in] synchroLink is input key analog in the format of a vector of numbers of type uint8. It's length is eight numbers
 *
 * \return Decrypted data, error message, if error occured
*/
std::vector<uint8_t> magmaFeedbackGammaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    try {
        magmaGammaCipherDataIsValid(data, key, synchroLink);
        std::array<uint8_t, 32> _key;
        for (size_t i = 0; i < key.size(); ++i) _key[i] = key[i];
        std::array<uint8_t, 8> _synchroLink;
        for (size_t i = 0; i < synchroLink.size(); ++i) _synchroLink[i] = synchroLink[i];
        Magma magma(_key);
        return magma.feedbackGammaAlgorithm(data, _synchroLink);
    }
    catch(input_data_invalid error) {
        std::cout << error.message;
        return {0};
    }
}

