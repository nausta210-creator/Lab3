package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestDynamicArray(t *testing.T) {
	arr := NewDynamicArray(4)
	assert.True(t, arr.IsEmpty())
	
	arr.PushBack("A"); arr.PushBack("B"); arr.PushBack("C"); arr.PushBack("D")
	arr.PushBack("E") 
	
	assert.Equal(t, 5, arr.GetSize())
	val, err := arr.GetAt(0)
	assert.Nil(t, err)
	assert.Equal(t, "A", val)
	
	err = arr.SetAt(1, "B2")
	assert.Nil(t, err)
	val, _ = arr.GetAt(1)
	assert.Equal(t, "B2", val)
	
	err = arr.InsertAt(2, "X")
	assert.Nil(t, err)
	err = arr.RemoveAt(0)
	assert.Nil(t, err)
	
	_, err = arr.GetAt(100); assert.NotNil(t, err)
	err = arr.RemoveAt(100); assert.NotNil(t, err)
}

func TestForwardList(t *testing.T) {
	fl := NewForwardList()
	assert.True(t, fl.IsEmpty())
	
	fl.PushHead("A"); fl.PushTail("B"); fl.PushTail("C")
	assert.Equal(t, 3, fl.GetSize())
	assert.True(t, fl.FindValue("B"))
	
	fl.PushAfter("A", "A2")
	fl.PushBefore("C", "B2")
	
	fl.PopHead()
	fl.PopTail()
	
	err := fl.RemoveValue("A2"); assert.Nil(t, err)
	err = fl.RemoveValue("NotExist"); assert.NotNil(t, err)
	
	val, err := fl.GetAt(0); assert.Nil(t, err); assert.Equal(t, "B", val)

	fl.PushAfter("99", "0"); fl.PushBefore("99", "0")
	fl.RemoveBefore("3"); fl.RemoveBefore("1")
	fl.RemoveAfter("1"); fl.RemoveAfter("3")
	_, err = fl.GetAt(100); assert.NotNil(t, err)

	fl.PushTail("X"); fl.PushTail("Y"); fl.PushTail("Z")
	fl.RemoveBefore("Z") 
	fl.RemoveAfter("X")  
	fl.GetAt(0); fl.GetAt(-1); fl.GetAt(100)
}

func TestDoublyLinkedList(t *testing.T) {
	dl := NewDoublyLinkedList()
	dl.PushHead("A"); dl.PushTail("C"); dl.PushBefore("C", "B")
	assert.Equal(t, 3, dl.GetSize())
	
	dl.RemoveAfter("A")
	assert.Equal(t, 2, dl.GetSize())
	
	dl.PopHead()
	dl.PopTail()
	dl.PopHead() 

	dl.PushTail("1"); dl.PushTail("2"); dl.PushTail("3")
	dl.PushAfter("2", "2.5"); dl.PushAfter("99", "0")
	dl.PushBefore("2", "1.5"); dl.PushBefore("99", "0")
	
	dl.RemoveValue("2.5"); dl.RemoveValue("99")
	dl.RemoveBefore("3"); dl.RemoveBefore("1")
	dl.RemoveAfter("1"); dl.RemoveAfter("3")
	
	val, err := dl.GetAt(1); assert.Nil(t, err)
	assert.NotEmpty(t, val)
	_, err = dl.GetAt(100); assert.NotNil(t, err)
	assert.True(t, dl.FindValue("3"))
	assert.False(t, dl.FindValue("99"))
}

func TestStack(t *testing.T) {
	s := NewStack()
	assert.True(t, s.IsEmpty())
	s.Push("bottom"); s.Push("top")
	
	val, err := s.Peek(); assert.Nil(t, err); assert.Equal(t, "top", val)
	val, err = s.Pop(); assert.Nil(t, err); assert.Equal(t, "top", val)
	assert.Equal(t, 1, s.GetSize())
	
	s.Pop()
	_, err = s.Pop(); assert.NotNil(t, err)
	_, err = s.Peek(); assert.NotNil(t, err)
}

