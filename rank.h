#pragma once

#include <cstdint>
#include "face.h"

class Rank {
public:
    enum Class {
        ROYAL_FLUSH = 9,
        STRAIGHT_FLUSH = 8,
        FOUR_OF_A_KIND = 7,
        FULL_HOUSE = 6,
        FLUSH = 5,
        STRAIGHT = 4,
        THREE_OF_A_KIND = 3,
        TWO_PAIR = 2,
        PAIR = 1,
        HIGH_CARD = 0
    };

    Class class_() { return _get_class(); }

    static Rank royal_flush() { return {ROYAL_FLUSH}; }
    static Rank straight_flush(Face high) { return {STRAIGHT_FLUSH, high}; }
    static Rank four_of_a_kind(Face quads) { return {FOUR_OF_A_KIND, quads}; }
    static Rank full_house(Face trips, Face pair_face) { return {FULL_HOUSE, trips, pair_face}; }
    static Rank flush(Face high) { return {FLUSH, high}; }
    static Rank straight(Face high) { return {STRAIGHT, high}; }
    static Rank three_of_a_kind(Face trips, Face kicker1, Face kicker2) { return {THREE_OF_A_KIND, trips, kicker1, kicker2}; }
    static Rank two_pair(Face high_pair, Face low_pair, Face kicker) { return {TWO_PAIR, high_pair, low_pair, kicker}; }
    static Rank pair(Face pair_face, Face kicker1, Face kicker2, Face kicker3) { return {PAIR, pair_face, kicker1, kicker2, kicker3}; }
    static Rank high_card(Face high, Face kicker1, Face kicker2, Face kicker3, Face kicker4) { return {HIGH_CARD, high, kicker1, kicker2, kicker3, kicker4}; }

    uint32_t value() const { return _value; }

    std::string string() const;

private:
    template<typename... Faces>
    Rank(Class class_, Faces... faces_in) : _value(0) {
        static_assert(sizeof...(faces_in) <= 5);
        _set_class(class_);
        Face faces[] = {faces_in...};
        for (size_t i = 0; i < sizeof...(faces_in); i++) {
            _set_face(i, faces[i]);
        }
    }

    void _set_class(Class class_) {
        _value |= int(class_) << 20;
    }

    Class _get_class() const {
        return Class(_value >> 20);
    }

    void _set_face(int pos, Face face) {
        _value |= uint32_t(face.value()) << (4-pos)*4;
    }

    Face _get_face(int pos) const {
        return Face(_value >> (4-pos)*4 & 0b1111);
    }

    uint32_t _value;
};

DEFINE_STANARD_OPS(Rank, value, uint32_t)
