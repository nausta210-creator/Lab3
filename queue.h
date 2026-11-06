#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <cstddef>

using namespace std;

class Queue {
private:
    struct QNode {
        string data;
        QNode* next;
    };
    QNode* head;
    QNode* tail;

public:
    Queue();
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void push(const string& val);
    bool pop(string& out);
    bool front(string& out) const;
    size_t getSize() const; 
    bool isEmpty() const;
    void print() const;
};

#endif