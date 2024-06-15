#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "mainwindow.h"
#include "doctest.h"

/**
 * \file Frontend_test.cpp
 *
 * This file contains affine ciphers testing for errors, ciphering and deciphering results
 *
 */

TEST_CASE("Hex string to vector test")
{
    QString hexString = "EF";
    CHECK(hexStringToVector(hexString[0]==static_cast<uint8_t>(239));
}

TEST_CASE("Vector to hex string test")
{
    std::vector<uint8_t> Vector={239};
    CHECK(vectorToHexString(Vector)=="EF ");
}
