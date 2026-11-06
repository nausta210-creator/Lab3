package main

import "errors"

type fNode struct {
	data string
	next *fNode
}

type ForwardList struct {
	head *fNode
}

func NewForwardList() *ForwardList {
	return &ForwardList{}
}

func (l *ForwardList) PushHead(val string) {
	l.head = &fNode{data: val, next: l.head}
}

func (l *ForwardList) PushTail(val string) {
	newNode := &fNode{data: val, next: nil}
	if l.head == nil {
		l.head = newNode
		return
	}
	curr := l.head
	for curr.next != nil {
		curr = curr.next
	}
	curr.next = newNode
}

func (l *ForwardList) PushAfter(target, val string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			curr.next = &fNode{data: val, next: curr.next}
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *ForwardList) PushBefore(target, val string) error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	if l.head.data == target {
		l.PushHead(val)
		return nil
	}
	curr := l.head
	for curr.next != nil {
		if curr.next.data == target {
			curr.next = &fNode{data: val, next: curr.next}
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *ForwardList) PopHead() error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	l.head = l.head.next
	return nil
}

func (l *ForwardList) PopTail() error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	if l.head.next == nil {
		l.head = nil
		return nil
	}
	curr := l.head
	for curr.next.next != nil {
		curr = curr.next
	}
	curr.next = nil
	return nil
}

func (l *ForwardList) RemoveValue(val string) error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	if l.head.data == val {
		l.head = l.head.next
		return nil
	}
	curr := l.head
	for curr.next != nil {
		if curr.next.data == val {
			curr.next = curr.next.next
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *ForwardList) RemoveBefore(target string) error {
	if l.head == nil || l.head.data == target {
		return errors.New("невозможно удалить")
	}
	if l.head.next != nil && l.head.next.data == target {
		l.head = l.head.next
		return nil
	}
	curr := l.head
	for curr.next != nil && curr.next.next != nil {
		if curr.next.next.data == target {
			curr.next = curr.next.next
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *ForwardList) RemoveAfter(target string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			if curr.next != nil {
				curr.next = curr.next.next
				return nil
			}
			return errors.New("нет элемента после")
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *ForwardList) GetAt(index int) (string, error) {
	if index < 0 {
		return "", errors.New("индекс вне границ")
	}
	curr := l.head
	for i := 0; i < index; i++ {
		if curr == nil {
			return "", errors.New("индекс вне границ")
		}
		curr = curr.next
	}
	if curr == nil {
		return "", errors.New("индекс вне границ")
	}
	return curr.data, nil
}

func (l *ForwardList) FindValue(val string) bool {
	curr := l.head
	for curr != nil {
		if curr.data == val {
			return true
		}
		curr = curr.next
	}
	return false
}

func (l *ForwardList) GetSize() int {
	c := 0
	curr := l.head
	for curr != nil {
		c++
		curr = curr.next
	}
	return c
}

func (l *ForwardList) IsEmpty() bool {
	return l.head == nil
}