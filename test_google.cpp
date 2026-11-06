#include <gtest/gtest.h>
#include <string>
#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "rbtree.h"

using namespace std;

TEST(DynamicArrayTest, BasicOperations) {
    DynamicArray arr;
    EXPECT_TRUE(arr.isEmpty());
    
    arr.pushBack("A"); arr.pushBack("B"); arr.pushBack("C"); arr.pushBack("D");
    arr.pushBack("E"); 
    
    EXPECT_EQ(arr.getSize(), 5);
    string val;
    EXPECT_TRUE(arr.getAt(0, val));
    EXPECT_EQ(val, "A");
    
    EXPECT_TRUE(arr.setAt(1, "B2"));
    EXPECT_TRUE(arr.getAt(1, val));
    EXPECT_EQ(val, "B2");
    
    EXPECT_TRUE(arr.insertAt(2, "X"));
    EXPECT_TRUE(arr.removeAt(0));
    
    EXPECT_FALSE(arr.getAt(100, val));
    EXPECT_FALSE(arr.removeAt(100));
}

TEST(ForwardListTest, Operations) {
    ForwardList fl;
    EXPECT_TRUE(fl.isEmpty());
    
    fl.pushHead("A"); fl.pushTail("B"); fl.pushTail("C");
    EXPECT_EQ(fl.getSize(), 3);
    EXPECT_TRUE(fl.findValue("B"));
    
    fl.pushAfter("A", "A2");
    fl.pushBefore("C", "B2");
    
    EXPECT_TRUE(fl.popHead());
    EXPECT_TRUE(fl.popTail());
    EXPECT_TRUE(fl.removeValue("A2"));
    EXPECT_FALSE(fl.removeValue("NotExist"));
    
    string val;
    EXPECT_TRUE(fl.getAt(0, val));
}

TEST(DoublyLinkedListTest, Operations) {
    DoublyLinkedList dl;
    dl.pushHead("A"); dl.pushTail("C"); dl.pushBefore("C", "B");
    EXPECT_EQ(dl.getSize(), 3);
    
    EXPECT_TRUE(dl.removeAfter("A"));
    EXPECT_EQ(dl.getSize(), 2);
    
    EXPECT_TRUE(dl.popHead());
    EXPECT_TRUE(dl.popTail());
    EXPECT_FALSE(dl.popHead());
}

TEST(StackTest, PushPop) {
    Stack s;
    EXPECT_TRUE(s.isEmpty());
    s.push("bottom"); s.push("top");
    string val;
    EXPECT_TRUE(s.peek(val));
    EXPECT_EQ(val, "top");
    EXPECT_TRUE(s.pop(val));
    EXPECT_EQ(val, "top");
    EXPECT_EQ(s.getSize(), 1);
    s.pop(val);
    EXPECT_FALSE(s.pop(val));
    EXPECT_FALSE(s.peek(val));
}

TEST(QueueTest, PushPop) {
    Queue q;
    EXPECT_TRUE(q.isEmpty());
    q.push("first"); q.push("second");
    string val;
    EXPECT_TRUE(q.front(val));
    EXPECT_EQ(val, "first");
    EXPECT_TRUE(q.pop(val));
    EXPECT_EQ(val, "first");
    q.pop(val);
    EXPECT_FALSE(q.pop(val));
    EXPECT_FALSE(q.front(val));
}

TEST(HashTableTest, InsertSearchRemove) {
    HashTable ht(10, 1); 
    EXPECT_TRUE(ht.isEmpty()); 
    EXPECT_TRUE(ht.insert("key1")); EXPECT_TRUE(ht.insert("key2"));
    
    for(int i = 3; i <= 10; i++) {
        EXPECT_TRUE(ht.insert("key" + to_string(i)));
    }
    EXPECT_FALSE(ht.insert("overflow")); 
    
    EXPECT_TRUE(ht.search("key1")); 
    EXPECT_FALSE(ht.search("unknown")); 
    EXPECT_TRUE(ht.remove("key1")); 
    EXPECT_FALSE(ht.search("key1")); 
}

