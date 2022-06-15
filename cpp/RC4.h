// RC4.h
// C++ implementation of the RC4 stream cipher
// The RC4 constructor requires a key
// encrypt() converts a string to hex ciphertext
// decrypt() converts a hex string back to original text

#ifndef RC4_H
#define RC4_H

#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <algorithm>

class RC4
{
public:
    RC4(const std::string &key)
        : m_key(key)
    {
    }

    std::string encrypt(const std::string &input)
    {
        ksa();
        std::vector<int> cipherText = prga(input);
        return intToHex(cipherText);
    }

    std::string decrypt(const std::string &input)
    {
        // input validation
        if (input.size() % 2 != 0)
            throw std::exception("Ciphertext must be an even-length hex string");

        if (!std::all_of(input.begin(), input.end(), ::isxdigit))
            throw std::exception("Ciphertext must be an even-length hex string");

        ksa();
        std::string asciiString = hexToAscii(input);

        std::string decodedString;
        for (int i : prga(asciiString))
        {
            decodedString += char(i);
        }
        return decodedString;
    }

private:
    // key scheduling algorithm
    void ksa()
    {
        // generate [0:255]
        m_s.resize(RC4_SIZE);
        std::iota(m_s.begin(), m_s.end(), 0);

        int j = 0;
        for (int i = 0; i < m_s.size(); ++i)
        {
            j = (j + m_s[i] + m_key[i % m_key.size()]) % RC4_SIZE;
            std::swap(m_s[i], m_s[j]);
        }
    }

    // pseudo-random generation algorithm
    std::vector<int> prga(const std::string input)
    {
        std::vector<int> cipherText;
        cipherText.resize(input.size());

        int i = 0;
        int j = 0;
        for (int idx = 0; idx < input.size(); ++idx)
        {
            i = (i + 1) % RC4_SIZE;
            j = (j + m_s[i]) % RC4_SIZE;
            std::swap(m_s[i], m_s[j]);

            cipherText[idx] = input[idx] ^ m_s[(m_s[i] + m_s[j]) % RC4_SIZE];
        }

        return cipherText;
    }

    // converts vector of int into a hex string,
    // ex: [50, 146, 220] => "3292dc"
    static std::string intToHex(const std::vector<int> &vInt)
    {
        std::stringstream stream;
        for (int num : vInt)
        {
            // convert to hex, ensuring each int spans two characters
            stream << std::hex << std::setfill('0') << std::setw(2) << num;
        }

        std::string ret = stream.str();
        assert(ret.size() % 2 == 0); // each int becomes two hex characters
        return ret;
    }

    static std::string hexToAscii(const std::string &input)
    {
        // hex string are in groups of two, ex: "af0b"
        assert(input.size() % 2 == 0);
        std::string asciiString;
        asciiString.reserve(input.size() / 2);

        // convert each two character hex into one ascii letter
        for (std::size_t x = 0; x < input.size(); x += 2)
        {
            std::string tmp = input.substr(x, 2);
            int letter = std::stoi(tmp, nullptr, 16);
            asciiString += char(letter);
        }

        return asciiString;
    }

    static constexpr int RC4_SIZE = 256;
    std::vector<int> m_s;
    const std::string m_key;
};

#endif
