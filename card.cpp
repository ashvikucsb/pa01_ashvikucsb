#include "card.h"

std::ostream& operator<<(std::ostream& out, const Card& n) {
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

