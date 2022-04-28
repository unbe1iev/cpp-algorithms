#include "bst.h"

template <class T>
void BST<T>::dInorder(Item<T>* item) {
    if (item == nullptr) return;

    dInorder(item->left);
    cout << item->val->getVal() << " ";
    dInorder(item->right);
}

template <class T>
void BST<T>::dPreorder(Item<T>* item) {
    if (item == nullptr) return;

    cout << item->val->getVal() << " ";
    dPreorder(item->left);
    dPreorder(item->right);
}

template <class T>
void BST<T>::displayAtOrder(bool order) { //inorder --> true ; preorder --> false
    if (order) dInorder(root);
    else dPreorder(root);
}

template <class T>
int BST<T>::getHeight(Item<T>* item) {
    if (item == nullptr)
        return 0;
    else {
        int left_height = getHeight(item->left);
        int right_height = getHeight(item->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

template <class T>
int BST<T>::getSize(Item<T>* item) {
    if (item == nullptr)
        return 0;
    else
        return (getSize(item->left) + 1 + getSize(item->right));
}

template<class T>
Item<T>* BST<T>::addItem(Item<T>* item, const T& val, bool(*cmpT)(Item<T>* item, const T& val)) {
    if (item == nullptr) {
		item = new Item<T>{};
		item->val = val;
		item->left = nullptr;
		item->right = nullptr;
		item->parent = nullptr;
	} else if (cmpT(item, val)) {
		item->right = addItem(item->right, val, compareT);
		item->right->parent = item;
	} else {
		item->left = addItem(item->left, val, compareT);
		item->left->parent = item;
	}

    return item;
}

template<class T>
void BST<T>::addItem(const T& val) {
	root = addItem(root, val, compareT);
}

template<class T>
Item<T>* BST<T>::findItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val)) {
	if (item == nullptr) return nullptr;
    else if (cmpInt(item, val) == 0) return item;
    else if (cmpInt(item, val) == 1) return findItem(item->right, val, compareInt);
	else return findItem(item->left, val, compareInt);
}

template<class T>
Item<T>* BST<T>::findItem(int val) {
	return findItem(root, val, compareInt);
}

template<class T>
void BST<T>::remOneByOne(Item<T>* item) {
    if (item == nullptr) return;

    remOneByOne(item->left);
    remOneByOne(item->right);

    delete item;
}

template<class T>
void BST<T>::remAll(Item<T>** item) {
    remOneByOne(*item);
    *item = nullptr;
}

template<class T>
void BST<T>::clearAll() {
    remAll(&root);
}

template<class T>
void BST<T>::displayItems(Item<T>* item) {
    if (item != nullptr) {
        displayItems(item->left);

        Item<T>* p = item->parent;
        Item<T>* l = item->left;
        Item<T>* r = item->right;
        Item<T>* i = item;

        cout << "[p: " << (p != nullptr ? to_string(p->val->getVal()) : "nullptr")
        << ", l: " << (l != nullptr ? to_string(l->val->getVal()) : "nullptr")
        << ", r: " << (r != nullptr ? to_string(r->val->getVal()) : "nullptr")
        << "], data: " << (i != nullptr ? to_string(i->val->getVal()) : "nullptr")
        << ")" << endl;

        displayItems(item->right);
    }
}

template<class T>
void BST<T>::display() {
    cout << "- - -" << endl;
    cout << "binary search tree:" << endl << "height: " << getHeight(root) << endl;
    cout << "size: " << getSize(root) << endl;
    displayItems(root);
    cout << "- - -" << endl;
}

template <class T>
Item<T>* BST<T>::remItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val)) {
    if (item == nullptr) return item;

    //Case that it has no children:
    if (cmpInt(item, val) == 2) {
        item->left = remItem(item->left, val, compareInt);
        return item;
    } else if (cmpInt(item, val) == 1) {
        item->right = remItem(item->right, val, compareInt);
        return item;
    }

    //Case that it has one child:
    if (item->right == nullptr) {
        Item<T>* temp = item->left;
        delete item;
        return temp;
    } else if (item->left == nullptr) {
        Item<T>* temp = item->right;
        delete item;
        return temp;
    }

    //Case that it has two children:
    else {
        Item<T>* succParent = item;
        Item<T>* succ = item->right;

        while (succ->left != nullptr) { //while loop to find successor of subtree
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != item) succParent->left = succ->right;
        else succParent->right = succ->right; //Case- when there is no succ, then assign


        item->val = succ->val; // need to copy succ to curr item (root)

        delete succ;
        return item;
    }
}

template <class T>
void BST<T>::rem(int val) {
    root = remItem(root, val, compareInt);
}
