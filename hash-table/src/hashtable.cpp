#include "hashtable.h"

template <class T>
bool List<T>::addItem_first(Reg reg) {
	Item<T>* item = new Item<T>{ reg };

	if (first != nullptr) {
		item->next = first;
		first->prev = item;
	}
	first = item;
	if (amount == 0) last = first;

	amount++;
	return true;
}

template <class T>
bool List<T>::addItem_last(Reg reg) {
	if (amount == 0) return addItem_first(reg);
	else {
		Item<T>* item = new Item<T>{ reg };
		last->next = item;
		item->prev = last;
		last = item;

		amount++;
		return true;
	}
}

template <class T>
Item<T>* List<T>::getItemById(int id) const {
	if (id < 0 || id > amount) return nullptr;
	else if (id == 0) return first;
	else if (id == amount - 1) return last;

	Item<T>* item = first;

	int i = 0;
	while (i != id) { item = item->next; i++; }

	return item;
}

template <class T>
int List<T>::getAmount() {
    return amount;
}

template <class T>
bool List<T>::delItem_first() {
	if (amount != 0) {
		if (amount == 1) delete first;
		else {
			Item<T>* item = first;
			first = first->next;
			delete item;

			if (first != nullptr) first->prev = nullptr;
		}
		amount--;
		return true;
	}
	else return false;
}

template <class T>
bool List<T>::delItem_last() {
	if (amount != 0) {
		if (amount == 1) return delItem_first();
		else {
			Item<T>* item = last;
			last = last->prev;
			last->next = nullptr;
			delete item;

			amount--;
			return true;
		}
	}
	else return false;
}

template <class T>
bool List<T>::findAndDelete(string key) {
    bool deleted = false;
	for (int i = 0; i < amount; i++) {
		if (getItemById(i)->reg.key == key) {
			if (i == 0) delItem_first();
			else if (i == amount - 1) delItem_last();
			else {
				getItemById(i - 1)->next = getItemById(i + 1);
				getItemById(i + 1)->prev = getItemById(i - 1);

				delete getItemById(i);
				amount--;
			}
			deleted = true;
		}
	}
	if (deleted) return true;
    else return false;
}

template <class T>
bool List<T>::clearAll() {
	if (amount == 0) return false;
	else {
		while (amount != 0) delItem_last();
		return true;
	}
}

template <class T>
void HashTable<T>::add(Reg reg) {
    int new_id = getHash(reg.key);

    if (l[new_id]->getAmount() == 0) {
        l[new_id]->addItem_last(reg);
        usage++;
        if (usage > limit*capacity) reHashAll();

    } else {
        l[new_id]->addItem_last(reg);
    }
}

template <class T>
void HashTable<T>::setHashTable() {
    l = new List<T>*[capacity];

    for (int i=0; i<capacity; i++)
        l[i] = new List<T>;

    Reg reg;
    reg.val = 0;
    add(reg);
}

template <class T>
int HashTable<T>::getHash(string key) {
    int sum;
    for (int i=0; i<(int)key.length(); i++)
        sum += pow(key[i]*31, key.length()-(i+1));

    return abs(sum%capacity);
}

template <class T>
void HashTable<T>::reHashAll() {
    capacity *= factor;
    List<T>** temp = new List<T>*[capacity];

    for (int k=0; k<capacity; k++)
        temp[k] = new List<T>;

    int new_id;

    for (int i = 0; i < (capacity/2); i++) {
        for (int j = 0; j < l[i]->getAmount(); j++) {
            new_id = getHash(l[i]->getItemById(j)->reg.key);
            temp[new_id]->addItem_last(l[i]->getItemById(j)->reg);
        }
    }

    l = temp;

    //Calculating usage after all:
    usage = 0;
    for (int i = 0; i < capacity; i++) {
        if (l[i]->getAmount() > 0) usage++;
    }
}

template <class T>
void HashTable<T>::printStats() {
    int list_min_size = l[0]->getAmount();
    int list_max_size = 0;
    int non_null_lists = 0;
    float list_avg_size = 0;
    int sum = 0;

    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < l[i]->getAmount(); j++) {
            sum++;
        }

        if (l[i]->getAmount() > list_max_size) list_max_size = l[i]->getAmount();
        if ((l[i]->getAmount() != 0) &&  (l[i]->getAmount()< list_min_size)) list_min_size = l[i]->getAmount();
        if (l[i]->getAmount() > 0) non_null_lists++;
    }

    list_avg_size = sum/capacity;

    cout << "hash table:" << endl << "\tusage: " << usage << "/" << capacity << endl;
    cout << "\ttable:" << endl << "\t{" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << "\t\t"; cout << "(" << l[i]->getAmount() << "): ";
            for (int j = 0; j < l[i]->getAmount(); j++) {
                    cout << l[i]->getItemById(j)->reg.key << " -> " << l[i]->getItemById(j)->reg.val << "; ";
            }
            cout << endl;
        }
    cout << "\t}" << endl << "\n\tstats:" << endl;

    cout << "\t\tlist min size (except emptiness): " << list_min_size << endl;
    cout << "\t\tlist max size: " << list_max_size << endl;
    cout << "\t\tnon null lists: " << non_null_lists << endl;
    cout << "\t\tlist avg size: " << list_avg_size << endl;
}

template <class T>
Item<T>* HashTable<T>::findElement(string key) {
    Item<T>* element;

    int j = 0;
    for (int i = 0; i < capacity; i++) {
        element = l[i]->first;

        j = 0;
        while (j < l[i]->getAmount()) {
            if (element->reg.key == key) return element;
            element = element->next;
            j++;
        }
    }
    return nullptr;
}

template <class T>
bool HashTable<T>::remElement(string key) {
    bool matches = false;
    for (int i = 0; i < capacity; i++) {
        if (l[i]->findAndDelete(key)) {
            if (l[i]->getAmount() == 0) usage--;
            matches = true;
        }
    }
    return matches;
}

template <class T>
bool HashTable<T>::clearAll() {
    bool smth_cleared = false;

    for (int i = 0; i < capacity; i++) {
        if (l[i]->clearAll()) smth_cleared = true;
    }
    usage = 0;
    capacity = 1;

    return smth_cleared;
}
