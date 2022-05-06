#include "avlt.h"

// LVR: - - -
void AVLT::dInorder() {
    if (root == nullptr) return;

    dInorder(root->leftChild);
    cout << root->val << "(" << root->bf << ") ";
    dInorder(root->rightChild);
}

void AVLT::dInorder(Item* item) {
    if (item == nullptr) return;

    dInorder(item->leftChild);
    cout << item->val << "(" << item->bf << ") ";
    dInorder(item->rightChild);
}

// VLR: - - -
void AVLT::dPreorder() {
    if (root == nullptr) return;

    cout << root->val << "(" << root->bf << ") ";
    dPreorder(root->leftChild);
    dPreorder(root->rightChild);
}

void AVLT::dPreorder(Item* item) {
    if (item == nullptr) return;

    cout << item->val << "(" << item->bf << ") ";
    dPreorder(item->leftChild);
    dPreorder(item->rightChild);
}

// LRV: - - -
void AVLT::dPostorder() {
    if (root == nullptr) return;

    dPostorder(root->leftChild);
    dPostorder(root->rightChild);
    cout << root->val << "(" << root->bf << ") ";
}

void AVLT::dPostorder(Item* item) {
    if (item == nullptr) return;

    dPostorder(item->leftChild);
    dPostorder(item->rightChild);
    cout << item->val << "(" << item->bf << ") ";
}
// - - - - -

int AVLT::getHeight(Item* item) {
    if (item == nullptr)
        return 0;
    else {
        int leftChild_height = getHeight(item->leftChild);
        int rightChild_height = getHeight(item->rightChild);
        if (leftChild_height >= rightChild_height)
            return leftChild_height + 1;
        else
            return rightChild_height + 1;
    }
}

int AVLT::getSize(Item* item) {
    if (item == nullptr)
        return 0;
    else return (getSize(item->leftChild) + 1 + getSize(item->rightChild));
}

int AVLT::getSize() {
    if (root == nullptr)
        return 0;
    else return (getSize(root->leftChild) + 1 + getSize(root->rightChild));
}

// ------- Rotations: -------

// Rotation RR
void rotateRR(Item*& root, Item* item) {
    Item* rcTemp = item->rightChild; // right child temp pointer
    Item* pTemp = item->parent; // parent temp pointer

    item->rightChild = rcTemp->leftChild;

    if (item->rightChild)
        item->rightChild->parent = item;

    rcTemp->leftChild = item;
    rcTemp->parent = pTemp;

    item->parent = rcTemp;

    if (pTemp) {
        if (pTemp->leftChild == item)
            pTemp->leftChild = rcTemp;
        else pTemp->rightChild = rcTemp;
    }
    else root = rcTemp;

    if (rcTemp->bf == -1) {
        item->bf = rcTemp->bf = 0;
    }
    else {
        item->bf = -1; rcTemp->bf = 1;
    }
}

// Rotation LL
void rotateLL(Item*& root, Item* item) {
    Item* lcTemp = item->leftChild;
    Item* pTemp = item->parent;

    item->leftChild = lcTemp->rightChild;

    if (item->leftChild)
        item->leftChild->parent = item;

    lcTemp->rightChild = item;
    lcTemp->parent = pTemp;

    item->parent = lcTemp;

    if (pTemp) {
        if (pTemp->leftChild == item)
            pTemp->leftChild = lcTemp;
        else pTemp->rightChild = lcTemp;
    }
    else root = lcTemp;

    if (lcTemp->bf == 1) {
        item->bf = lcTemp->bf = 0;
    }
    else {
        item->bf = 1;
        lcTemp->bf = -1;
    }
}

// Rotation RL:
void rotateRL(Item*& root, Item* item) {
    Item* rcTemp = item->rightChild;
    Item* lcTemp = rcTemp->leftChild;
    Item* pTemp = item->parent;

    rcTemp->leftChild = lcTemp->rightChild;
    if (rcTemp->leftChild != nullptr) rcTemp->leftChild->parent = rcTemp;

    item->rightChild = lcTemp->leftChild;
    if (item->rightChild != nullptr) item->rightChild->parent = item;

    lcTemp->leftChild = item;
    lcTemp->rightChild = rcTemp;
    item->parent = rcTemp->parent = lcTemp;
    lcTemp->parent = pTemp;

    if (pTemp) {
        if (pTemp->leftChild == item)
            pTemp->leftChild = lcTemp;
        else pTemp->rightChild = lcTemp;
    }
    else root = lcTemp;

    if (lcTemp->bf == -1)
        item->bf = 1;
    else item->bf = 0;

    if (lcTemp->bf == 1)
        rcTemp->bf = -1;
    else rcTemp->bf = 0;

    lcTemp->bf = 0;
}

