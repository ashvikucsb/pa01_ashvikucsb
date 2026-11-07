#include "card.h"
#include <cassert>

int main() {
    using Suit = Card::Suit;
    using Rank = Card::Rank;

    Card a(Suit::c, Rank::Ace);
    Card b(Suit::c, Rank::Ace);
    assert(a == b);

    Card c(Suit::d, Rank::Ace);
    assert(!(a == c));

    Card d(Suit::c, Rank::Ten);
    assert(a < d);
    assert(d > a);

    Card e(Suit::h, Rank::Ace);
    Card f(Suit::s, Rank::King);
    assert(e > f);
    assert(f < e);

    assert(!(a < b));
    assert(!(a > b));
}