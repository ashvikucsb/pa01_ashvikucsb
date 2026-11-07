// card.h
// Author: Ashvik Vivekan

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

inline std::ostream& operator<<(std::ostream& out, const Card& n) {
    switch (n.suit) {
        case Card::Suit::c: out << 'c'; break;
        case Card::Suit::d: out << 'd'; break;
        case Card::Suit::s: out << 's'; break;
        case Card::Suit::h: out << 'h'; break;
    }
    out << ' ';
    switch (n.rank) {
        case Card::Rank::Ace:   out << 'a'; break;
        case Card::Rank::Jack:  out << 'j'; break;
        case Card::Rank::Queen: out << 'q'; break;
        case Card::Rank::King:  out << 'k'; break;
        default: out << ((int) n.rank); break;
    }

    return out;
}

#endif