// Rotation LR:
void rotateLR(Item*& root, Item* item) {
    Item* lcTemp = item->leftChild;
    Item* rcTemp = lcTemp->rightChild;
    Item* pTemp = item->parent;

    lcTemp->rightChild = rcTemp->leftChild;

    if (lcTemp->rightChild)
        lcTemp->rightChild->parent = lcTemp;

    item->leftChild = rcTemp->rightChild;

    if (item->leftChild != nullptr)
        item->leftChild->parent = item;

    rcTemp->rightChild = item;
    rcTemp->leftChild = lcTemp;
    item->parent = lcTemp->parent = rcTemp;
    rcTemp->parent = pTemp;

    if (pTemp) {
        if (pTemp->leftChild == item)
            pTemp->leftChild = rcTemp;
        else pTemp->rightChild = rcTemp;
    }
    else root = rcTemp;

    if (rcTemp->bf == 1)
        item->bf = -1;
    else item->bf = 0;

    if (rcTemp->bf == -1)
        lcTemp->bf = 1;
    else lcTemp->bf = 0;

    rcTemp->bf = 0;
}

// --------------------------

// adding with recurency:
Item* AVLT::addItem(Item* item, const int val) {
    if (item == nullptr) {
        item = new Item{};
        item->val = val;
        item->leftChild = nullptr;
        item->rightChild = nullptr;
        item->parent = nullptr;
        item->bf = 0;
        aReg = item;
    }
    else if (item->val < val) {
        item->rightChild = addItem(item->rightChild, val);
        item->rightChild->parent = item;
        if (!pReg) {
            pReg = item->rightChild->parent;
        }
    }
    else {
        item->leftChild = addItem(item->leftChild, val);
        item->leftChild->parent = item;
        if (!pReg) {
            pReg = item->leftChild->parent;
        }
    }

    return item;
}

//printing AVL tree in such a nice view:
void AVLT::displayTree(string s4, string s5, Item* v) {
    string s;

    if (v) {
        s = s4;
        if (s5 == s1)
            s[s.length() - 2] = ' ';
        displayTree(s + s3, s1, v->rightChild);

        s = s.substr(0, s4.length() - 2);
        cout << s << s5 << v->val << "(" << v->bf << ")" << endl;

        s = s4;
        if (s5 == s2)
            s[s.length() - 2] = ' ';
        displayTree(s + s3, s2, v->leftChild);
    }
}

void AVLT::addItem(const int val) {
    root = addItem(root, val); // go to recursion

    if (getSize() > 1) {
        // Balancing AVLT:
        bool x;
        Item* current;

        if (pReg->bf) pReg->bf = 0;
        else {
            if (pReg->leftChild == aReg) pReg->bf = 1;
            else pReg->bf = -1;

            current = pReg->parent;

            x = false;

            while (current) {
                if (current->bf) {
                    x = true;
                    break;
                }

                if (current->leftChild == pReg) current->bf = 1;
                else current->bf = -1;

                pReg = current;
                current = current->parent;
            }

            if (x) {
                if (current->bf == 1) {
                    if (current->rightChild == pReg) current->bf = 0;
                    else if (pReg->bf == -1) rotateLR(root, current);
                    else rotateLL(root, current);
                }
                else {
                    if (current->leftChild == pReg) current->bf = 0;
                    else if (pReg->bf == 1) rotateRL(root, current);
                    else rotateRR(root, current);
                }
            }
        }

        pReg = nullptr; // We need to flush pReg register after addition if (size of tree > 1)
    }
    //Debugging and printing:
    cout << endl << endl;
    displayTree("", "", root);
    cout << endl << endl;

    aReg = nullptr; // We need to flush aReg register after addition every time:
}
// ----------------

// adding iteratively:
void AVLT::addItem2(const int val) {
    Item* item = new Item;
    item->leftChild = item->rightChild = item->parent = nullptr;
    item->val = val;
    item->bf = 0;

    if (root == nullptr) {
        root = item;
        return;
    }

    Item* p = nullptr;
    Item* current = root;

    while (current != nullptr) {
        p = current;
        if (item->val <= current->val) current = current->leftChild;
        else current = current->rightChild;
    }
    item->parent = p;

    if (p == nullptr) root = p;
    else if (item->val <= p->val) p->leftChild = item;
    else p->rightChild = item;

    // Balancing AVLT:
    bool x;
    Item* current2;

    if (p->bf) p->bf = 0;
    else {
        if (p->leftChild == item) p->bf = 1;
        else p->bf = -1;

        current2 = p->parent;

        x = false;

        while (current2) {
            if (current2->bf) {
                x = true;
                break;
            }

            if (current2->leftChild == p) current2->bf = 1;
            else current2->bf = -1;

            p = current2;
            current2 = current2->parent;
        }

        if (x) {
            if (current2->bf == 1) {
                if (current2->rightChild == p) current2->bf = 0;
                else if (p->bf == -1) rotateLR(root, current2);
                else rotateLL(root, current2);
            }
            else {
                if (current2->leftChild == p) current2->bf = 0;
                else if (p->bf == 1) rotateRL(root, current2);
                else rotateRR(root, current2);
            }
        }
    }
    //Debugging and printing:
    cout << endl << endl;
    displayTree("", "", root);
    cout << endl << endl;
}

