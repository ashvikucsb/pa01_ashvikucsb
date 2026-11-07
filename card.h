#ifndef CARD_H
#define CARD_H

#include <ostream>

struct Card {
    enum class Suit { h = 4, d = 2, c = 1, s = 3 };
    enum class Rank {
        Ace = 1, Two, Three, Four, Five, Six, Seven,
        Eight, Nine, Ten, Jack, Queen, King
    };

    Suit suit;
    Rank rank;

    Card(Suit s, Rank r) : suit(s), rank(r) {}

    bool operator==(const Card& other) const {
        return suit == other.suit && rank == other.rank;
    }

    bool operator>(const Card& other) const {
        if (suit != other.suit) {
            return suit > other.suit;
        }
        return rank > other.rank;
    }

    bool operator<(const Card& other) const {
        if (suit != other.suit) {
            return suit < other.suit;
        }
        return rank < other.rank;
    }
};

std::ostream& operator<<(std::ostream& out, const Card& n);

#endif
