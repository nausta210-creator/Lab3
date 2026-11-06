#ifndef STACK_H
#define STACK_H

#include <string>
#include <cstddef>

using namespace std;

class Stack {
private:
    struct SNode {
        string data;
        SNode* next;
    };
    SNode* top;

public:
    Stack();
    ~Stack();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const string& val);
    bool pop(string& out);
    bool peek(string& out) const;
    size_t getSize() const; 
    bool isEmpty() const;
    void print() const;
};

#endif