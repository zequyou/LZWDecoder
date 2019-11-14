//
// Created by developer on 10/31/19.
//

#ifndef LZW_SUPPORT_H
#define LZW_SUPPORT_H

#include <bits/stdc++.h>
#include <iostream>
#include <cstdint>

using namespace std;

uint16_t get_input(const uint8_t input[], uint32_t index) {
    uint16_t value;
    uint32_t byte_bias;
    if (index & 1u) {
        byte_bias = index / 2 * 3 + 1;
        value = ((input[byte_bias] & 15u) << 8u);
        value |= (uint16_t)(input[byte_bias + 1]);
    } else {
        byte_bias = index / 2 * 3;
        value = (((uint16_t)input[byte_bias]) << 4u);
        value |= (uint8_t)(input[byte_bias + 1] >> 4u);
    }

    return value;
}

uint32_t lzw_decode(uint8_t input[], uint8_t output[], uint32_t input_length) {
    unordered_map<uint16_t, string> dictionary(4096);
    int output_index = 0;
    int dict_index = 256;

    // initialize the variables
    for (int i = 0; i < 256; i++) {
        string temp(1, i);
        dictionary.insert({i, temp});
    }

    // the first one must be only a char
    uint16_t last = get_input(input, 0);
    output[output_index++] = (uint8_t)last;
    string c(1, (uint8_t)last);
    for (uint32_t i = 1; i < input_length * 8 / 12; i++) {
        uint16_t curr = get_input(input, i); // current
        string s;
        if (dictionary.find(curr) != dictionary.end()) {
            s = dictionary.find(curr)->second;
        } else {
            s = dictionary.find(last)->second + c;
        }
        for (auto character: s) {
            output[output_index++] = character;
        }
        c = s[0];
        string need_to_insert = dictionary.find(last)->second + c;
        dictionary.insert({dict_index++, need_to_insert});
        last = curr;
    }

    return output_index;
}

#endif //LZW_SUPPORT_H
