#include "card_list.h"
#include <iostream>
#include <stdexcept>

CardBST::CardBST() : root(nullptr) {}

CardBST::CardBST(const CardBST& other) : root(nullptr) {
    copy(other.root);
}

CardBST& CardBST::operator=(const CardBST& other) {
    if (this != &other){
        clear(root);
        root = nullptr;
        copy(other.root);
    }
    return *this;
}

CardBST::~CardBST() {
    clear(root);
}

void CardBST::clear(Node* curr) {
    if (curr == nullptr){
        return;
    }
    clear(curr->left);
    clear(curr->right);
    delete curr;
}

void CardBST::copy(Node* curr) {
    if (curr == nullptr){
        return;
    }
    insert(curr->card);
    copy(curr->left);
    copy(curr->right);
}

CardBST::Node* CardBST::find(const Card& card) const {
    Node* curr = root;
    while (curr != nullptr){
        if (card == curr->card){
            return curr;
        }
        if (card < curr->card){
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return nullptr;
}

bool CardBST::contains(const Card& card) const {
    return find(card) != nullptr;
}

bool CardBST::insert(const Card& card) {
    if (root == nullptr){
        root = new Node(card, nullptr);
        return true;
    }
    Node* curr = root;
    while (curr != nullptr){
        if (card == curr->card){
            return false;
        }
        if (card < curr->card){
            if (curr->left == nullptr){
                curr->left = new Node(card, curr);
                return true;
            }
            curr = curr->left;
        }
        else {
            if (curr->right == nullptr){
                curr->right = new Node(card, curr);
                return true;
            }
            curr = curr->right;
        }
    }
    return false;
}

bool CardBST::remove(const Card& card) {
    Node* curr = find(card);
    if (curr == nullptr){
        return false;
    }
    if (curr->left != nullptr && curr->right != nullptr){
        Node* next = curr->right;
        while (next->left != nullptr){
            next = next->left;
        }
        curr->card = next->card;
        curr = next;
    }
    Node* child = curr->left;
    if (child == nullptr){
        child = curr->right;
    }
    if (child != nullptr){
        child->parent = curr->parent;
    }
    if (curr->parent == nullptr){
        root = child;
    }
    else if (curr == curr->parent->left){
        curr->parent->left = child;
    }
    else {
        curr->parent->right = child;
    }
    delete curr;
    return true;
}

CardBST::Node* CardBST::Iterator::successor(Node* n) const {
    if (n == nullptr){
        return nullptr;
    }
    if (n->right != nullptr){
        n = n->right;
        while (n->left != nullptr){
            n = n->left;
        }
        return n;
    }
    Node* parent = n->parent;
    while (parent != nullptr && n == parent->right){
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

CardBST::Node* CardBST::Iterator::predecessor(Node* n) const {
    if (n == nullptr){
        return nullptr;
    }
    if (n->left != nullptr){
        n = n->left;
        while (n->right != nullptr){
            n = n->right;
        }
        return n;
    }
    Node* parent = n->parent;
    while (parent != nullptr && n == parent->left){
        n = parent;
        parent = parent->parent;
    }
    return parent;
}

CardBST::Iterator& CardBST::Iterator::operator++() {
    curr = successor(curr);
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    curr = predecessor(curr);
    return *this;
}

const Card& CardBST::Iterator::operator*() const {
    if (curr == nullptr){
        throw std::out_of_range("Cannot access an end iterator");
    }
    return curr->card;
}

const Card* CardBST::Iterator::operator->() const {
    return &operator*();
}

bool CardBST::Iterator::operator==(const Iterator& other) const {
    return curr == other.curr;
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
    return curr != other.curr;
}

CardBST::Iterator CardBST::begin() const {
    Node* curr = root;
    while (curr != nullptr && curr->left != nullptr){
        curr = curr->left;
    }
    return Iterator(curr);
}

CardBST::Iterator CardBST::end() const {
    return Iterator(nullptr);
}

CardBST::Iterator CardBST::rbegin() const {
    Node* curr = root;
    while (curr != nullptr && curr->right != nullptr){
        curr = curr->right;
    }
    return Iterator(curr);
}

CardBST::Iterator CardBST::rend() const {
    return Iterator(nullptr);
}

void CardBST::print(std::ostream& out) const {
    for (auto it = begin(); it != end(); ++it){
        out << *it << '\n';
    }
}

void playGame(CardBST& alice, CardBST& bob) {
    bool aliceTurn = true;
    while (true){
        if (aliceTurn){
            auto it = alice.begin();
            while (it != alice.end() && !bob.contains(*it)){
                ++it;
            }
            if (it == alice.end()){
                break;
            }
            Card card = *it;
            std::cout << "Alice picked matching card " << card << '\n';
            alice.remove(card);
            bob.remove(card);
        }
        else {
            auto it = bob.rbegin();
            while (it != bob.rend() && !alice.contains(*it)){
                --it;
            }
            if (it == bob.rend()){
                break;
            }
            Card card = *it;
            std::cout << "Bob picked matching card " << card << '\n';
            alice.remove(card);
            bob.remove(card);
        }
        aliceTurn = !aliceTurn;
    }
    std::cout << "\nAlice's cards:\n";
    alice.print(std::cout);
    std::cout << "\nBob's cards:\n";
    bob.print(std::cout);
}
