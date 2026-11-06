#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <cstddef>

using namespace std;

class DynamicArray {
private:
    string* data;
    size_t capacity;
    size_t length;

    void resize(size_t new_capacity);

public:
    DynamicArray(size_t initial_capacity = 4);
    ~DynamicArray();

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    void pushBack(const string& value);
    bool insertAt(size_t index, const string& value);
    bool getAt(size_t index, string& out) const;
    bool removeAt(size_t index);
    bool setAt(size_t index, const string& value);
    
    size_t getSize() const;
    size_t getCapacity() const;
    bool isEmpty() const;
    
    void print() const;
    string get(int index) const { return data[index]; }
};

#endif