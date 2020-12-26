// main.cpp

#include <iostream>
#include "cpp/AffineCipher.h"
#include "cpp/CaesarCipherTest.h"

int main()
{
    AffineCipher::testSuite();
    //CaesarCipher::testSuite();
    std::cout << "Tests passed!\n";
}
