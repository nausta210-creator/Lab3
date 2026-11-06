#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <cstddef>

using namespace std;

class DoublyLinkedList {
private:
    struct DNode {
        string data;
        DNode* prev;
        DNode* next;
    };
    
    DNode* head;
    DNode* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void pushHead(const string& val);
    void pushTail(const string& val);
    bool pushBefore(const string& target, const string& val);
    bool pushAfter(const string& target, const string& val);

    bool popHead();
    bool popTail();
    bool removeValue(const string& val);
    bool removeBefore(const string& target);
    bool removeAfter(const string& target);

    bool getAt(size_t index, string& out) const;
    bool findValue(const string& val) const;

    size_t getSize() const;
    bool isEmpty() const;

    void print() const;
};

#endif