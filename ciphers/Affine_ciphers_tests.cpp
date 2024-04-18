#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Affine_ciphers.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


/**
 * \file Affine_ciphers_tests.cpp
 *
 * This file contains affine ciphers testing for errors, ciphering and deciphering results
 *
*/


TEST_CASE("Mutual simple numbers")
{
    CHECK(mutual_simple(13, 19) == 1);
}

TEST_CASE("Not mutual simple numbers")
{
    CHECK(mutual_simple(8, 4) == 0);
}

TEST_CASE("Simple replacement key and and alphabet have not same length")
{
	CHECK_THROWS_WITH(replacement_cipher_data_is_valid("", "ABCDE", "ABCDEF"), "Key and alphabet should have equal length. Please, try again");
}

TEST_CASE("Repeating symbol in alphabet")
{
    CHECK_THROWS_WITH(replacement_cipher_data_is_valid("", "ABCDEF", "ABCDFF"), "Alphabet contains repeating symbol. Please, try again");

}

TEST_CASE("Repeating symbol in key")
{
    CHECK_THROWS_WITH(replacement_cipher_data_is_valid("", "AABCD", "ABCDE"), "Key contains repeating symbol. Please, try again");
}

TEST_CASE("Unknown symbol in the key")
{
    CHECK_THROWS_WITH(replacement_cipher_data_is_valid("", "ABCD$", "ABCDE"), "Key contains symbol, which is not in alphabet. Please, try again");
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK_THROWS_WITH(replacement_cipher_data_is_valid("ABC$E", "EDCAB", "ABCDE"), "Text contains symbol, which is not in alphabet. Please, try again");
}

TEST_CASE("Alphabet power and a-key are not mutual simple")
{
    CHECK_THROWS_WITH(affine_cipher_data_is_valid("ATTACK AT DAWN", {3, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ "), "Alphabet power and a-key should be mutual simple. Please, try again");
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK_THROWS_WITH(affine_cipher_data_is_valid("ATTACK AT DA$N", {7, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ "), "Text contains symbol, which is not in alphabet. Please, try again");
}

TEST_CASE("Alphabet power and a-key are not mutual simple")
{
    CHECK_THROWS_WITH(affine_reccurent_cipher_data_is_valid("ATTACK AT DAWN", {3, 7, 11, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ "), "Alphabet power and a-keys should be mutual simple. Please, try again");
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK_THROWS_WITH(affine_reccurent_cipher_data_is_valid("ATTACK AT DA$N", {7, 11, 19, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ "), "Text contains symbol, which is not in alphabet. Please, try again");
}

TEST_CASE("Simple replacement encryption")
{
    CHECK(simple_replacement_encryption("a lot of people ask me do i know tyler durden", "acegikmoqsuwybdfhjlnprtvxz ", "abcdefghijklmnopqrstuvwxyz ") == "a wdn dk fidfwi alu yi gd q ubdt nxwij gpjgib");
}

TEST_CASE("Simple replacement decryption")
{
    CHECK(simple_replacement_decryption("a wdn dk fidfwi alu yi gd q ubdt nxwij gpjgib", "acegikmoqsuwybdfhjlnprtvxz ", "abcdefghijklmnopqrstuvwxyz ") == "a lot of people ask me do i know tyler durden");
}

TEST_CASE("Affine encryption")
{
    CHECK(affine_encryption("ENCRYPTION", {19, 5}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "DSRQTECBLS");
}

TEST_CASE("Affine decryption")
{
    CHECK(affine_decryption("DSRQTECBLS", {19, 5}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "ENCRYPTION");
}

TEST_CASE("Recurrent affine encryption")
{
    CHECK(affine_reccurent_encryption("recurrence", {3, 7, 11, 13}, "abcdefghijklmnopqrstuvwxyz") == "kponuzhkwn");
}

TEST_CASE("Recurrent affine decryption")
{
    CHECK(affine_reccurent_decryption("kponuzhkwn", {3, 7, 11, 13}, "abcdefghijklmnopqrstuvwxyz") == "recurrence");
}

