package main

import "errors"

type dNode struct {
	data string
	prev *dNode
	next *dNode
}

type DoublyLinkedList struct {
	head *dNode
	tail *dNode
}

func NewDoublyLinkedList() *DoublyLinkedList {
	return &DoublyLinkedList{}
}

func (l *DoublyLinkedList) PushHead(val string) {
	newNode := &dNode{data: val, next: l.head}
	if l.head != nil {
		l.head.prev = newNode
	} else {
		l.tail = newNode
	}
	l.head = newNode
}

func (l *DoublyLinkedList) PushTail(val string) {
	newNode := &dNode{data: val, prev: l.tail}
	if l.tail != nil {
		l.tail.next = newNode
	} else {
		l.head = newNode
	}
	l.tail = newNode
}

func (l *DoublyLinkedList) PushBefore(target, val string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			if curr.prev == nil {
				l.PushHead(val)
			} else {
				newNode := &dNode{data: val, prev: curr.prev, next: curr}
				curr.prev.next = newNode
				curr.prev = newNode
			}
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *DoublyLinkedList) PushAfter(target, val string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			if curr.next == nil {
				l.PushTail(val)
			} else {
				newNode := &dNode{data: val, prev: curr, next: curr.next}
				curr.next.prev = newNode
				curr.next = newNode
			}
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *DoublyLinkedList) PopHead() error {
	if l.head == nil {
		return errors.New("список пуст")
	}
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	return nil
}

func (l *DoublyLinkedList) PopTail() error {
	if l.tail == nil {
		return errors.New("список пуст")
	}
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	return nil
}

func (l *DoublyLinkedList) RemoveValue(val string) error {
	curr := l.head
	for curr != nil {
		if curr.data == val {
			if curr.prev != nil {
				curr.prev.next = curr.next
			} else {
				l.head = curr.next
			}
			if curr.next != nil {
				curr.next.prev = curr.prev
			} else {
				l.tail = curr.prev
			}
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *DoublyLinkedList) RemoveBefore(target string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			if curr.prev == nil {
				return errors.New("нет элемента до")
			}
			toDelete := curr.prev
			if toDelete.prev != nil {
				toDelete.prev.next = curr
			} else {
				l.head = curr
			}
			curr.prev = toDelete.prev
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *DoublyLinkedList) RemoveAfter(target string) error {
	curr := l.head
	for curr != nil {
		if curr.data == target {
			if curr.next == nil {
				return errors.New("нет элемента после")
			}
			toDelete := curr.next
			if toDelete.next != nil {
				toDelete.next.prev = curr
			} else {
				l.tail = curr
			}
			curr.next = toDelete.next
			return nil
		}
		curr = curr.next
	}
	return errors.New("элемент не найден")
}

func (l *DoublyLinkedList) FindValue(val string) bool {
	curr := l.head
	for curr != nil {
		if curr.data == val {
			return true
		}
		curr = curr.next
	}
	return false
}

func (l *DoublyLinkedList) GetSize() int {
	c := 0
	curr := l.head
	for curr != nil {
		c++
		curr = curr.next
	}
	return c
}

func (l *DoublyLinkedList) IsEmpty() bool {
	return l.head == nil
}

func (l *DoublyLinkedList) GetAt(index int) (string, error) {
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