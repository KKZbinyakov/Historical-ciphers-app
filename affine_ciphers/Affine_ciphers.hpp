#include "exceptions.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/**
 * \file Affine_ciphers.hpp
 *
 * This file contains exception classes, and definition all of functions
 *
 */

bool mutual_simple(int a, int b);
void replacement_cipher_data_is_valid(const std::string &text,
                                      const std::string &key,
                                      const std::string &alphabet);
void affine_cipher_data_is_valid(const std::string &text,
                                 const std::vector<int> &key,
                                 const std::string &alphabet);
void affine_reccurent_cipher_data_is_valid(const std::string &text,
                                           const std::vector<int> &key,
                                           const std::string &alphabet);
std::string simple_replacement_encryption(const std::string &text,
                                          const std::string &key,
                                          const std::string &alphabet);
std::string simple_replacement_decryption(const std::string &ciphertext,
                                          const std::string &key,
                                          const std::string &alphabet);
std::string affine_encryption(const std::string &text,
                              const std::vector<int> &key,
                              const std::string &alphabet);
std::string affine_decryption(const std::string &ciphertext,
                              const std::vector<int> &key,
                              const std::string &alphabet);
std::string affine_reccurent_encryption(const std::string &text,
                                        const std::vector<int> &key,
                                        const std::string &alphabet);
std::string affine_reccurent_decryption(const std::string &ciphertext,
                                        const std::vector<int> &key,
                                        const std::string &alphabet);
