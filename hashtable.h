#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "array.h"
#include <string>

using namespace std;

class HashTable {
private:
    DynamicArray slots;
    DynamicArray used;
    int size;
    int count;
    int method; 

    int hash1(const string& key) const;
    int hash2(const string& key) const;
    int getHash(const string& key) const;

public:
    HashTable(int size = 1009, int method = 1);
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(const string& key);
    bool search(const string& key) const;
    bool remove(const string& key);

    int getSize() const;
    int getCount() const;
    bool isEmpty() const;
    
    int foldHash(const string& key) const;

    bool getSlot(int index, string& key, string& flag) const;
    void setSlot(int index, const string& key, const string& flag);
    void setCount(int newCount);
    int getMethod() const;

    void saveToFileText(const string& filename) const;
    void saveToFileBin(const string& filename) const;
    void loadFromFileText(const string& filename);
    void loadFromFileBin(const string& filename);
};

#endif