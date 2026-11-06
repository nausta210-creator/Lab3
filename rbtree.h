#ifndef RBTREE_H
#define RBTREE_H

#include <string>
#include <fstream>

using namespace std;

class RBTree {
private:
    enum Color { RED, BLACK };

    struct RBTNode {
        int data;
        Color color;
        RBTNode* left;
        RBTNode* right;
        RBTNode* parent;
    };

    RBTNode* root;
    RBTNode* nil;

    void rotateLeft(RBTNode* x);
    void rotateRight(RBTNode* x);
    void fixInsert(RBTNode* k);
    void fixDelete(RBTNode* x);
    void transplant(RBTNode* u, RBTNode* v);
    RBTNode* minimum(RBTNode* node) const;
    void destroyTree(RBTNode* node);
    void printHelper(RBTNode* root, string indent, bool last) const;

    void saveTextHelper(RBTNode* node, RBTNode* nil, ofstream& out) const;
    void saveBinHelper(RBTNode* node, RBTNode* nil, ofstream& out) const;

public:
    RBTree();
    ~RBTree();

    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    void insert(int key);
    bool search(int key) const;
    bool remove(int key);
    bool isEmpty() const;
    void print() const;

    void saveToFileText(const string& filename) const;
    void loadFromFileText(const string& filename);
    void saveToFileBin(const string& filename) const;
    void loadFromFileBin(const string& filename);
};

#endif