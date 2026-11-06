#include "stack.h"
#include <iostream>

using namespace std;

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (top != nullptr) {
        SNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(const string& val) {
    SNode* newNode = new SNode{val, top};
    top = newNode;
}

bool Stack::pop(string& out) {
    if (top == nullptr) return false;
    SNode* temp = top;
    out = temp->data;
    top = top->next;
    delete temp;
    return true;
}

bool Stack::peek(string& out) const {
    if (top == nullptr) return false;
    out = top->data;
    return true;
}

size_t Stack::getSize() const {
    size_t c = 0;
    SNode* curr = top;
    while (curr != nullptr) {
        c++;
        curr = curr->next;
    }
    return c;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::print() const {
    if (top == nullptr) {
        cout << "[Пустой стек]" << endl;
        return;
    }
    cout << "[ ";
    SNode* curr = top;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}