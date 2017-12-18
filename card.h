#pragma once

#include "face.h"
#include "suit.h"

constexpr size_t NCARDS = 52;

class Card {
public:
    Card(const std::string& str);
    Card(Face face, Suit suit) : _id(_pack(face, suit)) {}
    explicit Card(uint8_t id) : _id(id) {}

    uint8_t id() const { return _id; }

    Face face() const { return Face(_unpack_face()); }
    Suit suit() const { return Suit(_unpack_suit()); }

    const std::string& string();

private:
    static uint8_t _pack(Face face, Suit suit) { return face.value() << 2 | suit.id(); }
    uint8_t _unpack_face() const { return _id >> 2 & 0b1111; }
    uint8_t _unpack_suit() const { return _id >> 0 & 0b11; }

    uint8_t _id;
};

inline bool consecutive(Card a, Card b) { return a.face().value()+1 == b.face().value(); }

const std::vector<Card>& all_cards();

DEFINE_STANARD_OPS(Card, id, uint8_t)

