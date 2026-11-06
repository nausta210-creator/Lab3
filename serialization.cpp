#include <iostream>
#include <fstream>
#include <string>
#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "rbtree.h"

using namespace std;

void saveArrayText(const DynamicArray& arr, const string& filename) {
    ofstream out(filename); // Открываем файл на запись
    for (size_t i = 0; i < arr.getSize(); ++i) {
        string val;
        arr.getAt(i, val);
        out << val << endl;
    }
}

void loadArrayText(DynamicArray& arr, const string& filename) {
    ifstream in(filename); // Открываем на чтение
    string line;
    while (getline(in, line)) {
        arr.pushBack(line);
    }
}

void saveArrayBin(const DynamicArray& arr, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = arr.getSize();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size)); //Размер массива (Превратить число (size_t) в набор байтов)
    for (size_t i = 0; i < size; ++i) {
        string val;
        arr.getAt(i, val);
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len)); //Длина строки
        out.write(val.c_str(), len); //Сама строка
    }
}

void loadArrayBin(DynamicArray& arr, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string val(len, ' '); // Создаем строку нужной длины
        in.read(&val[0], len); // Читаем саму строку
        arr.pushBack(val); // Добавляем в массив
    }
}

void saveFListText(const ForwardList& fl, const string& filename) {
    ofstream out(filename);
    for (size_t i = 0; i < fl.getSize(); ++i) {
        string val;
        fl.getAt(i, val);
        out << val << endl;
    }
}

void loadFListText(ForwardList& fl, const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        fl.pushTail(line);
    }
}

void saveFListBin(const ForwardList& fl, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = fl.getSize();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        string val;
        fl.getAt(i, val);
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(val.c_str(), len);
    }
}

void loadFListBin(ForwardList& fl, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string val(len, ' ');
        in.read(&val[0], len);
        fl.pushTail(val);
    }
}

void saveDListText(const DoublyLinkedList& dl, const string& filename) {
    ofstream out(filename);
    for (size_t i = 0; i < dl.getSize(); ++i) {
        string val;
        dl.getAt(i, val);
        out << val << endl;
    }
}

void loadDListText(DoublyLinkedList& dl, const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        dl.pushTail(line);
    }
}

void saveDListBin(const DoublyLinkedList& dl, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = dl.getSize();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        string val;
        dl.getAt(i, val);
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(val.c_str(), len);
    }
}

void loadDListBin(DoublyLinkedList& dl, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string val(len, ' ');
        in.read(&val[0], len);
        dl.pushTail(val);
    }
}

void saveStackText(Stack& s, const string& filename) {
    ofstream out(filename);
    Stack temp;
    string val;
    while (s.pop(val)) {
        temp.push(val); //Выгружаем стек во временный
    }
    while (temp.pop(val)) {
        out << val << endl; //Записываем в файл
        s.push(val); //Возвращаем обратно в оригинальный стек
    }
}

void loadStackText(Stack& s, const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        s.push(line);
    }
}

void saveStackBin(Stack& s, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = s.getSize();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    Stack temp;
    string val;
    while (s.pop(val)) {
        temp.push(val);
    }
    while (temp.pop(val)) {
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(val.c_str(), len);
        s.push(val);
    }
}

void loadStackBin(Stack& s, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string val(len, ' ');
        in.read(&val[0], len);
        s.push(val);
    }
}

void saveQueueText(Queue& q, const string& filename) {
    ofstream out(filename);
    Queue temp;
    string val;
    while (q.pop(val)) {
        temp.push(val);
    }
    while (temp.pop(val)) {
        out << val << endl;
        q.push(val);
    }
}

void loadQueueText(Queue& q, const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        q.push(line);
    }
}

void saveQueueBin(Queue& q, const string& filename) {
    ofstream out(filename, ios::binary);
    size_t size = q.getSize();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    Queue temp;
    string val;
    while (q.pop(val)) {
        temp.push(val);
    }
    while (temp.pop(val)) {
        size_t len = val.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(val.c_str(), len);
        q.push(val);
    }
}

void loadQueueBin(Queue& q, const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) return;
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string val(len, ' ');
        in.read(&val[0], len);
        q.push(val);
    }
}

void printSlots(const HashTable& ht) {
    cout << "[";
    bool first = true;
    for (int i = 0; i < ht.getSize(); ++i) {
        string key, flag;
        ht.getSlot(i, key, flag);
        if (key.empty()) continue;
        if (!first) cout << " ";
        cout << key;
        first = false;
    }
    cout << "]";
}

