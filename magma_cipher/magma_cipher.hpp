#ifndef MAGMA_CIPHER_HPP
#define MAGMA_CIPHER_HPP
#include "exceptions.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

/**
 * \file magma_cipher.hpp
 *
 * This file contains magma class with all methods and
 * definition all of functions
 *
 */

/**
 * A class which contains parameters of magma cipher algorithm, classic S-box
 * replacement table, encryption and decryption functions, and auxiliary
 * functions for them
 *
 */
class Magma {
public:
  static const size_t BLOCK_SIZE =
      8; ///< BLOCK_SIZE is the size of the block into which the data was split
         ///< for processing
  static const size_t KEY_SIZE =
      32; ///< KEY_SIZE is the size of the key using for encryption
  static const size_t NUM_ROUNDS =
      32; ///< NUM_ROUNDS is the number of encryption rounds accepted in this
          ///< algorithm

  using Block =
      std::array<uint8_t, BLOCK_SIZE>; ///< Block is class object alias for
                                       ///< array of uint8 numbers
  using Key = std::array<uint8_t, KEY_SIZE>; ///< Key is class object alias for
                                             ///< array of uint8 numbers

private:
  // Classic S-box table for GOST 28147-89
  std::array<std::array<uint8_t, 16>, 8> sBox = {
      {{0xC, 0x4, 0x6, 0x2, 0xA, 0x5, 0xB, 0x9, 0xE, 0x8, 0xD, 0x7, 0x0, 0x3,
        0xF, 0x1},
       {0x6, 0x8, 0x2, 0x3, 0x9, 0xA, 0x5, 0xC, 0x1, 0xE, 0x4, 0x7, 0xB, 0xD,
        0x0, 0xF},
       {0xB, 0x3, 0x5, 0x8, 0x2, 0xF, 0xA, 0xD, 0xE, 0x1, 0x7, 0x4, 0xC, 0x9,
        0x6, 0x0},
       {0xC, 0x8, 0x2, 0x1, 0xD, 0x4, 0xF, 0x6, 0x7, 0x0, 0xA, 0x5, 0x3, 0xE,
        0x9, 0xB},
       {0x7, 0xF, 0x5, 0xA, 0x8, 0x1, 0x6, 0xD, 0x0, 0x9, 0x3, 0xE, 0xB, 0x4,
        0x2, 0xC},
       {0x5, 0xD, 0xF, 0x6, 0x9, 0x2, 0xC, 0xA, 0xB, 0x7, 0x8, 0x1, 0x4, 0x3,
        0xE, 0x0},
       {0x8, 0xE, 0x2, 0x5, 0x6, 0x9, 0x1, 0xC, 0xF, 0x4, 0xB, 0x0, 0xD, 0xA,
        0x3, 0x7},
       {0x1, 0x7, 0xE, 0xD, 0x0, 0x5, 0x8, 0x3, 0x4, 0xF, 0xA, 0x6, 0x9, 0xC,
        0xB, 0x2}}}; ///< sBox is the substitution table selected for our cipher

  std::array<uint32_t, 8> keySchedule; ///< representation of the key in the
                                       ///< form of array of eight numbers uint8

  /**
   * The method performs splitting key into eight sub-keys for more convenient
   * submission of it to the input of subsequent algorithms
   *
   * \param[in] Key is not-splitted key
   *
   */
  void generateKeySchedule(const Key &key) {
    for (size_t i = 0; i < 8; ++i) {
      keySchedule[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) |
                       (key[4 * i + 2] << 8) | key[4 * i + 3];
    }
  }

