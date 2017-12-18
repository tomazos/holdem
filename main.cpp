#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "face.h"
#include "suit.h"
#include "card.h"
#include "fivecards.h"

int main() {
    OutputFileStream ofs = OutputFileStream::truncate("/home/zos/fivecards");

    std::vector<FiveCards> five_cards;

    size_t nfive = 0;
    std::unordered_map<int, size_t> count_classes;

    FiveCards::for_each([&](FiveCards five_card){
        five_cards.push_back(five_card);
        count_classes[five_card.calc_rank().class_()]++;
        nfive++;
    });

    for (int i = 0; i < 10; i++) {
        std::cout << i << " " << count_classes[i] * 1.0 / nfive << std::endl;
    }

    std::sort(five_cards.begin(), five_cards.end(), [](FiveCards a, FiveCards b) {
        return a.calc_rank() > b.calc_rank();
    });

    for (FiveCards five_card : five_cards) {
        ofs << five_card;
        ofs << " " << five_card.calc_rank();
        ofs << "\n";
    }
}
