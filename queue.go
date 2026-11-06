package main

import "errors"

type qNode struct {
	data string
	next *qNode
}

type Queue struct {
	head *qNode
	tail *qNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) Push(val string) {
	newNode := &qNode{data: val, next: nil}
	if q.tail != nil {
		q.tail.next = newNode
	} else {
		q.head = newNode
	}
	q.tail = newNode
}

func (q *Queue) Pop() (string, error) {
	if q.head == nil {
		return "", errors.New("очередь пуста")
	}
	val := q.head.data
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	return val, nil
}

func (q *Queue) Front() (string, error) {
	if q.head == nil {
		return "", errors.New("очередь пуста")
	}
	return q.head.data, nil
}

func (q *Queue) GetSize() int {
	c := 0
	curr := q.head
	for curr != nil {
		c++
		curr = curr.next
	}
	return c
}

func (q *Queue) IsEmpty() bool { return q.head == nil }