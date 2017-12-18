#include "rank.h"

std::string Rank::string() const {
    switch (_get_class()) {
    case ROYAL_FLUSH:
        return "ROYAL FLUSH";

    case STRAIGHT_FLUSH:
        return stringify("STRAIGHT FLUSH ", _get_face(0), " HIGH");

    case FOUR_OF_A_KIND:
        return stringify("FOUR OF A KIND ", _get_face(0));

    case FULL_HOUSE:
        return stringify("FULL HOUSE ", _get_face(0), " OVER ", _get_face(1));

    case FLUSH:
        return stringify("FLUSH ", _get_face(0), " HIGH");

    case STRAIGHT:
        return stringify("STRAIGHT ", _get_face(0), " HIGH");

    case THREE_OF_A_KIND:
        return stringify("THREE OF A KIND ", _get_face(0), " KICKER ", _get_face(1), "-", _get_face(2));

    case TWO_PAIR:
        return stringify("TWO PAIR ", _get_face(0), "-", _get_face(1), " KICKER ", _get_face(2));

    case PAIR:
        return stringify("PAIR ", _get_face(0), " KICKER ", _get_face(1), "-", _get_face(2), "-", _get_face(3));

    case HIGH_CARD:
        return stringify("HIGH CARD ", _get_face(0), " KICKER ",
                         _get_face(1), "-", _get_face(2), "-", _get_face(3), "-", _get_face(4));
    };
    throw std::runtime_error(stringify("INVALID RANK: ", value()));
}

