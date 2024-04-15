#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Affine_ciphers.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
	CHECK(replacement_cipher_data_is_valid("", "ABCDE", "ABCDEF") == 0);
}

TEST_CASE("Repeating symbol in alphabet")
{
    CHECK(replacement_cipher_data_is_valid("", "ABCDE", "AABCD") == 0);
}

TEST_CASE("Repeating symbol in key")
{
    CHECK(replacement_cipher_data_is_valid("", "AABCD", "ABCDE") == 0);
}

TEST_CASE("Unknown symbol in the key")
{
    CHECK(replacement_cipher_data_is_valid("", "ABCD$", "ABCDE") == 0);
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK(replacement_cipher_data_is_valid("ABC$E", "EDCAB", "ABCDE") == 0);
}

TEST_CASE("Replacement cipher data is valid")
{
    CHECK(replacement_cipher_data_is_valid("CDEAB", "EDCAB", "ABCDE") == 1);
}

TEST_CASE("Alphabet power and a-key are not mutual simple")
{
    CHECK(affine_cipher_data_is_valid("ATTACK AT DAWN", {3, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 0);
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK(affine_cipher_data_is_valid("ATTACK AT DA$N", {7, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 0);
}

TEST_CASE("Affine cipher data is valid")
{
    CHECK(affine_cipher_data_is_valid("ATTACK AT DAWN", {7, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 1);
}

TEST_CASE("Alphabet power and a-key are not mutual simple")
{
    CHECK(affine_reccurent_cipher_data_is_valid("ATTACK AT DAWN", {3, 7, 11, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 0);
}

TEST_CASE("Unknown symbol in the text")
{
    CHECK(affine_reccurent_cipher_data_is_valid("ATTACK AT DA$N", {7, 11, 19, 13}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 0);
}

TEST_CASE("Reccurent affine cipher data is valid")
{
    CHECK(affine_reccurent_cipher_data_is_valid("ATTACK AT DAWN", {7, 13, 19, 23}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ ") == 1);
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

TEST_CASE("Reccurent affine encryption")
{
    CHECK(affine_reccurent_encryption("recurrence", {3, 7, 11, 13}, "abcdefghijklmnopqrstuvwxyz") == "kponuzhkwn");
}

TEST_CASE("Reccurent affine decryption")
{
    CHECK(affine_reccurent_decryption("kponuzhkwn", {3, 7, 11, 13}, "abcdefghijklmnopqrstuvwxyz") == "recurrence");
}
