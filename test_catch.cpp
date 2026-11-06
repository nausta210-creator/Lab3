#include <catch2/catch_test_macros.hpp>
#include <string>
#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "rbtree.h"

using namespace std;

TEST_CASE("DynamicArray BasicOperations", "[array]") {
    DynamicArray arr;
    REQUIRE(arr.isEmpty() == true); //Условие
    
    arr.pushBack("A"); arr.pushBack("B"); arr.pushBack("C"); arr.pushBack("D"); arr.pushBack("E"); 
    REQUIRE(arr.getSize() == 5);
    
    string val;
    REQUIRE(arr.getAt(0, val) == true);
    REQUIRE(val == "A");
    
    REQUIRE(arr.setAt(1, "B2") == true);
    REQUIRE(arr.getAt(1, val) == true);
    REQUIRE(val == "B2");
    
    REQUIRE(arr.insertAt(2, "X") == true);
    REQUIRE(arr.removeAt(0) == true);
    
    REQUIRE(arr.getAt(100, val) == false);
    REQUIRE(arr.removeAt(100) == false);
}

TEST_CASE("ForwardList Operations", "[flist]") {
    ForwardList fl;
    REQUIRE(fl.isEmpty() == true);
    
    fl.pushHead("A"); fl.pushTail("B"); fl.pushTail("C");
    REQUIRE(fl.getSize() == 3);
    REQUIRE(fl.findValue("B") == true);
    
    fl.pushAfter("A", "A2"); fl.pushBefore("C", "B2");
    
    REQUIRE(fl.popHead() == true);
    REQUIRE(fl.popTail() == true);
    REQUIRE(fl.removeValue("A2") == true);
    REQUIRE(fl.removeValue("NotExist") == false);
    
    string val;
    REQUIRE(fl.getAt(0, val) == true);
}

TEST_CASE("DoublyLinkedList Operations", "[dlist]") {
    DoublyLinkedList dl;
    dl.pushHead("A"); dl.pushTail("C"); dl.pushBefore("C", "B");
    REQUIRE(dl.getSize() == 3);
    
    REQUIRE(dl.removeAfter("A") == true);
    REQUIRE(dl.getSize() == 2);
    
    REQUIRE(dl.popHead() == true);
    REQUIRE(dl.popTail() == true);
    REQUIRE(dl.popHead() == false);
}

TEST_CASE("Stack PushPop", "[stack]") {
    Stack s;
    REQUIRE(s.isEmpty() == true);
    s.push("bottom"); s.push("top");
    string val;
    REQUIRE(s.peek(val) == true);
    REQUIRE(val == "top");
    REQUIRE(s.pop(val) == true);
    REQUIRE(val == "top");
    REQUIRE(s.getSize() == 1);
    s.pop(val);
    REQUIRE(s.pop(val) == false);
    REQUIRE(s.peek(val) == false);
}

TEST_CASE("Queue PushPop", "[queue]") {
    Queue q;
    REQUIRE(q.isEmpty() == true);
    q.push("first"); q.push("second");
    string val;
    REQUIRE(q.front(val) == true);
    REQUIRE(val == "first");
    REQUIRE(q.pop(val) == true);
    REQUIRE(val == "first");
    q.pop(val);
    REQUIRE(q.pop(val) == false);
    REQUIRE(q.front(val) == false);
}

TEST_CASE("HashTable InsertSearchRemove", "[hash]") {
    HashTable ht(10, 1); 
    REQUIRE(ht.isEmpty() == true); 
    REQUIRE(ht.insert("key1") == true); REQUIRE(ht.insert("key2") == true);
    
    for(int i = 3; i <= 10; i++) {
        REQUIRE(ht.insert("key" + to_string(i)) == true);
    }
    REQUIRE(ht.insert("overflow") == false); 
    
    REQUIRE(ht.search("key1") == true); 
    REQUIRE(ht.search("unknown") == false); 
    REQUIRE(ht.remove("key1") == true); 
    REQUIRE(ht.search("key1") == false); 
}

