#include "queue.h"
#include <iostream>

using namespace std;

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Queue::~Queue() {
    while (head != nullptr) {
        QNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void Queue::push(const string& val) {
    QNode* newNode = new QNode{val, nullptr};
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

bool Queue::pop(string& out) {
    if (head == nullptr) return false;
    QNode* temp = head;
    out = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    return true;
}

bool Queue::front(string& out) const {
    if (head == nullptr) return false;
    out = head->data;
    return true;
}

size_t Queue::getSize() const {
    size_t c = 0;
    QNode* curr = head;
    while (curr != nullptr) {
        c++;
        curr = curr->next;
    }
    return c;
}

bool Queue::isEmpty() const {
    return head == nullptr;
}

void Queue::print() const {
    if (head == nullptr) {
        cout << "[Пустая очередь]" << endl;
        return;
    }
    cout << "[ ";
    QNode* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " <- ";
        }
        curr = curr->next;
    }
    cout << " ]" << endl;
}