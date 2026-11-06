#include "array.h"
#include <iostream>

using namespace std;

DynamicArray::DynamicArray(size_t initial_capacity) {
    if (initial_capacity == 0) {
        capacity = 4;
    } else {
        capacity = initial_capacity;
    }
    length = 0;
    data = new string[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
    data = nullptr;
    length = 0;
    capacity = 0;
}

void DynamicArray::resize(size_t new_capacity) {
    string* new_data = new string[new_capacity];
    for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void DynamicArray::pushBack(const string& value) {
    if (length == capacity) {
        resize(capacity * 2);
    }
    data[length++] = value;
}

bool DynamicArray::insertAt(size_t index, const string& value) {
    if (index > length) {
        return false;
    }
    if (length == capacity) {
        resize(capacity * 2);
    }
    for (size_t i = length; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    length++;
    return true;
}

bool DynamicArray::getAt(size_t index, string& out) const {
    if (index >= length) {
        return false;
    }
    out = data[index];
    return true;
}

bool DynamicArray::removeAt(size_t index) {
    if (index >= length) {
        return false;
    }
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    length--;
    return true;
}

bool DynamicArray::setAt(size_t index, const string& value) {
    if (index >= length) {
        return false;
    }
    data[index] = value;
    return true;
}

size_t DynamicArray::getSize() const {
    return length;
}

size_t DynamicArray::getCapacity() const {
    return capacity;
}

bool DynamicArray::isEmpty() const {
    return length == 0;
}

void DynamicArray::print() const {
    if (length == 0) {
        cout << "[Пустой массив]" << endl;
        return;
    }
    cout << "[ ";
    for (size_t i = 0; i < length; ++i) {
        cout << data[i];
        if (i + 1 < length) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}