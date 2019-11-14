#include <bits/stdc++.h>
#include "LZWEncoder/encoder.h"
#include "decoder.h"

using namespace std;

int main() {
    ifstream in_stream;
    uint64_t byte_counter = 0;
    unsigned char input[5760];
    unsigned char encode_output[5760];
    unsigned char decode_output[5760];

    // there are multiple test files
    // in_stream.open("little_prince", ios::binary);
    // in_stream.open("gtk+.tar", ios::binary);
    // in_stream.open("limit_node", ios::binary);
    in_stream.open("linux.tar", ios::binary);

    // check streams
    if (!in_stream.good()) {
        std::cerr << "Could not open input file.\n";
        return EXIT_FAILURE;
    }

    // compress
    while (true) {
        // read in string
        if (in_stream.eof() || in_stream.bad()) {
            break;
        }

        in_stream.read((char *) input, 3584 + random() % 2177);
        byte_counter += in_stream.gcount();

        // if the string length is zero, stop the compress
        if (in_stream.gcount() == 0) {
            break;
        }

        uint32_t encode_length;
        bool result = lzw_tree_encode(input, encode_output, in_stream.gcount(), encode_length);

        if (! result) {
            cout << "chunk length " << in_stream.gcount() << endl;
            continue;
        }

        uint32_t decode_length = lzw_decode(encode_output, decode_output, encode_length);

        // find errors
        bool exit_flag = false;
        if (decode_length != in_stream.gcount()) {
            cout << "data length mismatch!" << endl;
            cout << "exp " << in_stream.gcount() << endl;
            cout << "act " << decode_length << endl;
            exit_flag = true;
        }
        for (uint32_t i = 0; i < decode_length; i++) {
            if (decode_output[i] != input[i]) {
                cout << "data mismatch!" << endl;
                cout << "index " << i << endl;
                cout << "exp " << input[i] << endl;
                cout << "act " << decode_output[i] << endl;
                exit_flag = true;
            }
        }

        if (exit_flag) {
            exit(1);
        }
    }

    return 0;
}