TEST(RBTreeTest, InsertSearchRemove) {
    RBTree tree;
    EXPECT_TRUE(tree.isEmpty());
    
    for (int i = 1; i <= 20; ++i) tree.insert(i);
    EXPECT_TRUE(tree.search(10));
    EXPECT_FALSE(tree.search(99));
    
    EXPECT_TRUE(tree.remove(10));
    EXPECT_TRUE(tree.remove(15));
    EXPECT_FALSE(tree.remove(99));
    EXPECT_FALSE(tree.search(10));
}

TEST(CoverageBoostTest, PrintAndEdgeCases) {
    DynamicArray arr(0); arr.print(); arr.pushBack("A"); arr.print(); 
    Stack s; s.print(); s.push("S"); s.print(); s.getSize();
    Queue q; q.print(); q.push("Q"); q.print(); q.getSize();
    RBTree tree; tree.print(); tree.insert(5); tree.print();
}

TEST(DoublyLinkedListTest, FullCoverage) {
    DoublyLinkedList dl;
    dl.print(); 
    dl.pushTail("1"); dl.pushTail("2"); dl.pushTail("3"); dl.print(); 
    
    EXPECT_TRUE(dl.pushAfter("2", "2.5")); EXPECT_FALSE(dl.pushAfter("99", "0"));
    EXPECT_TRUE(dl.pushBefore("2", "1.5")); EXPECT_FALSE(dl.pushBefore("99", "0"));
    
    EXPECT_TRUE(dl.removeValue("2.5")); EXPECT_FALSE(dl.removeValue("99"));
    EXPECT_TRUE(dl.removeBefore("3")); EXPECT_FALSE(dl.removeBefore("1")); 
    EXPECT_TRUE(dl.removeAfter("1")); EXPECT_FALSE(dl.removeAfter("3")); 
    
    string val;
    EXPECT_TRUE(dl.getAt(1, val)); EXPECT_FALSE(dl.getAt(100, val));
    EXPECT_TRUE(dl.findValue("3")); EXPECT_FALSE(dl.findValue("99"));
}

TEST(ForwardListTest, FullCoverage) {
    ForwardList fl;
    fl.print();
    fl.pushHead("1"); fl.pushTail("2"); fl.pushTail("3"); fl.print();
    
    EXPECT_FALSE(fl.pushAfter("99", "0")); EXPECT_FALSE(fl.pushBefore("99", "0"));
    EXPECT_TRUE(fl.removeBefore("3")); EXPECT_FALSE(fl.removeBefore("1"));
    EXPECT_TRUE(fl.removeAfter("1")); EXPECT_FALSE(fl.removeAfter("3"));
    
    string out;
    EXPECT_FALSE(fl.getAt(100, out)); 
}

TEST(HashTableTest, FoldHashMethod) {
    HashTable ht(10, 2); 
    
    EXPECT_TRUE(ht.insert("123456789"));
    EXPECT_FALSE(ht.insert("123456789")); 
    
    EXPECT_TRUE(ht.search("123456789"));
    EXPECT_FALSE(ht.search("000"));
    
    EXPECT_TRUE(ht.remove("123456789"));
    EXPECT_FALSE(ht.remove("000"));
    
    EXPECT_EQ(ht.getSize(), 10);
    EXPECT_EQ(ht.getCount(), 0);
}

TEST(RBTreeTest, FullCoverage) {
    RBTree tree;
    EXPECT_TRUE(tree.isEmpty());

    for (int i = 1; i <= 15; ++i) tree.insert(i);
    for (int i = -1; i >= -15; --i) tree.insert(i);
    
    tree.insert(100); tree.insert(50); tree.insert(150); 
    tree.insert(25); tree.insert(75); tree.insert(125);
    tree.insert(10);

    EXPECT_TRUE(tree.search(50));
    EXPECT_FALSE(tree.search(999));

    tree.remove(999);
    tree.remove(1);
    tree.remove(-1);
    tree.remove(100);
    tree.remove(50);
    tree.remove(150);

    EXPECT_TRUE(tree.search(10));
    
    testing::internal::CaptureStdout();
    tree.print();
    EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}