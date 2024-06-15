#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Hill_encoder.hpp"
#include "doctest.h"

Matrix_class Key1({{2, 3, 1}, {7, 4, 5}, {8, 8, 2}}, 3, 3);
Matrix_class Key2({{7, 2, 4}, {9, 1, 7}, {7, 2, 6}}, 3, 3);
Matrix_class Key3({{3, 0, 0}, {0, 3, 0}, {0, 0, 1}}, 3, 3);

TEST_CASE("Hill cipher encoder output data correct.") {
  CHECK(Hill_cipher_encoder(" abcdefghijklmnopqrstuvwxyz", "skilled", Key1) ==
        "zfokvmhae");
}

TEST_CASE("Hill cipher decoder output data correct.") {
  CHECK(Hill_cipher_decoder(" abcdefghijklmnopqrstuvwxyz", "zfokvmhae", Key1) ==
        "skilled  ");
}

TEST_CASE("Hill's recurrent cipher encoder output data correct.") {
  CHECK(Rec_Hill_cipher_encoder(" abcdefghijklmnopqrstuvwxyz", "economics",
                                Key1, Key2) == "gnmrpqqqv");
}

TEST_CASE("Hill's recurrent cipher decoder output data correct.") {
  CHECK(Rec_Hill_cipher_decoder(" abcdefghijklmnopqrstuvwxyz", "gnmrpqqqv",
                                Key1, Key2) == "economics");
}

TEST_CASE("Input data incorrect, case Alphabet letter repeat") {
  CHECK_THROWS_WITH(
      hill_data_is_valid("skilled", " abbcdefghijklmnopqrstuvwxyz", Key1),
      "Alphabet letter repeat error");
}

TEST_CASE("Input data incorrect, case Invalid Key matrix.") {
  CHECK_THROWS_WITH(
      hill_data_is_valid("zfokvmxjr", " abcdefghijklmnopqrstuvwxyz", Key3),
      "Invalid Key matrix");
}

TEST_CASE("Input data incorrect, case Unknown text symbol.") {
  CHECK_THROWS_WITH(
      hill_data_is_valid("economics7", " abcdefghijklmnopqrstuvwxyz", Key1),
      "Unknown text symbol");
}

TEST_CASE("Input data incorrect, case Invalid Key matrix.") {
  CHECK_THROWS_WITH(
      hill_data_is_valid("gnmrpqqqv", " abcdefghijklmnopqrstuvwxyz", Key3),
      "Invalid Key matrix");
}
