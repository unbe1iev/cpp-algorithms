#include <iostream>

#include "rbt.h"

using namespace std;

template <class T>
bool compareT(Item<T>* item1, Item<T>* item2) {
    return item1->val->getVal() < item2->val->getVal();
}

template <class T>
int compareInt(Item<T>* item, int val) {
    if (item->val->getVal() == val) return 0;
    else if (item->val->getVal() < val) return 1;
    else return 2;
}

template <class T>
void RBT<T>::dInorder(Item<T>* item) {
    if (item == nullptr) return;

    dInorder(item->left);
    cout << item->val->getVal() << " ";
    dInorder(item->right);
}

template <class T>
void RBT<T>::dPreorder(Item<T>* item) {
    if (item == nullptr) return;

    cout << item->val->getVal() << " ";
    dPreorder(item->left);
    dPreorder(item->right);
}

template <class T>
void RBT<T>::displayAtOrder(bool order) { //inorder --> true ; preorder --> false
    if (order) dInorder(root);
    else dPreorder(root);
}

template <class T>
int RBT<T>::getHeight(Item<T>* item) {
    if (item == nullptr) return 0;
    else {
        int left_height = getHeight(item->left);
        int right_height = getHeight(item->right);

        if (left_height >= right_height) return left_height + 1;
        else return right_height + 1;
    }
}

template <class T>
int RBT<T>::getSize() {
    return sizeRBT;
}

template <class T>
void RBT<T>::setColor(Item<T> *item, bool color) {
    if (item == nullptr) return;
        item->color = color;
}

template <class T>
void RBT<T>::rotLeft(Item<T> *item) { // It is used to tree fixing method (fixRBT) - rotate left
    Item<T>* rchild = item->right;
    item->right = rchild->left;

    if (item->right != nullptr) item->right->parent = item;

    rchild->parent = item->parent;

    if (item->parent == nullptr) root = rchild;
    else if (item == item->parent->left) item->parent->left = rchild;
    else item->parent->right = rchild;

    rchild->left = item;
    item->parent = rchild;
}

template <class T>
void RBT<T>::rotRight(Item<T> *item) { // It is used to tree fixing method (fixRBT) - rotate right
    Item<T>* lchild = item->left;
    item->left = lchild->right;

    if (item->left != nullptr) item->left->parent = item;

    lchild->parent = item->parent;

    if (item->parent == nullptr) root = lchild;
    else if (item == item->parent->left) item->parent->left = lchild;
    else item->parent->right = lchild;

    lchild->right = item;
    item->parent = lchild;
}

template<class T>
Item<T>* RBT<T>::addItem(Item<T>* root, Item<T>* item, bool(*cmpT)(Item<T>* item1, Item<T>* item2)) {
    if (root == nullptr) return item;

    if (cmpT(item, root)) {
        root->left = addItem(root->left, item, compareT);
        root->left->parent = root;
    } else if (!cmpT(item, root)) {
        root->right = addItem(root->right, item, compareT);
        root->right->parent = root;
    }

    return root;
}

template<class T>
void RBT<T>::addItem(const T& val) {
    Item<T> *item = new Item<T>(val);
    root = addItem(root, item, compareT);
    fixRBT(item);
    sizeRBT++;
}

template <class T>
void RBT<T>::swapColors(Item<T>* a, Item<T>* b) { // Helpful method in tree to swap colors between two items in tree fixing...
	bool temp_color = a->color;
	setColor(a, b->color);
	setColor(b, temp_color);
}

template<class T>
void RBT<T>::fixRBT(Item<T>* item) { // After every one insertion we need to check if RBT properties are preserved

    // To do this we can create temporary items to figure out where are: parent, grandparent of given item
    Item<T> *parent = nullptr;
    Item<T> *grandparent = nullptr;

    while (item != root && item->color == false && item->parent->color == false) {
        parent = item->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Item<T> *uncle = grandparent->right; // uncle item of given item

            if (uncle->color == false) {
                setColor(uncle, true);
                setColor(parent, true);
                setColor(grandparent, false);
                item = grandparent;
            } else {
                if (item == parent->right) {
                    rotLeft(parent);
                    item = parent;
                    parent = item->parent;
                }

                rotRight(grandparent);
                swapColors(parent, grandparent);
                item = parent;
            }
        } else {
            Item<T> *uncle = grandparent->left; // uncle item of given item

            if (uncle->color == false) {
                setColor(uncle, true);
                setColor(parent, true);
                setColor(grandparent, false);
                item = grandparent;
            } else {
                if (item == parent->left) {
                    rotRight(parent);
                    item = parent;
                    parent = item->parent;
                }
                rotLeft(grandparent);
                swapColors(parent, grandparent);
                item = parent;
            }
        }
    }
    setColor(root, true); // After all we need to change root color to black = true [arg]
    cout << "... Tree fixed" << endl;
}

template<class T>
Item<T>* RBT<T>::findItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val)) {
	if (item == nullptr) return nullptr;
    else if (cmpInt(item, val) == 0) return item;
    else if (cmpInt(item, val) == 1) return findItem(item->right, val, compareInt);
	else return findItem(item->left, val, compareInt);
}

template<class T>
Item<T>* RBT<T>::findItem(int val) {
	return findItem(root, val, compareInt);
}

template<class T>
void RBT<T>::remOneByOne(Item<T>* item) {
    if (item == nullptr) return;

    remOneByOne(item->left);
    remOneByOne(item->right);

    delete item;
}

template<class T>
void RBT<T>::remAll() {
    remOneByOne(root);
    root = nullptr;
    sizeRBT = 0;
}

template<class T>
void RBT<T>::displayItems(Item<T>* item) {
    if (item != nullptr) {
        displayItems(item->left);

        Item<T>* p = item->parent;
        Item<T>* l = item->left;
        Item<T>* r = item->right;
        Item<T>* i = item;

        cout << "[p: " << (p != nullptr ? to_string(p->val->getVal()) : "nullptr")
        << ", l: " << (l != nullptr ? to_string(l->val->getVal()) : "nullptr")
        << ", r: " << (r != nullptr ? to_string(r->val->getVal()) : "nullptr")
        << "], val: " << (i != nullptr ? to_string(i->val->getVal()) : "nullptr")
        << ", color: " << (i->color == 1 ? "Black" : "Red")
        << ")" << endl;

        displayItems(item->right);
    }
}

template<class T>
void RBT<T>::display() {
    cout << "- - -" << endl;
    cout << "red-black tree:" << endl << "height: " << getHeight(root) << endl;
    cout << "size: " << sizeRBT << endl;
    displayItems(root);
    cout << "- - -" << endl;
}
