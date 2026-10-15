
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

//For text or paths
string sha1(const string& input) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    string msg = input;
    msg += static_cast<char>(0x80);

    uint64_t bit_len = msg.length() * 8;
    msg += string(64 - (msg.length() % 64), 0);

    for (uint64_t i = 0; i < msg.length(); i += 64) {
        uint32_t w[80];
        for (int j = 0; j < 16; ++j) {
            w[j] = (static_cast<uint32_t>(msg[i + j * 4 + 0]) << 24) |
                (static_cast<uint32_t>(msg[i + j * 4 + 1]) << 16) |
                (static_cast<uint32_t>(msg[i + j * 4 + 2]) << 8) |
                (static_cast<uint32_t>(msg[i + j * 4 + 3]) << 0);
        }
        for (int j = 16; j < 80; ++j) {
            uint32_t temp = w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16];
            w[j] = (temp << 1) | (temp >> 31);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int j = 0; j < 80; ++j) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[j];
            e = d;
            d = c;
            c = (b << 30) | (b >> 2);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    ostringstream oss;
    oss << hex << setfill('0') << setw(8) << h0
        << setw(8) << h1 << setw(8) << h2
        << setw(8) << h3 << setw(8) << h4;
    return oss.str();
}

//For Images 
string sha1(const Mat& input) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    string msg(reinterpret_cast<const char*>(input.data), input.total() * input.elemSize());

    msg += static_cast<char>(0x80);

    uint64_t bit_len = msg.length() * 8;
    msg += string(64 - (msg.length() % 64), 0);

    for (uint64_t i = 0; i < msg.length(); i += 64) {
        uint32_t w[80];
        for (int j = 0; j < 16; ++j) {
            w[j] = (static_cast<uint32_t>(msg[i + j * 4 + 0]) << 24) |
                (static_cast<uint32_t>(msg[i + j * 4 + 1]) << 16) |
                (static_cast<uint32_t>(msg[i + j * 4 + 2]) << 8) |
                (static_cast<uint32_t>(msg[i + j * 4 + 3]) << 0);
        }
        for (int j = 16; j < 80; ++j) {
            uint32_t temp = w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16];
            w[j] = (temp << 1) | (temp >> 31);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        for (int j = 0; j < 80; ++j) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[j];
            e = d;
            d = c;
            c = (b << 30) | (b >> 2);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    ostringstream oss;
    oss << hex << setfill('0') << setw(8) << h0
        << setw(8) << h1 << setw(8) << h2
        << setw(8) << h3 << setw(8) << h4;
    return oss.str();
}


