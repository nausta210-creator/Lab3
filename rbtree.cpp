#include "rbtree.h"
#include <iostream>
#include <fstream>

RBTree::RBTree() {
    nil = new RBTNode{0, BLACK, nullptr, nullptr, nullptr};
    root = nil;
}

RBTree::~RBTree() {
    destroyTree(root);
    delete nil;
}

void RBTree::destroyTree(RBTNode* node) {
    if (node != nil) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

bool RBTree::isEmpty() const {
    return root == nil;
}

void RBTree::rotateLeft(RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rotateRight(RBTNode* x) {
    RBTNode* y = x->left;
    x->left = y->right;
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::fixInsert(RBTNode* k) {
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            RBTNode* u = k->parent->parent->right;
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        } else {
            RBTNode* u = k->parent->parent->left;
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::insert(int key) {
    RBTNode* node = new RBTNode{key, RED, nil, nil, nil};
    RBTNode* y = nil;
    RBTNode* x = root;

    while (x != nil) {
        y = x;
        if (node->data == x->data) {
            delete node;
            return;
        }
        if (node->data < x->data) x = x->left;
        else x = x->right;
    }

    node->parent = y;
    if (y == nil) root = node;
    else if (node->data < y->data) y->left = node;
    else y->right = node;

    if (node->parent == nil) {
        node->color = BLACK;
        return;
    }
    if (node->parent->parent == nil) return;

    fixInsert(node);
}

bool RBTree::search(int key) const {
    RBTNode* curr = root;
    while (curr != nil) {
        if (key == curr->data) return true;
        if (key < curr->data) curr = curr->left;
        else curr = curr->right;
    }
    return false;
}

void RBTree::transplant(RBTNode* u, RBTNode* v) {
    if (u->parent == nil) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

RBTree::RBTNode* RBTree::minimum(RBTNode* node) const {
    while (node->left != nil) node = node->left;
    return node;
}

void RBTree::fixDelete(RBTNode* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBTNode* s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                s = x->parent->right;
            }
            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotateRight(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            RBTNode* s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                s = x->parent->left;
            }
            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotateLeft(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

bool RBTree::remove(int key) {
    RBTNode* z = root;
    while (z != nil && z->data != key) {
        if (key < z->data) z = z->left;
        else z = z->right;
    }
    if (z == nil) return false;

    RBTNode* y = z;
    RBTNode* x;
    Color yOriginalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) fixDelete(x);

    return true;
}

void RBTree::printHelper(RBTNode* node, string indent, bool last) const {
    if (node != nil) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }
        string sColor = (node->color == RED) ? "(RED)" : "(BLK)";
        cout << node->data << " " << sColor << endl;
        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}

void RBTree::print() const {
    if (root == nil) {
        cout << "[Пустое дерево]" << endl;
        return;
    }
    printHelper(root, "", true);
}

void RBTree::saveTextHelper(RBTNode* node, RBTNode* nil, ofstream& out) const {
    if (node != nil) {
        saveTextHelper(node->left, nil, out);
        out << node->data << endl;
        saveTextHelper(node->right, nil, out);
    }
}

void RBTree::saveToFileText(const string& filename) const {
    ofstream out(filename);
    saveTextHelper(root, nil, out);
}

void RBTree::loadFromFileText(const string& filename) {
    ifstream in(filename);
    int val;
    while (in >> val) {
        insert(val);
    }
}

void RBTree::saveBinHelper(RBTNode* node, RBTNode* nil, ofstream& out) const {
    if (node != nil) {
        saveBinHelper(node->left, nil, out);
        out.write(reinterpret_cast<const char*>(&node->data), sizeof(node->data));
        saveBinHelper(node->right, nil, out);
    }
}

void RBTree::saveToFileBin(const string& filename) const {
    ofstream out(filename, ios::binary);
    saveBinHelper(root, nil, out);
}

void RBTree::loadFromFileBin(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    int val;
    while (in.read(reinterpret_cast<char*>(&val), sizeof(val))) {
        insert(val);
    }
}