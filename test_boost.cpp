#define BOOST_TEST_MODULE AllStructuresTest
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "rbtree.h"

using namespace std;

BOOST_AUTO_TEST_CASE(DynamicArrayTest_BasicOperations) { //Тест-функция
    DynamicArray arr;
    BOOST_TEST(arr.isEmpty() == true); //Результат работы
    
    arr.pushBack("A"); arr.pushBack("B"); arr.pushBack("C"); arr.pushBack("D");
    arr.pushBack("E"); 
    
    BOOST_TEST(arr.getSize() == 5);
    string val;
    BOOST_TEST(arr.getAt(0, val) == true);
    BOOST_TEST(val == "A");
    
    BOOST_TEST(arr.setAt(1, "B2") == true);
    BOOST_TEST(arr.getAt(1, val) == true);
    BOOST_TEST(val == "B2");
    
    BOOST_TEST(arr.insertAt(2, "X") == true);
    BOOST_TEST(arr.removeAt(0) == true);
    
    BOOST_TEST(arr.getAt(100, val) == false);
    BOOST_TEST(arr.removeAt(100) == false);
}

BOOST_AUTO_TEST_CASE(ForwardListTest_Operations) {
    ForwardList fl;
    BOOST_TEST(fl.isEmpty() == true);
    
    fl.pushHead("A"); fl.pushTail("B"); fl.pushTail("C");
    BOOST_TEST(fl.getSize() == 3);
    BOOST_TEST(fl.findValue("B") == true);
    
    fl.pushAfter("A", "A2");
    fl.pushBefore("C", "B2");
    
    BOOST_TEST(fl.popHead() == true);
    BOOST_TEST(fl.popTail() == true);
    BOOST_TEST(fl.removeValue("A2") == true);
    BOOST_TEST(fl.removeValue("NotExist") == false);
    
    string val;
    BOOST_TEST(fl.getAt(0, val) == true);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListTest_Operations) {
    DoublyLinkedList dl;
    dl.pushHead("A"); dl.pushTail("C"); dl.pushBefore("C", "B");
    BOOST_TEST(dl.getSize() == 3);
    
    BOOST_TEST(dl.removeAfter("A") == true);
    BOOST_TEST(dl.getSize() == 2);
    
    BOOST_TEST(dl.popHead() == true);
    BOOST_TEST(dl.popTail() == true);
    BOOST_TEST(dl.popHead() == false);
}

BOOST_AUTO_TEST_CASE(StackTest_PushPop) {
    Stack s;
    BOOST_TEST(s.isEmpty() == true);
    s.push("bottom"); s.push("top");
    string val;
    BOOST_TEST(s.peek(val) == true);
    BOOST_TEST(val == "top");
    BOOST_TEST(s.pop(val) == true);
    BOOST_TEST(val == "top");
    BOOST_TEST(s.getSize() == 1);
    s.pop(val);
    BOOST_TEST(s.pop(val) == false);
    BOOST_TEST(s.peek(val) == false);
}

BOOST_AUTO_TEST_CASE(QueueTest_PushPop) {
    Queue q;
    BOOST_TEST(q.isEmpty() == true);
    q.push("first"); q.push("second");
    string val;
    BOOST_TEST(q.front(val) == true);
    BOOST_TEST(val == "first");
    BOOST_TEST(q.pop(val) == true);
    BOOST_TEST(val == "first");
    q.pop(val);
    BOOST_TEST(q.pop(val) == false);
    BOOST_TEST(q.front(val) == false);
}

BOOST_AUTO_TEST_CASE(HashTableTest_InsertSearchRemove) {
    HashTable ht(10, 1); 
    BOOST_TEST(ht.isEmpty() == true); 
    BOOST_TEST(ht.insert("key1") == true); BOOST_TEST(ht.insert("key2") == true);
    
    for(int i = 3; i <= 10; i++) {
        BOOST_TEST(ht.insert("key" + to_string(i)) == true);
    }
    BOOST_TEST(ht.insert("overflow") == false); 
    
    BOOST_TEST(ht.search("key1") == true); 
    BOOST_TEST(ht.search("unknown") == false); 
    BOOST_TEST(ht.remove("key1") == true); 
    BOOST_TEST(ht.search("key1") == false); 
}

