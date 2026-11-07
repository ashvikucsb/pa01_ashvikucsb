#include "card.h"
#include "card_list.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using Suit = Card::Suit;
using Rank = Card::Rank;

int passed = 0;
int failed = 0;

void check(bool result, const string& name) {
    if (result){
        passed++;
    }
    else {
        failed++;
        cout << "FAIL: " << name << endl;
    }
}

Card club(int rank) {
    return Card(Suit::c, static_cast<Rank>(rank));
}

string display(const CardBST& tree) {
    ostringstream out;
    tree.print(out);
    return out.str();
}

void testCards() {
    Card a(Suit::c, Rank::Ace);
    Card b(Suit::c, Rank::Ace);
    Card c(Suit::d, Rank::Ace);
    Card d(Suit::c, Rank::Ten);
    Card e(Suit::h, Rank::Ace);
    Card f(Suit::s, Rank::King);
    check(a == b, "equal cards");
    check(!(a == c), "different suits");
    check(a < d && d > a, "rank order");
    check(e > f && f < e, "suit before rank");
    check(!(a < b) && !(a > b), "equal ordering");
    Suit suits[] = {Suit::c, Suit::d, Suit::s, Suit::h};
    string suitNames[] = {"c", "d", "s", "h"};
    string ranks[] = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};
    for (int i = 0; i < 4; i++){
        for (int j = 1; j <= 13; j++){
            Card card(suits[i], static_cast<Rank>(j));
            ostringstream out;
            out << card << "!";
            check(out.str() == suitNames[i] + " " + ranks[j - 1] + "!", "card output");
            for (int k = 0; k < 4; k++){
                for (int n = 1; n <= 13; n++){
                    Card other(suits[k], static_cast<Rank>(n));
                    int left = i * 13 + j;
                    int right = k * 13 + n;
                    check((card < other) == (left < right), "all card less comparisons");
                    check((card > other) == (left > right), "all card greater comparisons");
                    check((card == other) == (left == right), "all card equality comparisons");
                }
            }
        }
    }
}

void testTrees() {
    int values[5][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0},
        {1, 2, 3, 4, 5, 6, 7},
        {7, 6, 5, 4, 3, 2, 1},
        {4, 2, 6, 1, 3, 5, 7}
    };
    int sizes[] = {0, 1, 7, 7, 7};
    for (int i = 0; i < 5; i++){
        CardBST tree;
        check(tree.begin() == tree.end(), "constructor empty forward");
        check(tree.rbegin() == tree.rend(), "constructor empty reverse");
        check(!tree.contains(club(4)), "contains empty");
        check(!tree.remove(club(4)), "remove empty");
        for (int j = 0; j < sizes[i]; j++){
            check(tree.insert(club(values[i][j])), "insert unique");
        }
        check(tree.insert(club(13)), "insert new card in each shape");
        check(!tree.insert(club(13)), "reject duplicate in each shape");
        check(tree.contains(club(13)), "contains inserted card");
        check(tree.remove(club(13)), "remove inserted card");
        check(!tree.contains(club(13)), "removed card absent");
        check(!tree.remove(club(12)), "remove missing card");
        string expected;
        if (i == 1){
            expected = "c 4\n";
        }
        else if (i > 1){
            expected = "c a\nc 2\nc 3\nc 4\nc 5\nc 6\nc 7\n";
        }
        check(display(tree) == expected, "print each tree shape");
        ostringstream forward;
        auto it = tree.begin();
        int count = 0;
        while (it != tree.end() && count < 52){
            forward << *it << '\n';
            check(it->suit == Suit::c, "iterator arrow access");
            check(it == it && !(it != it), "iterator comparisons");
            ++it;
            count++;
        }
        check(count == sizes[i] && it == tree.end(), "begin end forward endpoint");
        check(forward.str() == expected, "forward traversal each shape");
        ++it;
        check(it == tree.end(), "safe increment after end");
        string reverse;
        auto back = tree.rbegin();
        count = 0;
        while (back != tree.rend() && count < 52){
            ostringstream out;
            out << *back << '\n';
            reverse = out.str() + reverse;
            --back;
            count++;
        }
        check(count == sizes[i] && back == tree.rend(), "rbegin rend reverse endpoint");
        check(reverse == expected, "reverse traversal each shape");
        --back;
        check(back == tree.rend(), "safe decrement after rend");
        if (sizes[i] > 1){
            auto first = tree.begin();
            auto next = first;
            ++next;
            check(first != next && !(first == next), "different iterators");
            --next;
            check(first == next, "iterator forward then reverse");
        }
        CardBST copied(tree);
        check(display(copied) == expected, "copy constructor each shape");
        copied.insert(club(12));
        check(!tree.contains(club(12)), "copy independent");
        CardBST assigned;
        assigned.insert(club(11));
        assigned = tree;
        check(display(assigned) == expected, "assignment each shape");
        assigned = assigned;
        check(display(assigned) == expected, "self assignment each shape");
        assigned.insert(club(10));
        check(!tree.contains(club(10)), "assignment independent");
        for (int j = 0; j < sizes[i]; j++){
            check(tree.contains(club(values[i][j])), "contains before removal");
            check(tree.remove(club(values[i][j])), "remove root and descendants");
            check(!tree.contains(club(values[i][j])), "contains after removal");
        }
        check(tree.begin() == tree.end(), "all removed");
        check(display(copied) == expected + "c q\n", "original removals preserve copy");
    }
    CardBST tree;
    tree.insert(club(4));
    tree.insert(club(2));
    tree.insert(club(6));
    tree.insert(club(1));
    tree.insert(club(5));
    tree.insert(club(7));
    check(tree.remove(club(1)), "remove leaf");
    check(tree.remove(club(4)), "remove root two children deep successor");
    check(tree.remove(club(6)), "remove internal node one child");
    check(tree.remove(club(5)), "remove root two children immediate successor");
    check(tree.remove(club(7)), "remove root only left child");
    check(tree.remove(club(2)), "remove only node");
    check(display(tree).empty(), "deletion cases empty result");
}

