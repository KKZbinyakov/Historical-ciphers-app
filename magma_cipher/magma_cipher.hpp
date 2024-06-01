#ifndef MAGMA_CIPHER_HPP
#define MAGMA_CIPHER_HPP
#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>

/**
 * \file magma_cipher.hpp
 *
 * This file contains magma class with all methods, exception class, and definition all of functions
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

class Magma {
public:
    static const size_t BLOCK_SIZE = 8;  // 64-bit blocks
    static const size_t KEY_SIZE = 32;   // 256-bit key
    static const size_t NUM_ROUNDS = 32; // Number of rounds

    using Block = std::array<uint8_t, BLOCK_SIZE>;
    using Key = std::array<uint8_t, KEY_SIZE>;

private:
    // Classic S-box table for GOST 28147-89
    std::array<std::array<uint8_t, 16>, 8> sBox = {{
        {0xC, 0x4, 0x6, 0x2, 0xA, 0x5, 0xB, 0x9, 0xE, 0x8, 0xD, 0x7, 0x0, 0x3, 0xF, 0x1},
        {0x6, 0x8, 0x2, 0x3, 0x9, 0xA, 0x5, 0xC, 0x1, 0xE, 0x4, 0x7, 0xB, 0xD, 0x0, 0xF},
        {0xB, 0x3, 0x5, 0x8, 0x2, 0xF, 0xA, 0xD, 0xE, 0x1, 0x7, 0x4, 0xC, 0x9, 0x6, 0x0},
        {0xC, 0x8, 0x2, 0x1, 0xD, 0x4, 0xF, 0x6, 0x7, 0x0, 0xA, 0x5, 0x3, 0xE, 0x9, 0xB},
        {0x7, 0xF, 0x5, 0xA, 0x8, 0x1, 0x6, 0xD, 0x0, 0x9, 0x3, 0xE, 0xB, 0x4, 0x2, 0xC},
        {0x5, 0xD, 0xF, 0x6, 0x9, 0x2, 0xC, 0xA, 0xB, 0x7, 0x8, 0x1, 0x4, 0x3, 0xE, 0x0},
        {0x8, 0xE, 0x2, 0x5, 0x6, 0x9, 0x1, 0xC, 0xF, 0x4, 0xB, 0x0, 0xD, 0xA, 0x3, 0x7},
        {0x1, 0x7, 0xE, 0xD, 0x0, 0x5, 0x8, 0x3, 0x4, 0xF, 0xA, 0x6, 0x9, 0xC, 0xB, 0x2}
    }};

    std::array<uint32_t, 8> keySchedule;
    // Splitting key into eight sub-keys
    void generateKeySchedule(const Key& key) {
        for (size_t i = 0; i < 8; ++i) {
            keySchedule[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | key[4 * i + 3];
        }
    }
    // Mixing according to S-box
    uint32_t f(uint32_t halfBlock, uint32_t roundKey) const {
        uint32_t temp = halfBlock + roundKey;
        uint8_t output[4];
        // Every output element contains two S-blocks
        output[0] = (sBox[0][(temp >> 28) & 0xF] << 4) | sBox[1][(temp >> 24) & 0xF];
        output[1] = (sBox[2][(temp >> 20) & 0xF] << 4) | sBox[3][(temp >> 16) & 0xF];
        output[2] = (sBox[4][(temp >> 12) & 0xF] << 4) | sBox[5][(temp >> 8) & 0xF];
        output[3] = (sBox[6][(temp >> 4) & 0xF] << 4) | sBox[7][(temp >> 0) & 0xF];

        temp = (output[0] << 24) | (output[1] << 16) | (output[2] << 8) | output[3];
        return (temp << 11) | (temp >> (32 - 11)); // left rotation by 11 bits
    }

    Block encryptBlock(const Block& block) const {
        uint32_t left = (block[0] << 24) | (block[1] << 16) | (block[2] << 8) | block[3];
        uint32_t right = (block[4] << 24) | (block[5] << 16) | (block[6] << 8) | block[7];

        for (size_t i = 0; i < NUM_ROUNDS; ++i) {
            uint32_t temp = right;
            right = left ^ f(right, keySchedule[i % 8]);
            left = temp;
        }

        Block encryptedBlock = { static_cast<uint8_t>(right >> 24), static_cast<uint8_t>(right >> 16), static_cast<uint8_t>(right >> 8), static_cast<uint8_t>(right),
                                 static_cast<uint8_t>(left >> 24), static_cast<uint8_t>(left >> 16), static_cast<uint8_t>(left >> 8), static_cast<uint8_t>(left) };
        return encryptedBlock;
    }

    Block decryptBlock(const Block& block) const {
        uint32_t left = (block[0] << 24) | (block[1] << 16) | (block[2] << 8) | block[3];
        uint32_t right = (block[4] << 24) | (block[5] << 16) | (block[6] << 8) | block[7];

        for (size_t i = 0; i < NUM_ROUNDS; ++i) {
            uint32_t temp = right;
            right = left ^ f(right, keySchedule[(NUM_ROUNDS - 1 - i) % 8]);
            left = temp;
        }

        Block decryptedBlock = { static_cast<uint8_t>(right >> 24), static_cast<uint8_t>(right >> 16), static_cast<uint8_t>(right >> 8), static_cast<uint8_t>(right),
                                 static_cast<uint8_t>(left >> 24), static_cast<uint8_t>(left >> 16), static_cast<uint8_t>(left >> 8), static_cast<uint8_t>(left) };
        return decryptedBlock;
    }

    std::vector<uint8_t> gammaBuilding(const Block& synchroLink, size_t dataSize) {
        std::vector<uint8_t> gamma(dataSize);
        Block cipheredLink = encryptBlock(synchroLink);
        uint32_t N1 = (synchroLink[0] << 24) | (synchroLink[1] << 16) | (synchroLink[2] << 8) | synchroLink[3];
        uint32_t N2 = (synchroLink[4] << 24) | (synchroLink[5] << 16) | (synchroLink[6] << 8) | synchroLink[7];
        for (size_t i = 0; i < dataSize - 1; i += 8) {
            uint32_t N3 = N1;
            uint32_t N4 = N2;
            N3 += 0x1010101;
            if (N4 > 0 ^ (0x1010104)) N4 += 0x1010104 + 1;
            else N4 += 0x1010104;

            Block block = { static_cast<uint8_t>(N4 >> 24), static_cast<uint8_t>(N4 >> 16), static_cast<uint8_t>(N4 >> 8), static_cast<uint8_t>(N4),
                                 static_cast<uint8_t>(N3 >> 24), static_cast<uint8_t>(N3 >> 16), static_cast<uint8_t>(N3 >> 8), static_cast<uint8_t>(N3) };
            Block gammaBlock = encryptBlock(block);

            for (int j = 0; j < 8; ++j) {
                gamma[i + j] = gammaBlock[j];
            }
            N1 = N3;
            N2 = N4;
        }
        return gamma;
    }

    std::vector<uint8_t> feedbackGammaBuilding(const Block& synchroLink, const std::vector<uint8_t>& data) {
        size_t dataSize = data.size();
        std::vector<uint8_t> gamma(dataSize);
        uint32_t N1 = (synchroLink[0] << 24) | (synchroLink[1] << 16) | (synchroLink[2] << 8) | synchroLink[3];
        uint32_t N2 = (synchroLink[4] << 24) | (synchroLink[5] << 16) | (synchroLink[6] << 8) | synchroLink[7];
        for (size_t i = 0; i < dataSize - 7; i += 8) {
            Block block = { static_cast<uint8_t>(N1 >> 24), static_cast<uint8_t>(N1 >> 16), static_cast<uint8_t>(N1 >> 8), static_cast<uint8_t>(N1),
                                 static_cast<uint8_t>(N2 >> 24), static_cast<uint8_t>(N2 >> 16), static_cast<uint8_t>(N2 >> 8), static_cast<uint8_t>(N2) };
            Block gammaBlock = encryptBlock(block);
            for (size_t k = 0; k < BLOCK_SIZE; ++k) {
                gamma[i + k] = data[i + k] ^ gammaBlock[k];
            }
            N1 = (gammaBlock[0] << 24) | (gammaBlock[1] << 16) | (gammaBlock[2] << 8) | gammaBlock[3];
            N2 = (gammaBlock[4] << 24) | (gammaBlock[5] << 16) | (gammaBlock[6] << 8) | gammaBlock[7];
        }

        return gamma;
    }


public:
    Magma() = default;

    explicit Magma(const Key& key) {
        setKey(key);
    }

    void setKey(const Key& key) {
        generateKeySchedule(key);
    }
    // Union cutted key into key
    Key getKey() const {
        Key key;
        for (size_t i = 0; i < 8; ++i) {
            key[4 * i] = (keySchedule[i] >> 24) & 0xFF;
            key[4 * i + 1] = (keySchedule[i] >> 16) & 0xFF;
            key[4 * i + 2] = (keySchedule[i] >> 8) & 0xFF;
            key[4 * i + 3] = keySchedule[i] & 0xFF;
        }
        return key;
    }

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data) const {
        size_t dataSize = data.size();
        size_t paddedSize = ((dataSize + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE; // Correction for an incomplete block
        std::vector<uint8_t> paddedData(data); // Augmented text
        paddedData.resize(paddedSize, 0);

        std::vector<uint8_t> encryptedData(paddedSize);

        for (size_t i = 0; i < paddedSize; i += BLOCK_SIZE) {
            Block block;
            std::copy(paddedData.begin() + i, paddedData.begin() + i + BLOCK_SIZE, block.begin());
            Block encryptedBlock = encryptBlock(block);
            std::copy(encryptedBlock.begin(), encryptedBlock.end(), encryptedData.begin() + i);
        }

        return encryptedData;
    }

    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data) const {
        size_t dataSize = data.size();
        std::vector<uint8_t> decryptedData(dataSize);

        for (size_t i = 0; i < dataSize; i += BLOCK_SIZE) {
            Block block;
            std::copy(data.begin() + i, data.begin() + i + BLOCK_SIZE, block.begin());
            Block decryptedBlock = decryptBlock(block);
            std::copy(decryptedBlock.begin(), decryptedBlock.end(), decryptedData.begin() + i);
        }

        return decryptedData;
    }

    std::vector<uint8_t> gammaAlgorithm(const std::vector<uint8_t>& data, const Block& synchroLink) {
        size_t dataSize = data.size();
        std::vector<uint8_t> gamma = gammaBuilding(synchroLink, dataSize);
        std::vector<uint8_t> encryptedData(dataSize);
        for (size_t i = 0; i < std::min(dataSize, gamma.size()); ++i) {
            encryptedData[i] = data[i] ^ gamma[i];
        }
        return encryptedData;
    }

    std::vector<uint8_t> feedbackGammaAlgorithm(const std::vector<uint8_t>& data, const Block& synchroLink) {
        std::vector<uint8_t> gamma = feedbackGammaBuilding(synchroLink, data);
        return gamma;
    }
};

void magmaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
void magmaGammaCipherDataIsValid(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink);
std::vector<uint8_t> magmaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
std::vector<uint8_t> magmaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
std::vector<uint8_t> magmaGammaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink);
std::vector<uint8_t> magmaGammaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink);
std::vector<uint8_t> magmaFeedbackGammaEncrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink);
std::vector<uint8_t> magmaFeedbackGammaDecrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, const std::vector<uint8_t>& synchroLink);

#endif