Item* AVLT::findItem(Item* item, int val) {
    if (item == nullptr) return nullptr;
    else if (item->val == val) return item;
    else if (item->val < val) return findItem(item->rightChild, val);
    else return findItem(item->leftChild, val);
}

Item* AVLT::findItem(int val) {
    return findItem(root, val);
}

// Method finds precursor of element:
Item* AVLT::precursorOf(Item* item) {
    Item* temp;

    if (item != nullptr) {
        if (item->leftChild) {
            item = item->leftChild;

            while (item->rightChild != nullptr)
                item = item->rightChild;

        }
        else {
            do {
                temp = item;
                item = item->parent;
            } while ((item != nullptr) && (item->rightChild != temp));
        }
    }

    return item; // returning it by pointer
}

Item* AVLT::delItem(Item*& root, Item* item) {
    // Simple temporary items to provide confusion:
    Item* a;
    Item* b;
    Item* c;

    bool x; //decision

    if (item->leftChild && item->rightChild) {
        b = delItem(root, precursorOf(item)); // we delete an item recurively
        x = false;
    }
    else {
        if (item->leftChild) {
            b = item->leftChild; item->leftChild = nullptr;
        }
        else {
            b = item->rightChild; item->rightChild = nullptr;
        }

        item->bf = 0;
        x = true;
    }

    if (b != nullptr) {
        b->parent = item->parent;
        b->leftChild = item->leftChild;

        if (b->leftChild)
            b->leftChild->parent = b;

        b->rightChild = item->rightChild;

        if (b->rightChild)
            b->rightChild->parent = b;

        b->bf = item->bf;
    }

    if (item->parent != nullptr) {
        if (item->parent->leftChild == item)
            item->parent->leftChild = b;
        else item->parent->rightChild = b;
    }
    else root = b;

    if (x) {
        c = b;
        b = item->parent;

        while (b != nullptr) {
            if (!b->bf) {
                if (b->leftChild == c)
                    b->bf = -1;
                else b->bf = 1;
                break;
            }
            else {
                if (((b->bf == 1) && (b->leftChild == c)) || ((b->bf == -1) && (b->rightChild == c))) {
                    b->bf = 0;
                    c = b; b = b->parent;
                }
                else {
                    if (b->leftChild == c)
                        a = b->rightChild;
                    else a = b->leftChild;

                    if (!a->bf) {
                        if (b->bf == 1) rotateLL(root, b);
                        else rotateRR(root, b);

                        break;
                    }
                    else if (b->bf == a->bf) {
                        if (b->bf == 1) rotateLL(root, b);
                        else rotateRR(root, b);

                        c = a; b = a->parent;
                    }
                    else {
                        if (b->bf == 1) rotateLR(root, b);
                        else rotateRL(root, b);

                        c = b->parent; b = c->parent;
                    }
                }
            }
        }
    }
    return item;
}

void AVLT::delItem(const int val) {
    Item* item = findItem(val);
    if (item == nullptr) {
        cout << "There is no such value in the tree!";
        return;
    }
    delItem(root, findItem(val));
    cout << "Item successfully deleted.";
    //Debugging and printing:
    cout << endl << endl;
    displayTree("", "", root);
    cout << endl << endl;
}

void AVLT::delOneByOne(Item* item) {
    if (item == nullptr) return;

    delOneByOne(item->leftChild);
    delOneByOne(item->rightChild);

    delete item;
}

void AVLT::delAll(Item** item) {
    delOneByOne(*item);
    *item = nullptr;
}

void AVLT::clearAll() {
    delAll(&root);
}

void AVLT::displayItems(Item* item) {
    if (item != nullptr) {
        displayItems(item->leftChild);

        Item* p = item->parent;
        Item* l = item->leftChild;
        Item* r = item->rightChild;
        Item* i = item;

        cout << "[p: " << (p != nullptr ? to_string(p->val) : "nullptr")
            << ", l: " << (l != nullptr ? to_string(l->val) : "nullptr")
            << ", r: " << (r != nullptr ? to_string(r->val) : "nullptr")
            << "], data: " << (i != nullptr ? to_string(i->val) : "nullptr")
            << ")" << endl;

        displayItems(item->rightChild);
    }
}