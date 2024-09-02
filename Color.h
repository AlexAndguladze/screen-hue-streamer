#pragma once

#include <stdint.h> // Contains uint8_t

 struct Color{
    uint8_t R;
    uint8_t G;
    uint8_t B;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : R(r), G(g), B(b) {}
};