TEST_CASE("RBTree InsertSearchRemove", "[rbtree]") {
    RBTree tree;
    REQUIRE(tree.isEmpty() == true);
    
    for (int i = 1; i <= 20; ++i) tree.insert(i);
    REQUIRE(tree.search(10) == true);
    REQUIRE(tree.search(99) == false);
    
    REQUIRE(tree.remove(10) == true);
    REQUIRE(tree.remove(15) == true);
    REQUIRE(tree.remove(99) == false);
    REQUIRE(tree.search(10) == false);
}

TEST_CASE("CoverageBoost PrintAndEdgeCases", "[misc]") {
    DynamicArray arr(0); arr.print(); arr.pushBack("A"); arr.print(); 
    Stack s; s.print(); s.push("S"); s.print(); s.getSize();
    Queue q; q.print(); q.push("Q"); q.print(); q.getSize();
    RBTree tree; tree.print(); tree.insert(5); tree.print();
}

TEST_CASE("DoublyLinkedList FullCoverage", "[dlist]") {
    DoublyLinkedList dl;
    dl.print(); 
    dl.pushTail("1"); dl.pushTail("2"); dl.pushTail("3"); dl.print(); 
    
    REQUIRE(dl.pushAfter("2", "2.5") == true); REQUIRE(dl.pushAfter("99", "0") == false);
    REQUIRE(dl.pushBefore("2", "1.5") == true); REQUIRE(dl.pushBefore("99", "0") == false);
    
    REQUIRE(dl.removeValue("2.5") == true); REQUIRE(dl.removeValue("99") == false);
    REQUIRE(dl.removeBefore("3") == true); REQUIRE(dl.removeBefore("1") == false); 
    REQUIRE(dl.removeAfter("1") == true); REQUIRE(dl.removeAfter("3") == false); 
    
    string val;
    REQUIRE(dl.getAt(1, val) == true); REQUIRE(dl.getAt(100, val) == false);
    REQUIRE(dl.findValue("3") == true); REQUIRE(dl.findValue("99") == false);
}

TEST_CASE("ForwardList FullCoverage", "[flist]") {
    ForwardList fl;
    fl.print();
    fl.pushHead("1"); fl.pushTail("2"); fl.pushTail("3"); fl.print();
    
    REQUIRE(fl.pushAfter("99", "0") == false); REQUIRE(fl.pushBefore("99", "0") == false);
    REQUIRE(fl.removeBefore("3") == true); REQUIRE(fl.removeBefore("1") == false);
    REQUIRE(fl.removeAfter("1") == true); REQUIRE(fl.removeAfter("3") == false);
    
    string out;
    REQUIRE(fl.getAt(100, out) == false); 
}

TEST_CASE("HashTable FoldHashMethod", "[hash]") {
    HashTable ht(10, 2); 
    REQUIRE(ht.insert("123456789") == true);
    REQUIRE(ht.insert("123456789") == false); 
    
    REQUIRE(ht.search("123456789") == true);
    REQUIRE(ht.search("000") == false);
    
    REQUIRE(ht.remove("123456789") == true);
    REQUIRE(ht.remove("000") == false);
    
    REQUIRE(ht.getSize() == 10);
    REQUIRE(ht.getCount() == 0);
}

TEST_CASE("RBTree FullCoverage", "[rbtree]") {
    RBTree tree;
    REQUIRE(tree.isEmpty() == true);

    for (int i = 1; i <= 15; ++i) tree.insert(i);
    for (int i = -1; i >= -15; --i) tree.insert(i);
    
    tree.insert(100); tree.insert(50); tree.insert(150); 
    tree.insert(25); tree.insert(75); tree.insert(125);
    tree.insert(10);

    REQUIRE(tree.search(50) == true);
    REQUIRE(tree.search(999) == false);

    tree.remove(999);
    tree.remove(1);
    tree.remove(-1);
    tree.remove(100);
    tree.remove(50);
    tree.remove(150);

    REQUIRE(tree.search(10) == true);
    tree.print();
}