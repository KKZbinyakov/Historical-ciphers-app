#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include <algorithm>
#include "vigenere_ciphers.hpp"
#include "doctest.h"

TEST_CASE("Input data incorrect, case Alphabet letter repeat")
{
    CHECK_THROWS_WITH(vigenere_data_is_valid("ABC", "AA", "AABCDEFGHIJKLMOPQRSTUVWXYZ "), "Alphabet letter repeat error");
}

TEST_CASE("Input data incorrect, case Unknown key letter")
{
    CHECK_THROWS_WITH(vigenere_data_is_valid("ABC", "!A", "ABCDEFG"), "Unknown key symbol");
}

TEST_CASE("Input data incorrect, case Unknown text letter")
{
    CHECK_THROWS_WITH(vigenere_data_is_valid("A$C", "AA", "ABCDEFG"), "Unknown text symbol");
}

TEST_CASE("Vigenere shortkey encryption")
{
    CHECK(repeat_key_ciphering("ECONOMICS", "TEN", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "XGBGSZBGF");
}

TEST_CASE("Vigenere shortkey decryption")
{
    CHECK(repeat_key_deciphering("XGBGSZBGF", "TEN", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "ECONOMICS");
}

TEST_CASE("Vigenere selfkey opentext encryption")
{
    CHECK(self_open_key_ciphering("ALPHABET", "MIEM", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "MTTTAMTA");
}

TEST_CASE("Vigenere selfkey opentext decryption")
{
    CHECK(self_open_key_deciphering("MTTTAMTA", "MIEM", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "ALPHABET");
}

TEST_CASE("Vigenere selfkey ciphertext encryption")
{
    CHECK(self_cipher_key_ciphering("VOLENS NOLENS", "CORE", " ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "YCCJLVCX GHKS");
}

TEST_CASE("Vigenere selfkey ciphertext decryption")
{
    CHECK(self_cipher_key_deciphering("YCCJLVCX GHKS", "CORE", " ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "VOLENS NOLENS");
}
/*
TEST_CASE("")
{
    CHECK();
}

TEST_CASE("")
{
    CHECK();
}
*/