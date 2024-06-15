#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "mainwindow.h"


TEST_CASE("Hex string to vector test") {
  std::string hexString = "EF";
  uint8_t ans = 239;
  CHECK(hexStringToVector(hexString)[0] == ans);
}

TEST_CASE("Hex string to vector test") {
  std::string hexString = "EF 00";
  std::vector<uint8_t> ans = {239, 0};
  CHECK(hexStringToVector(hexString) == ans);
}

TEST_CASE("Vector to hex string test") {
  std::vector<uint8_t> Vector = {239};
  CHECK(vectorToHexString(Vector) == "EF");
}

TEST_CASE("Vector to hex string test") {
  std::vector<uint8_t> Vector = {239, 0};
  CHECK(vectorToHexString(Vector) == "EF 00");
}
