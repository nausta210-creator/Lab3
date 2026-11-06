#include "dlist.h"
#include <iostream>

using namespace std;

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
    while (head != nullptr) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void DoublyLinkedList::pushHead(const string& val) {
    DNode* new_node = new DNode{val, nullptr, head};
    if (head != nullptr) {
        head->prev = new_node;
    } else {
        tail = new_node;
    }
    head = new_node;
}

void DoublyLinkedList::pushTail(const string& val) {
    DNode* new_node = new DNode{val, tail, nullptr};
    if (tail != nullptr) {
        tail->next = new_node;
    } else {
        head = new_node;
    }
    tail = new_node;
}

bool DoublyLinkedList::pushAfter(const string& target, const string& val) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        DNode* new_node = new DNode{val, curr, curr->next};
        if (curr->next != nullptr) {
            curr->next->prev = new_node;
        } else {
            tail = new_node;
        }
        curr->next = new_node;
        return true;
    }
    return false;
}

bool DoublyLinkedList::pushBefore(const string& target, const string& val) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        DNode* new_node = new DNode{val, curr->prev, curr};
        if (curr->prev != nullptr) {
            curr->prev->next = new_node;
        } else {
            head = new_node;
        }
        curr->prev = new_node;
        return true;
    }
    return false;
}

bool DoublyLinkedList::popHead() {
    if (head == nullptr) return false;
    DNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    return true;
}

bool DoublyLinkedList::popTail() {
    if (tail == nullptr) return false;
    DNode* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    return true;
}

bool DoublyLinkedList::removeValue(const string& val) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != val) {
        curr = curr->next;
    }
    if (curr == nullptr) return false;

    if (curr == head) {
        return popHead();
    } else if (curr == tail) {
        return popTail();
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        return true;
    }
}

bool DoublyLinkedList::removeBefore(const string& target) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->prev != nullptr) {
        DNode* to_delete = curr->prev;
        if (to_delete == head) {
            return popHead();
        } else {
            to_delete->prev->next = curr;
            curr->prev = to_delete->prev;
            delete to_delete;
            return true;
        }
    }
    return false;
}

bool DoublyLinkedList::removeAfter(const string& target) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->next != nullptr) {
        DNode* to_delete = curr->next;
        if (to_delete == tail) {
            return popTail();
        } else {
            curr->next = to_delete->next;
            to_delete->next->prev = curr;
            delete to_delete;
            return true;
        }
    }
    return false;
}

bool DoublyLinkedList::getAt(size_t index, string& out) const {
    DNode* curr = head;
    size_t currIdx = 0;
    while (curr != nullptr) {
        if (currIdx == index) {
            out = curr->data;
            return true;
        }
        curr = curr->next;
        currIdx++;
    }
    return false; 
}

bool DoublyLinkedList::findValue(const string& val) const {
    DNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == val) return true;
        curr = curr->next;
    }
    return false;
}

size_t DoublyLinkedList::getSize() const {
    size_t c = 0;
    DNode* curr = head;
    while (curr != nullptr) {
        c++;
        curr = curr->next;
    }
    return c;
}

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

void DoublyLinkedList::print() const {
    if (head == nullptr) {
        cout << "[Пустой список]" << endl;
        return;
    }
    cout << "[ ";
    DNode* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " <=> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}