int main() {
    cout << "СЕРИАЛИЗАЦИЯ И ДЕСЕРИАЛИЗАЦИЯ" << endl << endl;

    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    
    cout << "1. МАССИВ" << endl;
    
    cout << "   [Текст] Сохранено: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        string v;
        arr.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveArrayText(arr, "array.txt");

    DynamicArray arrT;
    loadArrayText(arrT, "array.txt");
    cout << "   [Текст] Восстановлено: ";
    for (size_t i = 0; i < arrT.getSize(); ++i) {
        string v;
        arrT.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;

    cout << "   [Бинарный] Сохранено: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        string v;
        arr.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveArrayBin(arr, "array.bin");

    DynamicArray arrB;
    loadArrayBin(arrB, "array.bin");
    cout << "   [Бинарный] Восстановлено: ";
    for (size_t i = 0; i < arrB.getSize(); ++i) {
        string v;
        arrB.getAt(i, v);
        cout << v << " ";
    }
    cout << endl << endl;

    ForwardList fl;
    fl.pushTail("X");
    fl.pushTail("Y");
    
    cout << "2. ОДНОСВЯЗНЫЙ СПИСОК" << endl;
    
    cout << "   [Текст] Сохранено: ";
    for (size_t i = 0; i < fl.getSize(); ++i) {
        string v;
        fl.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveFListText(fl, "flist.txt");

    ForwardList flT;
    loadFListText(flT, "flist.txt");
    cout << "   [Текст] Восстановлено: ";
    for (size_t i = 0; i < flT.getSize(); ++i) {
        string v;
        flT.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;

    cout << "   [Бинарный] Сохранено: ";
    for (size_t i = 0; i < fl.getSize(); ++i) {
        string v;
        fl.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveFListBin(fl, "flist.bin");

    ForwardList flB;
    loadFListBin(flB, "flist.bin");
    cout << "   [Бинарный] Восстановлено: ";
    for (size_t i = 0; i < flB.getSize(); ++i) {
        string v;
        flB.getAt(i, v);
        cout << v << " ";
    }
    cout << endl << endl;

    DoublyLinkedList dl;
    dl.pushTail("1");
    dl.pushTail("2");
    
    cout << "3. ДВУСВЯЗНЫЙ СПИСОК" << endl;
    
    cout << "   [Текст] Сохранено: ";
    for (size_t i = 0; i < dl.getSize(); ++i) {
        string v;
        dl.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveDListText(dl, "dlist.txt");

    DoublyLinkedList dlT;
    loadDListText(dlT, "dlist.txt");
    cout << "   [Текст] Восстановлено: ";
    for (size_t i = 0; i < dlT.getSize(); ++i) {
        string v;
        dlT.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;

    cout << "   [Бинарный] Сохранено: ";
    for (size_t i = 0; i < dl.getSize(); ++i) {
        string v;
        dl.getAt(i, v);
        cout << v << " ";
    }
    cout << endl;
    saveDListBin(dl, "dlist.bin");

    DoublyLinkedList dlB;
    loadDListBin(dlB, "dlist.bin");
    cout << "   [Бинарный] Восстановлено: ";
    for (size_t i = 0; i < dlB.getSize(); ++i) {
        string v;
        dlB.getAt(i, v);
        cout << v << " ";
    }
    cout << endl << endl;

    Stack s;
    s.push("First");
    s.push("Second");
    
    cout << "4. СТЕК" << endl;
    
    cout << "   [Текст] Сохранено: (элементы стека)" << endl;
    saveStackText(s, "stack.txt");

    Stack sT;
    loadStackText(sT, "stack.txt");
    cout << "   [Текст] Восстановлено: ";
    string val;
    while (sT.pop(val)) {
        cout << val << " ";
    }
    cout << endl;

    cout << "   [Бинарный] Сохранено: (элементы стека)" << endl;
    saveStackBin(s, "stack.bin");

    Stack sB;
    loadStackBin(sB, "stack.bin");
    cout << "   [Бинарный] Восстановлено: ";
    while (sB.pop(val)) {
        cout << val << " ";
    }
    cout << endl << endl;

    Queue q;
    q.push("One");
    q.push("Two");
    
    cout << "5. ОЧЕРЕДЬ" << endl;
    
    cout << "   [Текст] Сохранено: (элементы очереди)" << endl;
    saveQueueText(q, "queue.txt");

    Queue qT;
    loadQueueText(qT, "queue.txt");
    cout << "   [Текст] Восстановлено: ";
    while (qT.pop(val)) {
        cout << val << " ";
    }
    cout << endl;

    cout << "   [Бинарный] Сохранено: (элементы очереди)" << endl;
    saveQueueBin(q, "queue.bin");

    Queue qB;
    loadQueueBin(qB, "queue.bin");
    cout << "   [Бинарный] Восстановлено: ";
    while (qB.pop(val)) {
        cout << val << " ";
    }
    cout << endl << endl;

    HashTable ht(11, 1);
    ht.insert("apple");
    ht.insert("banana");
    ht.insert("cherry");

    cout << "6. ХЕШ-ТАБЛИЦА" << endl;

    cout << "   [Текст] Сохранено: ";
    printSlots(ht);
    cout << endl;
    ht.saveToFileText("hashtable.txt");

    HashTable htT(11, 1);                    
    htT.loadFromFileText("hashtable.txt");  
    cout << "   [Текст] Восстановлено: ";
    printSlots(htT);
    cout << endl;
    cout << "   [Текст] size=" << htT.getSize() << " count=" << htT.getCount() << endl;

    cout << "   [Бинарный] Сохранено: ";
    printSlots(ht);
    cout << endl;
    ht.saveToFileBin("hashtable.bin");

    HashTable htB(11, 1);                    
    htB.loadFromFileBin("hashtable.bin");   
    cout << "   [Бинарный] Восстановлено: ";
    printSlots(htB);
    cout << endl;
    cout << "   [Бинарный] size=" << htB.getSize() << " count=" << htB.getCount() << endl;
    cout << endl;

    RBTree tree;
    tree.insert(10); tree.insert(20); tree.insert(5); tree.insert(15);
    
    cout << "7. КРАСНО-ЧЁРНОЕ ДЕРЕВО" << endl;
    
    cout << "   [Текст] Сохранено: 10 20 5 15 (в порядке вставки)" << endl;
    tree.saveToFileText("tree.txt");

    RBTree treeT;
    treeT.loadFromFileText("tree.txt");
    
    cout << "   [Текст] Восстановлено: ";
    treeT.print(); 
    cout << endl;

    cout << "   [Бинарный] Сохранено: 10 20 5 15" << endl;
    tree.saveToFileBin("tree.bin");

    RBTree treeB;
    treeB.loadFromFileBin("tree.bin");
    
    cout << "   [Бинарный] Восстановлено: ";
    treeB.print(); 
    cout << endl;

    return 0;
}