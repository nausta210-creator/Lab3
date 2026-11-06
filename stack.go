package main

import "errors"

type sNode struct {
	data string
	next *sNode
}

type Stack struct {
	top *sNode
}

func NewStack() *Stack {
	return &Stack{}
}

func (s *Stack) Push(val string) {
	s.top = &sNode{data: val, next: s.top}
}

func (s *Stack) Pop() (string, error) {
	if s.top == nil {
		return "", errors.New("стек пуст")
	}
	val := s.top.data
	s.top = s.top.next
	return val, nil
}

func (s *Stack) Peek() (string, error) {
	if s.top == nil {
		return "", errors.New("стек пуст")
	}
	return s.top.data, nil
}

func (s *Stack) GetSize() int {
	c := 0
	curr := s.top
	for curr != nil {
		c++
		curr = curr.next
	}
	return c
}

func (s *Stack) IsEmpty() bool { return s.top == nil }