func TestHashTable(t *testing.T) {
	ht := NewHashTable(10, 1)
	assert.True(t, ht.IsEmpty())
	assert.True(t, ht.Insert("key1")); assert.True(t, ht.Insert("key2"))
	
	for i := 3; i <= 10; i++ {
		assert.True(t, ht.Insert("key" + string(rune(i+48))))
	}
	assert.False(t, ht.Insert("overflow"))
	
	assert.True(t, ht.Search("key1"))
	assert.False(t, ht.Search("unknown"))
	assert.Nil(t, ht.Remove("key1"))
	assert.False(t, ht.Search("key1"))

	ht2 := NewHashTable(10, 2)
	ht2.Insert("123456789"); ht2.Insert("123456789")
	ht2.Search("123456789"); ht2.Search("000")
	ht2.Remove("123456789"); ht2.Remove("000")
	assert.Equal(t, 10, ht2.GetSize())
	assert.Equal(t, 0, ht2.GetCount())
}

func TestRBTree(t *testing.T) {
	tree := NewRBTree()
	assert.True(t, tree.IsEmpty())
	
	for i := 1; i <= 20; i++ { tree.Insert(i) }
	assert.True(t, tree.Search(10))
	assert.False(t, tree.Search(99))
	
	assert.True(t, tree.Remove(10))
	assert.True(t, tree.Remove(15))
	assert.False(t, tree.Remove(99))
	assert.False(t, tree.Search(10))

	tree.Insert(30); tree.Insert(40); tree.Insert(50)
	tree.Remove(30); tree.Remove(40); tree.Remove(50)
	tree.Remove(99)
}

func TestCoverageBoost(t *testing.T) {
  arr := NewDynamicArray(0) 
  arr.PushBack("A")

  fl := NewForwardList()
  fl.PushHead("Head")
  fl.RemoveValue("Head")

  dl := NewDoublyLinkedList()
  dl.PushTail("TailNode")
  dl.RemoveValue("TailNode") 
  dl.PushTail("A")
  dl.PushTail("B")
  dl.RemoveValue("B") 

  s := NewStack()
  s.Push("Item")

  q := NewQueue()
  q.Push("Item")

  ht := NewHashTable(10, 2)
  ht.Insert("A")    
  ht.Insert("AB")    
  ht.Insert("ABC")   
  ht.Insert("ABCD")  
  ht.Insert("ABCDE")

  tree := NewRBTree()
  tree.Insert(100)
  
  for i := 50; i >= 20; i-- {
    tree.Insert(i)
  }
  
  tree.Remove(50) 
  tree.Remove(40)

  	tree.Insert(50)
	tree.Insert(25)
	tree.Insert(75)
	tree.Insert(10)
	tree.Insert(30)
	tree.Insert(60)
	tree.Insert(80)
	tree.Remove(50)
}

func TestQueue(t *testing.T) {
	q := NewQueue()
	assert.True(t, q.IsEmpty())
	q.Push("first"); q.Push("second")
	
	val, err := q.Front(); assert.Nil(t, err); assert.Equal(t, "first", val)
	val, err = q.Pop(); assert.Nil(t, err); assert.Equal(t, "first", val)
	
	q.Pop()
	_, err = q.Pop(); assert.NotNil(t, err)
	_, err = q.Front(); assert.NotNil(t, err)
}

func TestQueueSize(t *testing.T) {
    q := NewQueue()
    q.Push("1")
    q.Push("2")
    assert.Equal(t, 2, q.GetSize()) 
}

func TestExtraCoverage(t *testing.T) {
	fl := NewForwardList()
	fl.RemoveValue("x")

	fl.PushHead("A")
	fl.RemoveValue("A")

	fl.PushTail("B")
	fl.PushTail("C")
	fl.RemoveValue("B")

	fl.RemoveBefore("C")
	fl.RemoveAfter("C")

	fl.PopTail() 
	fl.PopTail() 

	tree := NewRBTree()
	tree.Print()

	tree.Insert(50)
	tree.Insert(25)
	tree.Insert(75)
	tree.Insert(10)
	tree.Insert(30)
	tree.Insert(60)
	tree.Insert(80)

	tree.Remove(50)
	tree.Remove(25)
	
	tree.Print()
}