  /**
   * The method performs transformation of a half-block using the part of the
   * key and mixing it according to generally accepted S-box. After that eleven
   * bit left shift is being made
   *
   * \param[in] halfBlock is half of a block of encrypted or decrypted data. It
   * consists of four uint8 numbers and it is submitted to the input in uint32
   * format \param[in] roundKey is a part of the key which is used in this round
   * of encryption. It consists of four uint8 numbers and it is submitted to the
   * input in uint32 format
   *
   * \return part of data after mixing and transformation
   *
   */
  uint32_t f(uint32_t halfBlock, uint32_t roundKey) const {
    uint32_t temp = halfBlock + roundKey;
    uint8_t output[4];
    // Every output element contains two S-blocks
    output[0] =
        (sBox[0][(temp >> 28) & 0xF] << 4) | sBox[1][(temp >> 24) & 0xF];
    output[1] =
        (sBox[2][(temp >> 20) & 0xF] << 4) | sBox[3][(temp >> 16) & 0xF];
    output[2] = (sBox[4][(temp >> 12) & 0xF] << 4) | sBox[5][(temp >> 8) & 0xF];
    output[3] = (sBox[6][(temp >> 4) & 0xF] << 4) | sBox[7][(temp >> 0) & 0xF];

    temp = (output[0] << 24) | (output[1] << 16) | (output[2] << 8) | output[3];
    return (temp << 11) | (temp >> (32 - 11)); // left rotation by 11 bits
  }

  /**
   * The method performs encryption of one block using magma algorithm and
   * calling f function
   *
   * \param[in] block is block for encryption in format of Block
   *
   * \return block after encryption in format of Block
   */
  Block encryptBlock(const Block &block) const {
    uint32_t left =
        (block[0] << 24) | (block[1] << 16) | (block[2] << 8) | block[3];
    uint32_t right =
        (block[4] << 24) | (block[5] << 16) | (block[6] << 8) | block[7];

    for (size_t i = 0; i < NUM_ROUNDS; ++i) {
      uint32_t temp = right;
      right = left ^ f(right, keySchedule[i % 8]);
      left = temp;
    }

    Block encryptedBlock = {
        static_cast<uint8_t>(right >> 24), static_cast<uint8_t>(right >> 16),
        static_cast<uint8_t>(right >> 8),  static_cast<uint8_t>(right),
        static_cast<uint8_t>(left >> 24),  static_cast<uint8_t>(left >> 16),
        static_cast<uint8_t>(left >> 8),   static_cast<uint8_t>(left)};
    return encryptedBlock;
  }

  /**
   * The method performs decryption of one block using magma algorithm and
   * calling f function
   *
   * \param[in] block is block for decryption, eight uint8 numbers in array
   *
   * \return block after decryption
   */
  Block decryptBlock(const Block &block) const {
    uint32_t left =
        (block[0] << 24) | (block[1] << 16) | (block[2] << 8) | block[3];
    uint32_t right =
        (block[4] << 24) | (block[5] << 16) | (block[6] << 8) | block[7];

    for (size_t i = 0; i < NUM_ROUNDS; ++i) {
      uint32_t temp = right;
      right = left ^ f(right, keySchedule[(NUM_ROUNDS - 1 - i) % 8]);
      left = temp;
    }

    Block decryptedBlock = {
        static_cast<uint8_t>(right >> 24), static_cast<uint8_t>(right >> 16),
        static_cast<uint8_t>(right >> 8),  static_cast<uint8_t>(right),
        static_cast<uint8_t>(left >> 24),  static_cast<uint8_t>(left >> 16),
        static_cast<uint8_t>(left >> 8),   static_cast<uint8_t>(left)};
    return decryptedBlock;
  }

