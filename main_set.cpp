#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

bool readHand(istream& input, set<Card>& hand) {
  char suit;
  string rank;
  while (input >> suit) {
    if (!(input >> rank)){
      return false;
    }
    Card::Suit cardSuit;
    switch (suit) {
      case 'c': cardSuit = Card::Suit::c; break;
      case 'd': cardSuit = Card::Suit::d; break;
      case 's': cardSuit = Card::Suit::s; break;
      case 'h': cardSuit = Card::Suit::h; break;
      default: return false;
    }

    int value;
    if (rank == "a") value = 1;
    else if (rank == "j") value = 11;
    else if (rank == "q") value = 12;
    else if (rank == "k") value = 13;
    else if (rank == "10") value = 10;
    else if (rank.size() == 1 && rank[0] >= '2' && rank[0] <= '9') {
      value = rank[0] - '0';
    } 
    else {
      return false;
    }
    hand.insert(Card(cardSuit, static_cast<Card::Rank>(value)));
  }
  return input.eof() && !input.bad();
}

int main(int argc, char** argv){
  if(argc != 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argv[1]);
  ifstream cardFile2 (argv[2]);

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << (cardFile1.fail() ? argv[1] : argv[2]);
    return 1;
  }

  set<Card> alice, bob;
  if (!readHand(cardFile1, alice) || !readHand(cardFile2, bob)){
    cout << "Invalid card input" << endl;
    return 1;
  }

  bool aliceTurn = true;
  while (true) {
    if (aliceTurn) {
      auto match = alice.begin();
      while (match != alice.end() && bob.find(*match) == bob.end()) ++match;
        if (match == alice.end()) break;
        cout << "Alice picked matching card " << *match << '\n';
        bob.erase(*match);
        alice.erase(match);
    } 
    else {
        auto match = bob.rbegin();
          while (match != bob.rend() && alice.find(*match) == alice.end()) ++match;
            if (match == bob.rend()) break;
            Card card = *match;
            cout << "Bob picked matching card " << card << '\n';
            alice.erase(card);
            bob.erase(card);
    }
    aliceTurn = !aliceTurn;
  }

  cout << "\nAlice's cards:\n";
  for (const Card& card : alice) cout << card << '\n';
  cout << "\nBob's cards:\n";
  for (const Card& card : bob) cout << card << '\n';

  return 0;
}

