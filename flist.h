#ifndef FLIST_H
#define FLIST_H

#include <string>
#include <cstddef>

using namespace std;

class ForwardList {
private:
    struct FNode {
        string data;
        FNode* next;
    };
    FNode* head;

public:
    ForwardList();
    ~ForwardList();

    ForwardList(const ForwardList&) = delete;
    ForwardList& operator=(const ForwardList&) = delete;

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