  /**
   * The method performs building of gamma according to synchrolink
   *
   * \param[in] block is block for decryption, eight uint8 numbers in array
   *
   * \param[in] dataSize is integer length of encrypted data in bits
   *
   * \return builded gamma
   *
   */
  std::vector<uint8_t> gammaBuilding(const Block &synchroLink,
                                     size_t dataSize) {
    std::vector<uint8_t> gamma(dataSize);
    Block cipheredLink = encryptBlock(synchroLink);
    uint32_t N1 = (synchroLink[0] << 24) | (synchroLink[1] << 16) |
                  (synchroLink[2] << 8) | synchroLink[3];
    uint32_t N2 = (synchroLink[4] << 24) | (synchroLink[5] << 16) |
                  (synchroLink[6] << 8) | synchroLink[7];
    for (size_t i = 0; i < dataSize - 1; i += 8) {
      uint32_t N3 = N1;
      uint32_t N4 = N2;
      N3 += 0x1010101;
      if (N4 > 0 ^ (0x1010104))
        N4 += 0x1010104 + 1;
      else
        N4 += 0x1010104;

      Block block = {
          static_cast<uint8_t>(N4 >> 24), static_cast<uint8_t>(N4 >> 16),
          static_cast<uint8_t>(N4 >> 8),  static_cast<uint8_t>(N4),
          static_cast<uint8_t>(N3 >> 24), static_cast<uint8_t>(N3 >> 16),
          static_cast<uint8_t>(N3 >> 8),  static_cast<uint8_t>(N3)};
      Block gammaBlock = encryptBlock(block);

      for (int j = 0; j < 8; ++j) {
        gamma[i + j] = gammaBlock[j];
      }
      N1 = N3;
      N2 = N4;
    }
    return gamma;
  }

  /**
   * The method performs building of gamma using feedback algorithm according to
   * data for encryption and synchrolink
   *
   * \param[in] block for decryption, eight uint8 numbers in array
   *
   * \param[in] data for encryption, vector of uint8 numbers
   *
   * \return builded gamma
   *
   */
  std::vector<uint8_t> feedbackGammaBuilding(const Block &synchroLink,
                                             const std::vector<uint8_t> &data) {
    size_t dataSize = data.size();
    std::vector<uint8_t> gamma(dataSize);
    uint32_t N1 = (synchroLink[0] << 24) | (synchroLink[1] << 16) |
                  (synchroLink[2] << 8) | synchroLink[3];
    uint32_t N2 = (synchroLink[4] << 24) | (synchroLink[5] << 16) |
                  (synchroLink[6] << 8) | synchroLink[7];
    for (size_t i = 0; i < dataSize - 7; i += 8) {
      Block block = {
          static_cast<uint8_t>(N1 >> 24), static_cast<uint8_t>(N1 >> 16),
          static_cast<uint8_t>(N1 >> 8),  static_cast<uint8_t>(N1),
          static_cast<uint8_t>(N2 >> 24), static_cast<uint8_t>(N2 >> 16),
          static_cast<uint8_t>(N2 >> 8),  static_cast<uint8_t>(N2)};
      Block gammaBlock = encryptBlock(block);
      for (size_t k = 0; k < BLOCK_SIZE; ++k) {
        gamma[i + k] = data[i + k] ^ gammaBlock[k];
      }
      N1 = (gammaBlock[0] << 24) | (gammaBlock[1] << 16) |
           (gammaBlock[2] << 8) | gammaBlock[3];
      N2 = (gammaBlock[4] << 24) | (gammaBlock[5] << 16) |
           (gammaBlock[6] << 8) | gammaBlock[7];
    }

    return gamma;
  }

public:
  Magma() = default;

  /**
   * Constructor of Magma object
   *
   * \param[in] key for encryption
   *
   */
  explicit Magma(const Key &key) { setKey(key); }

  /**
   * The method performs splitting key into eight sub-keys
   *
   * \param[in] key for splitting
   *
   */
  void setKey(const Key &key) { generateKeySchedule(key); }

  /**
   * The method performs union key from eight sub-keys
   *
   * \param[in] key for union
   *
   */
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

  /**
   * The method performs data encryption using magma simple replacement
   * algorithm. Every block is only processed using the f function
   *
   * \param[in] data for encryption
   *
   * \return encrypted data
   *
   */
  std::vector<uint8_t> encrypt(const std::vector<uint8_t> &data) const {
    size_t dataSize = data.size();
    size_t paddedSize = ((dataSize + BLOCK_SIZE - 1) / BLOCK_SIZE) *
                        BLOCK_SIZE;        // Correction for an incomplete block
    std::vector<uint8_t> paddedData(data); // Augmented text
    paddedData.resize(paddedSize, 0);

    std::vector<uint8_t> encryptedData(paddedSize);

    for (size_t i = 0; i < paddedSize; i += BLOCK_SIZE) {
      Block block;
      std::copy(paddedData.begin() + i, paddedData.begin() + i + BLOCK_SIZE,
                block.begin());
      Block encryptedBlock = encryptBlock(block);
      std::copy(encryptedBlock.begin(), encryptedBlock.end(),
                encryptedData.begin() + i);
    }

    return encryptedData;
  }

