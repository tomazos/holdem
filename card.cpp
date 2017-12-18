#include "card.h"

#include <unordered_map>

namespace {

std::unordered_map <uint8_t, std::string> build_card_id_to_string_map() {
    std::unordered_map <uint8_t, std::string> map;
    for (Card card : all_cards())
        map[card.id()] = card.face().string() + card.suit().string();
    return map;
};

const std::string& card_id_to_string(uint8_t id) {
    static const std::unordered_map<uint8_t, std::string> map = build_card_id_to_string_map();
    return map.at(id);
}

std::unordered_map <std::string, uint8_t> build_card_string_to_id_map() {
    std::unordered_map <std::string, uint8_t> map;
    for (Card card : all_cards())
        map[card.face().string() + card.suit().string()] = card.id();
    return map;
};

uint8_t card_string_to_id(const std::string& str) {
    static const std::unordered_map<std::string, uint8_t> map = build_card_string_to_id_map();
    return map.at(str);
}

std::vector<Card> build_all_cards() {
    std::vector<Card> cards;
    for (Face face : all_faces())
        for (Suit suit : all_suits())
            cards.emplace_back(face, suit);
    return cards;
}

}  // namespace

Card::Card(const std::string& str) : _id(card_string_to_id(str)) {}

const std::string& Card::string() { return card_id_to_string(_id); }

const std::vector<Card>& all_cards() {
    static std::vector<Card> cards = build_all_cards();
    return cards;
}
