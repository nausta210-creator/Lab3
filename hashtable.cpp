#include "hashtable.h"

HashTable::HashTable(int size, int method) : slots(size), used(size) {
    this->size = size;
    this->count = 0;
    this->method = method;
    
    for (int i = 0; i < size; ++i) {
        slots.pushBack("");
        used.pushBack("0");
    }
}

HashTable::~HashTable() {}

int HashTable::hash1(const string& key) const {
    unsigned long long h = 14695981039346656037ULL;
    for (size_t i = 0; i < key.size(); ++i) {
        h ^= (unsigned char)key[i];
        h *= 1099511628211ULL;
    }
    return (int)(h % size);
}

int HashTable::hash2(const string& key) const {
    unsigned long long h = 5381;
    for (size_t i = 0; i < key.size(); ++i) {
        h = ((h << 5) + h) + (unsigned char)key[i];
    }
    return (int)(h % (size - 1)) + 1;
}

int HashTable::foldHash(const string& key) const {
    int sum = 0; 
    string part = "";
    for (size_t i = 0; i < key.size(); ++i) {
        part += key[i];
        if (part.size() == 3) {
            sum += stoll(part);
            part = "";
        }
    }
    if (!part.empty()) sum += stoll(part);
    return (int)(sum % size);
}

int HashTable::getHash(const string& key) const {
    if (method == 2) {
        return foldHash(key);
    }
    return hash1(key);
}

bool HashTable::insert(const string& key) {
    if (count >= size) return false;

    int idx = getHash(key);
    int step = (method == 2) ? hash2(key) : 1;

    for (int i = 0; i < size; ++i) {
        int cur = (idx + i * step) % size;
        if (used.get(cur) == "0") {       
            slots.setAt(cur, key);       
            used.setAt(cur, "1");        
            count++;
            return true;
        }
        if (slots.get(cur) == key) return false; 
    }
    return false;
}

bool HashTable::search(const string& key) const {
    int idx = getHash(key);
    int step = (method == 2) ? hash2(key) : 1;

    for (int i = 0; i < size; ++i) {
        int cur = (idx + i * step) % size;
        if (used.get(cur) == "0") return false;  
        if (slots.get(cur) == key) return true;  
    }
    return false;
}

bool HashTable::remove(const string& key) {
    int idx = getHash(key);
    int step = (method == 2) ? hash2(key) : 1;

    for (int i = 0; i < size; ++i) {
        int cur = (idx + i * step) % size;
        if (used.get(cur) == "0") return false;  
        if (slots.get(cur) == key) {             
            slots.setAt(cur, "");                
            used.setAt(cur, "0");                
            count--;
            return true;
        }
    }
    return false;
}

#include <fstream>

bool HashTable::getSlot(int index, string& key, string& flag) const {
    if (index < 0 || index >= size) return false;
    slots.getAt(index, key);
    used.getAt(index, flag);
    return true;
}

void HashTable::setSlot(int index, const string& key, const string& flag) {
    if (index < 0 || index >= size) return;
    slots.setAt(index, key);
    used.setAt(index, flag);
}

void HashTable::setCount(int newCount) { count = newCount; }

int HashTable::getMethod() const { return method; }

void HashTable::saveToFileText(const string& filename) const {
    ofstream out(filename);
    if (!out) return;
    out << size << " " << count << " " << method << endl;
    for (int i = 0; i < size; ++i) {
        string key, flag;
        slots.getAt(i, key);
        used.getAt(i, flag);
        out << (key.empty() ? "-" : key) << " " << flag << endl;
    }
}

void HashTable::loadFromFileText(const string& filename) {
    ifstream in(filename);
    if (!in) return;
    int newSize, newCount, newMethod;
    in >> newSize >> newCount >> newMethod;

    if (newSize != size) return; 

    count = newCount;
    method = newMethod;

    string key, flag;
    for (int i = 0; i < size; ++i) {
        in >> key >> flag;
        slots.setAt(i, key == "-" ? "" : key);
        used.setAt(i, flag);
    }
}

void HashTable::saveToFileBin(const string& filename) const {
    ofstream out(filename, ios::binary);
    if (!out) return;
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    out.write(reinterpret_cast<const char*>(&method), sizeof(method));
    for (int i = 0; i < size; ++i) {
        string key, flag;
        slots.getAt(i, key);
        used.getAt(i, flag);
        size_t len = key.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(key.c_str(), len);
        out.write(flag.c_str(), 1);
    }
}

void HashTable::loadFromFileBin(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    int newSize, newCount, newMethod;
    in.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    in.read(reinterpret_cast<char*>(&newCount), sizeof(newCount));
    in.read(reinterpret_cast<char*>(&newMethod), sizeof(newMethod));

    if (newSize != size) return;

    count = newCount;
    method = newMethod;

    for (int i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string key(len, ' ');
        in.read(&key[0], len);
        char flag;
        in.read(&flag, 1);
        slots.setAt(i, key);
        used.setAt(i, string(1, flag));
    }
}

int HashTable::getSize() const { return size; }
int HashTable::getCount() const { return count; }
bool HashTable::isEmpty() const { return count == 0; }