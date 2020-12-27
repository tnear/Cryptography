// main.cpp

#include <iostream>
#include "cpp/AffineCipherTest.h"
#include "cpp/CaesarCipherTest.h"

int main()
{
    testSuite();
    CaesarCipher::testSuite();
    std::cout << "Tests passed!\n";
}