BOOST_AUTO_TEST_CASE(RBTreeTest_InsertSearchRemove) {
    RBTree tree;
    BOOST_TEST(tree.isEmpty() == true);
    
    for (int i = 1; i <= 20; ++i) tree.insert(i);
    BOOST_TEST(tree.search(10) == true);
    BOOST_TEST(tree.search(99) == false);
    
    BOOST_TEST(tree.remove(10) == true);
    BOOST_TEST(tree.remove(15) == true);
    BOOST_TEST(tree.remove(99) == false);
    BOOST_TEST(tree.search(10) == false);
}

BOOST_AUTO_TEST_CASE(CoverageBoostTest_PrintAndEdgeCases) {
    DynamicArray arr(0); arr.print(); arr.pushBack("A"); arr.print(); 
    Stack s; s.print(); s.push("S"); s.print(); s.getSize();
    Queue q; q.print(); q.push("Q"); q.print(); q.getSize();
    RBTree tree; tree.print(); tree.insert(5); tree.print();
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListTest_FullCoverage) {
    DoublyLinkedList dl;
    dl.print(); 
    dl.pushTail("1"); dl.pushTail("2"); dl.pushTail("3"); dl.print(); 
    
    BOOST_TEST(dl.pushAfter("2", "2.5") == true); BOOST_TEST(dl.pushAfter("99", "0") == false);
    BOOST_TEST(dl.pushBefore("2", "1.5") == true); BOOST_TEST(dl.pushBefore("99", "0") == false);
    
    BOOST_TEST(dl.removeValue("2.5") == true); BOOST_TEST(dl.removeValue("99") == false);
    BOOST_TEST(dl.removeBefore("3") == true); BOOST_TEST(dl.removeBefore("1") == false); 
    BOOST_TEST(dl.removeAfter("1") == true); BOOST_TEST(dl.removeAfter("3") == false); 
    
    string val;
    BOOST_TEST(dl.getAt(1, val) == true); BOOST_TEST(dl.getAt(100, val) == false);
    BOOST_TEST(dl.findValue("3") == true); BOOST_TEST(dl.findValue("99") == false);
}

BOOST_AUTO_TEST_CASE(ForwardListTest_FullCoverage) {
    ForwardList fl;
    fl.print();
    fl.pushHead("1"); fl.pushTail("2"); fl.pushTail("3"); fl.print();
    
    BOOST_TEST(fl.pushAfter("99", "0") == false); BOOST_TEST(fl.pushBefore("99", "0") == false);
    BOOST_TEST(fl.removeBefore("3") == true); BOOST_TEST(fl.removeBefore("1") == false);
    BOOST_TEST(fl.removeAfter("1") == true); BOOST_TEST(fl.removeAfter("3") == false);
    
    string out;
    BOOST_TEST(fl.getAt(100, out) == false); 
}

BOOST_AUTO_TEST_CASE(HashTableTest_FoldHashMethod) {
    HashTable ht(10, 2); 
    
    BOOST_TEST(ht.insert("123456789") == true);
    BOOST_TEST(ht.insert("123456789") == false); 
    
    BOOST_TEST(ht.search("123456789") == true);
    BOOST_TEST(ht.search("000") == false);
    
    BOOST_TEST(ht.remove("123456789") == true);
    BOOST_TEST(ht.remove("000") == false);
    
    BOOST_TEST(ht.getSize() == 10);
    BOOST_TEST(ht.getCount() == 0);
}

BOOST_AUTO_TEST_CASE(RBTreeTest_FullCoverage) {
    RBTree tree;
    BOOST_TEST(tree.isEmpty() == true);

    for (int i = 1; i <= 15; ++i) tree.insert(i);
    for (int i = -1; i >= -15; --i) tree.insert(i);
    
    tree.insert(100); tree.insert(50); tree.insert(150); 
    tree.insert(25); tree.insert(75); tree.insert(125);
    tree.insert(10);

    BOOST_TEST(tree.search(50) == true);
    BOOST_TEST(tree.search(999) == false);

    tree.remove(999);
    tree.remove(1);
    tree.remove(-1);
    tree.remove(100);
    tree.remove(50);
    tree.remove(150);

    BOOST_TEST(tree.search(10) == true);
    tree.print();
}