void checkGame(CardBST& alice, CardBST& bob, const string& expected,
               const string& aliceLeft, const string& bobLeft) {
    ostringstream out;
    streambuf* old = cout.rdbuf(out.rdbuf());
    playGame(alice, bob);
    cout.rdbuf(old);
    check(out.str() == expected, "game output");
    check(display(alice) == aliceLeft, "Alice remaining cards");
    check(display(bob) == bobLeft, "Bob remaining cards");
}

void testGames() {
    {
        CardBST alice, bob;
        Card a[] = {Card(Suit::h, Rank::Three), Card(Suit::s, Rank::Ten),
                    club(1), club(3), Card(Suit::s, Rank::Five),
                    Card(Suit::h, Rank::Ten), Card(Suit::d, Rank::Ace)};
        Card b[] = {club(2), Card(Suit::d, Rank::Ace), Card(Suit::h, Rank::Ten),
                    club(3), Card(Suit::d, Rank::Jack), Card(Suit::s, Rank::Ten),
                    Card(Suit::h, Rank::Ace)};
        for (int i = 0; i < 7; i++){
            alice.insert(a[i]);
            bob.insert(b[i]);
        }
        checkGame(alice, bob,
            "Alice picked matching card c 3\nBob picked matching card h 10\n"
            "Alice picked matching card d a\nBob picked matching card s 10\n"
            "\nAlice's cards:\nc a\ns 5\nh 3\n\nBob's cards:\nc 2\nd j\nh a\n",
            "c a\ns 5\nh 3\n", "c 2\nd j\nh a\n");
    }
    {
        CardBST alice, bob;
        bob.insert(club(2));
        checkGame(alice, bob, "\nAlice's cards:\n\nBob's cards:\nc 2\n", "", "c 2\n");
    }
    {
        CardBST alice, bob;
        alice.insert(club(1));
        checkGame(alice, bob, "\nAlice's cards:\nc a\n\nBob's cards:\n", "c a\n", "");
    }
    {
        CardBST alice, bob;
        alice.insert(club(1));
        bob.insert(club(2));
        checkGame(alice, bob, "\nAlice's cards:\nc a\n\nBob's cards:\nc 2\n", "c a\n", "c 2\n");
    }
    {
        CardBST alice, bob;
        checkGame(alice, bob, "\nAlice's cards:\n\nBob's cards:\n", "", "");
    }
    {
        CardBST alice, bob;
        for (int i = 1; i <= 3; i++){
            alice.insert(club(i));
            bob.insert(club(i));
        }
        checkGame(alice, bob, "Alice picked matching card c a\nBob picked matching card c 3\n"
            "Alice picked matching card c 2\n\nAlice's cards:\n\nBob's cards:\n", "", "");
    }
}

int main() {
    testCards();
    testTrees();
    testGames();
    cout << passed << " checks passed, " << failed << " checks failed" << endl;
    if (failed != 0){
        return 1;
    }
    return 0;
}