  /**
   * The method performs data decryption using magma simple replacement
   * algorithm. Every block is only processed using the f function
   *
   * \param[in] data for decryption
   *
   * \return decrypted data
   *
   */
  std::vector<uint8_t> decrypt(const std::vector<uint8_t> &data) const {
    size_t dataSize = data.size();
    std::vector<uint8_t> decryptedData(dataSize);

    for (size_t i = 0; i < dataSize; i += BLOCK_SIZE) {
      Block block;
      std::copy(data.begin() + i, data.begin() + i + BLOCK_SIZE, block.begin());
      Block decryptedBlock = decryptBlock(block);
      std::copy(decryptedBlock.begin(), decryptedBlock.end(),
                decryptedData.begin() + i);
    }

    return decryptedData;
  }

  /**
   * The method performs data encryption and decryption using magma gamming
   * replacement algorithm. Addition modulo two is applied between each block of
   * data and pre-calculated gamma
   *
   * \param[in] data for encryption
   * \param[in] input key analog in the format of a vector of numbers of type
   * uint8
   *
   * \return encrypted data
   *
   */
  std::vector<uint8_t> gammaAlgorithm(const std::vector<uint8_t> &data,
                                      const Block &synchroLink) {
    size_t dataSize = data.size();
    std::vector<uint8_t> gamma = gammaBuilding(synchroLink, dataSize);
    std::vector<uint8_t> encryptedData(dataSize);
    for (size_t i = 0; i < std::min(dataSize, gamma.size()); ++i) {
      encryptedData[i] = data[i] ^ gamma[i];
    }
    return encryptedData;
  }

  /**
   * The method performs data encryption and decryption using magma feedback
   * gamming replacement algorithm. Addition modulo two is applied between each
   * block of data and pre-calculated gamma
   *
   * \param[in] data for encryption
   * \param[in] input key analog in the format of a vector of numbers of type
   * uint8
   *
   * \return encrypted data
   *
   */
  std::vector<uint8_t> feedbackGammaAlgorithm(const std::vector<uint8_t> &data,
                                              const Block &synchroLink) {
    std::vector<uint8_t> gamma = feedbackGammaBuilding(synchroLink, data);
    return gamma;
  }
};

void magmaCipherDataIsValid(const std::vector<uint8_t> &data,
                            const std::vector<uint8_t> &key);
void magmaGammaCipherDataIsValid(const std::vector<uint8_t> &data,
                                 const std::vector<uint8_t> &key,
                                 const std::vector<uint8_t> &synchroLink);
std::vector<uint8_t> magmaEncrypt(const std::vector<uint8_t> &data,
                                  const std::vector<uint8_t> &key);
std::vector<uint8_t> magmaDecrypt(const std::vector<uint8_t> &data,
                                  const std::vector<uint8_t> &key);
std::vector<uint8_t> magmaGammaEncrypt(const std::vector<uint8_t> &data,
                                       const std::vector<uint8_t> &key,
                                       const std::vector<uint8_t> &synchroLink);
std::vector<uint8_t> magmaGammaDecrypt(const std::vector<uint8_t> &data,
                                       const std::vector<uint8_t> &key,
                                       const std::vector<uint8_t> &synchroLink);
std::vector<uint8_t>
magmaFeedbackGammaEncrypt(const std::vector<uint8_t> &data,
                          const std::vector<uint8_t> &key,
                          const std::vector<uint8_t> &synchroLink);
std::vector<uint8_t>
magmaFeedbackGammaDecrypt(const std::vector<uint8_t> &data,
                          const std::vector<uint8_t> &key,
                          const std::vector<uint8_t> &synchroLink);

#endif
