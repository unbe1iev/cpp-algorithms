#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#define size 10 // Predefined variable specifying the maximum number of numbers in the queue

using namespace std;

// One element representation class:
class Item {
    int val = NULL;
    Item* next = nullptr; // next item
    Item* prev = nullptr; // previous item
public:
    friend class Queue; // FIFO Queue is using items

    Item(const Item&) {}; // copy constructor

    Item(int v) {
        val = v;
    }

    int getVal() {
        return val;
    }
};

// FIFO Queue class:
class Queue {
    int amount = 0; // actual amount of elements (numbers in queue)
    Item* first = nullptr; //head
    Item* last = nullptr; //tail
public:
    // functions to check if it is possible to enter/delete n numbers
    bool possibleToAdd(const int val);
    bool possibleToDelete(const int val);

    bool addValue(int& val);

    bool deleteValue();
    bool deleteAll();

    int getAmount() const;

    void print() const;
    void printReversed() const;

    Queue() = default;
    ~Queue() {
        // Deleting memory alocated things:
        delete first; first = nullptr;
        delete last; last = nullptr;
    }
};