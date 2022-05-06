#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Item {
public:
    int val;
    int bf; // Can be only in {-1, 0, 1}

    Item* leftChild;
    Item* rightChild;
    Item* parent;
};

class AVLT {
private:
    Item* root = nullptr;
    Item* pReg = nullptr; // parent register to remember parent of inserteed node in recurency
    Item* aReg = nullptr; // node that has been added in result of recurency adding - actual node
public:

    string s1, s2, s3;      // global strings for symbols in AVL tree printing
    //int arr;

    // Adding methods (recursively & iteratively way):
    void addItem(const int val); // assistance to recursively for adding
    void addItem2(const int val); // iteratively for add
    Item* addItem(Item* item, const int val); // recursively for adding

    // Displaying section methods:
    void dInorder(); // LVR
    void dPreorder(); // VLR
    void dPostorder(); // LRV
    void dInorder(Item* item);
    void dPreorder(Item* item);
    void dPostorder(Item* item);
    void displayItems(Item* item);
    void displayTree(std::string s4, std::string s5, Item* v);

    // We need to find an item in delete section at first point:
    Item* findItem(Item* item, int val);
    Item* findItem(int val);

    // Deletion methods:
    Item* precursorOf(Item* item); // Finds precursor of an item in deletion
    Item* delItem(Item*& root, Item* item); // Deletion of specific item
    void delItem(const int val); // Deletion of specific val
    void delOneByOne(Item* item); // Used by delAll() to recurively all deletion
    void delAll(Item** item);
    void clearAll(); // To clear everything...

    // Rest of helpful methods:
    int getHeight(Item* item);
    int getSize();
    int getSize(Item* item);
};

