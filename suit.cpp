#include "suit.h"

#include <vector>
#include <unordered_map>

namespace {

std::vector<std::string> suit_strings = { "♠", "♦", "♣", "♥" };

std::unordered_map <std::string, uint8_t> build_suit_string_to_id_map() {
    std::unordered_map <std::string, uint8_t> map;
    for (size_t i = 0; i < NSUITS; i++)
        map[suit_strings[i]] = i;
    return map;
};

uint8_t suit_string_to_id(const std::string& str) {
    static const std::unordered_map<std::string, uint8_t> map = build_suit_string_to_id_map();
    return map.at(str);
}

std::vector<Suit> build_all_suits() {
    std::vector<Suit> vec;
    for (uint8_t i = 0; i < NSUITS; i++)
        vec.push_back(Suit(i));
    return vec;
}

}  // namespace

Suit::Suit(const std::string& str) : _id(suit_string_to_id(str)) {}

const std::string& Suit::string() { return suit_strings.at(_id); }

const std::vector<Suit>& all_suits() {
    static std::vector<Suit> suits = build_all_suits();
    return suits;
}
