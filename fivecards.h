#pragma once

#include <optional>
#include <sstream>
#include <algorithm>

#include "card.h"
#include "rank.h"

class FiveCards {
public:
    FiveCards(Card card1, Card card2, Card card3, Card card4, Card card5) : _id(_pack(card1, card2, card3, card4, card5)) {}
    explicit FiveCards(uint32_t id) : _id(id) {}

    std::string string() const {
        std::ostringstream oss;
        for (size_t i = 0; i < 5; i++)
            oss << card(i) << " ";
        return oss.str();
    }

    uint32_t id() const { return _id; }

    Card card(size_t i) const { return Card(_id >> (4-i)*6 & 0b0011'1111); }

    template<typename F>
    static void for_each(F f);

    bool calc_flush() {
        for (size_t i = 1; i < 5; i++)
            if (card(0).suit() != card(i).suit())
                return false;
        return true;
    }

    std::optional<Face> calc_straight() {
        for (size_t i = 0; i < 3; i++)
            if (!consecutive(card(i), card(i+1)))
                return std::nullopt;

        if (card(4).face() == Face::ace && card(0).face() == Face::two)
            return Face::five;
        else if (consecutive(card(3), card(4)))
            return card(4).face();
        else
            return std::nullopt;
    }

    Rank calc_rank() {
        bool flush = calc_flush();

        if (std::optional<Face> straight = calc_straight()) {
            Face high = *straight;

            if (flush) {
                if (high == Face::ace)
                    return Rank::royal_flush();
                else
                    return Rank::straight_flush(high);
            } else
                return Rank::straight(high);
        }

        if (flush)
            return Rank::flush(card(4).face());

        for (size_t i = 0; i < 2; i++)
            if (card(i).face() == card(i+3).face())
                return Rank::four_of_a_kind(card(i).face());

        for (size_t i = 0; i < 3; i++) {
            if (card(i).face() == card(i+2).face()) {
                Face trips = card(i).face();
                Face face1 = card((i+3) % 5).face();
                Face face2 = card((i+4) % 5).face();
                if (face1 == face2)
                    return Rank::full_house(trips, face1);
                else if (face1 > face2)
                    return Rank::three_of_a_kind(trips, face1, face2);
                else
                    return Rank::three_of_a_kind(trips, face2, face1);
            }
        }

        for (size_t i = 4; i > 0; i--) {
            if (card(i).face() != card(i-1).face())
                continue;

            for (size_t j = 0; j < i-1; j++)
                if (card(j).face() == card(j+1).face())
                    for (size_t k = 0; k < 5; k++)
                        if (k != i && k != i-1 && k != j && k != j+1)
                            return Rank::two_pair(card(i).face(), card(j).face(), card(k).face());

            std::vector<Face> kickers;

            for (size_t j = 4; j != size_t(-1); j--)
                if (j != i && j != i-1)
                    kickers.push_back(card(j).face());

            return Rank::pair(card(i).face(), kickers.at(0), kickers.at(1), kickers.at(2));
        }

        return Rank::high_card(card(4).face(), card(3).face(), card(2).face(), card(1).face(), card(0).face());
    }

private:
    static uint64_t _pack(Card card1, Card card2, Card card3, Card card4, Card card5) {
        Card cards[5] = {card1, card2, card3, card4, card5};
        std::sort(cards, cards+5);
        return _pack_sorted(cards);
    }
    static uint32_t _pack_sorted(Card (&cards)[5]) {
        return uint32_t(cards[0].id()) << 24 | uint32_t(cards[1].id()) << 18 | uint32_t(cards[2].id()) << 12 | cards[3].id() << 6 | cards[4].id() << 0;
    }

    uint32_t _id;
};

DEFINE_STANARD_OPS(FiveCards, id, uint32_t)

template<typename F>
void FiveCards::for_each(F f) {
    const std::vector<Card>& C = all_cards();
    for (size_t x0 = 0; x0 < NCARDS-4; x0++)
        for (size_t x1 = x0+1; x1 < NCARDS-3; x1++)
            for (size_t x2 = x1+1; x2 < NCARDS-2; x2++)
                for (size_t x3 = x2+1; x3 < NCARDS-1; x3++)
                    for (size_t x4 = x3+1; x4 < NCARDS; x4++) {
                        Card cards[5] = {C[x0],C[x1],C[x2],C[x3],C[x4]};
                        f(FiveCards(_pack_sorted(cards)));
                    }
}
