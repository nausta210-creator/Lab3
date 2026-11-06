#include "flist.h"
#include <iostream>

using namespace std;

ForwardList::ForwardList() {
    head = nullptr;
}

ForwardList::~ForwardList() {
    while (head != nullptr) {
        FNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void ForwardList::pushHead(const string& val) {
    FNode* new_node = new FNode{val, head};
    head = new_node;
}

void ForwardList::pushTail(const string& val) {
    FNode* new_node = new FNode{val, nullptr};
    if (head == nullptr) {
        head = new_node;
        return;
    }
    FNode* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = new_node;
}

bool ForwardList::pushAfter(const string& target, const string& val) {
    FNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr) {
        FNode* new_node = new FNode{val, curr->next};
        curr->next = new_node;
        return true;
    }
    return false;
}

bool ForwardList::pushBefore(const string& target, const string& val) {
    if (head == nullptr) return false;
    if (head->data == target) {
        pushHead(val);
        return true;
    }
    FNode* curr = head;
    while (curr->next != nullptr && curr->next->data != target) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FNode* new_node = new FNode{val, curr->next};
        curr->next = new_node;
        return true;
    }
    return false;
}

bool ForwardList::popHead() {
    if (head == nullptr) return false;
    FNode* temp = head;
    head = head->next;
    delete temp;
    return true;
}

bool ForwardList::popTail() {
    if (head == nullptr) return false;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return true;
    }
    FNode* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return true;
}

bool ForwardList::removeValue(const string& val) {
    if (head == nullptr) return false;
    if (head->data == val) {
        return popHead();
    }
    FNode* curr = head;
    while (curr->next != nullptr && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
        return true;
    }
    return false;
}

bool ForwardList::removeBefore(const string& target) {
    if (head == nullptr || head->data == target) return false;
    if (head->next != nullptr && head->next->data == target) {
        return popHead();
    }
    FNode* curr = head;
    while (curr->next != nullptr && curr->next->next != nullptr && curr->next->next->data != target) {
        curr = curr->next;
    }
    if (curr->next != nullptr && curr->next->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
        return true;
    }
    return false;
}

bool ForwardList::removeAfter(const string& target) {
    FNode* curr = head;
    while (curr != nullptr && curr->data != target) {
        curr = curr->next;
    }
    if (curr != nullptr && curr->next != nullptr) {
        FNode* to_delete = curr->next;
        curr->next = to_delete->next;
        delete to_delete;
        return true;
    }
    return false;
}

bool ForwardList::getAt(size_t index, string& out) const {
    FNode* curr = head;
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

bool ForwardList::findValue(const string& val) const {
    FNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == val) return true;
        curr = curr->next;
    }
    return false;
}

size_t ForwardList::getSize() const {
    size_t c = 0;
    FNode* curr = head;
    while (curr != nullptr) {
        c++;
        curr = curr->next;
    }
    return c;
}

bool ForwardList::isEmpty() const {
    return head == nullptr;
}

void ForwardList::print() const {
    if (head == nullptr) {
        cout << "[Пустой список]" << endl;
        return;
    }
    cout << "[ ";
    FNode* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}