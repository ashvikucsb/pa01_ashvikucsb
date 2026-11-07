#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardBST {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Card& c, Node* p) : card(c), left(nullptr), right(nullptr), parent(p) {}
    };

    Node* root;
    void clear(Node* curr);
    void copy(Node* curr);
    Node* find(const Card& card) const;

public:
    class Iterator {
    private:
        Node* curr;
        Iterator(Node* n) : curr(n) {}
        Node* successor(Node* n) const;
        Node* predecessor(Node* n) const;
        friend class CardBST;

    public:
        Iterator& operator++();
        Iterator& operator--();
        const Card& operator*() const;
        const Card* operator->() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    CardBST();
    CardBST(const CardBST& other);
    CardBST& operator=(const CardBST& other);
    ~CardBST();
    bool insert(const Card& card);
    bool remove(const Card& card);
    bool contains(const Card& card) const;
    void print(std::ostream& out) const;
    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

void playGame(CardBST& alice, CardBST& bob);

#endif
