#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "util.h"

constexpr size_t NSUITS = 4;

class Suit {
public:
    explicit Suit(const std::string& str);
    explicit Suit(uint8_t id) : _id(id) {}

    const std::string& string();
    uint8_t id() const { return _id; }

private:
    uint8_t _id;
};

const std::vector<Suit>& all_suits();

DEFINE_STANARD_OPS(Suit, id, uint8_t)
