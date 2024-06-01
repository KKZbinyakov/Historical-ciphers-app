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
 * \param[in] data
 * \param[in] b second number
 *
 * \return Boolean true if numbers are mutual simple, boolean false if they don't
*/
void magmaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) {
    if (key.size() != 32) throw input_data_invalid("The key must consist of thirty two eight-bit numbers");
    if (data.size() % 8 != 0) throw input_data_invalid("The data must contain an integer number of encrypted blocks");
}

void magmaGammaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink) {
    if (key.size() != 32) throw input_data_invalid("The key must consist of thirty two eight-bit numbers");
    if (data.size() % 8 != 0) throw input_data_invalid("The data must contain an integer number of encrypted blocks");
    if (synchroLink.size() != 8) throw input_data_invalid("Synchrolink should be same as data block");
}

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

