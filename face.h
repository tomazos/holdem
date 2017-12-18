#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>
#include "util.h"

constexpr size_t NFACES = 13;

class Face {
public:
    explicit Face(const std::string& str);
    explicit Face(uint8_t value) : _value(value) {}

    const std::string& string();
    uint8_t value() const { return _value; }

    static Face ace;
    static Face two;
    static Face five;

private:
    uint8_t _value;
};

const std::vector<Face>& all_faces();

DEFINE_STANARD_OPS(Face, value, uint8_t)