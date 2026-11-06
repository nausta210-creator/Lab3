package main

import (
	"fmt"
	"testing"
)

const N = 10000

func BenchmarkDynamicArray(b *testing.B) {
	for i := 0; i < b.N; i++ {
		arr := NewDynamicArray(4)
		for j := 0; j < N; j++ {
			arr.PushBack("item")
		}
	}
}

func BenchmarkForwardList(b *testing.B) {
	for i := 0; i < b.N; i++ {
		list := NewForwardList()
		for j := 0; j < N; j++ {
			list.PushHead("item")
		}
	}
}

func BenchmarkDoublyLinkedList(b *testing.B) {
	for i := 0; i < b.N; i++ {
		list := NewDoublyLinkedList()
		for j := 0; j < N; j++ {
			list.PushTail("item")
		}
	}
}

func BenchmarkStack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		s := NewStack()
		for j := 0; j < N; j++ {
			s.Push("item")
		}
		for j := 0; j < N; j++ {
			s.Pop()
		}
	}
}

func BenchmarkQueue(b *testing.B) {
	for i := 0; i < b.N; i++ {
		q := NewQueue()
		for j := 0; j < N; j++ {
			q.Push("item")
		}
		for j := 0; j < N; j++ {
			q.Pop()
		}
	}
}

func BenchmarkHashTable(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ht := NewHashTable(N*2, 1)
		for j := 0; j < N; j++ {
			ht.Insert(fmt.Sprintf("key%d", j))
		}
	}
}

func BenchmarkRBTree(b *testing.B) {
	for i := 0; i < b.N; i++ {
		tree := NewRBTree()
		for j := 0; j < N; j++ {
			tree.Insert(j)
		}
	}
}