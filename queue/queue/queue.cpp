#include "queue.h"


// push from the end of the queue
bool Queue::addValue(int& val) {
    if (amount == 0) {
        Item* item = new Item(val);

        if (first != nullptr) {
            item->next = first;
            first->prev = item;
        }
        first = item;
        if (amount == 0) last = item;

        amount++;
    }
    else {
        Item* item = new Item(val);
        last->next = item;
        item->prev = last;
        last = item;

        amount++;
    }
    return true;
}

bool Queue::possibleToAdd(const int n) {
    if (n <= (size - amount)) return true;
    else return false;
}

bool Queue::possibleToDelete(const int n) {
    if (n <= amount) return true;
    else return false;
}

// pop from beginning of the queue
bool Queue::deleteValue() {
    if (amount != 0) {
        if (amount == 1) {
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else {
            Item* item = first;
            first = first->next;
            delete item;

            first->prev = nullptr; //if (first != nullptr) first->prev = nullptr;
        }
        amount--;
        return true;
    }
    else return false;
}

int Queue::getAmount() const {
    return amount;
}

// one way counter printing
void Queue::print() const {
    Item* currentItem(first);

    while (currentItem) {
        cout << currentItem->getVal() << " ";
        currentItem = currentItem->next;
    }
}

// other way counter printing
void Queue::printReversed() const {
    Item* currentItem(last);

    while (currentItem) {
        cout << currentItem->getVal() << " ";
        currentItem = currentItem->prev;
    }
}

// clearing all the queue (deleting all elements in queue)
bool Queue::deleteAll() {
    if (amount == 0) return false;
    else {
        int i = 0;
        while (i != amount) { deleteValue(); }
        return true;
    }
}