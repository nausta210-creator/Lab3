package main

import "errors"

type DynamicArray struct {
	data     []string
	capacity int
}

func NewDynamicArray(initialCapacity int) *DynamicArray {
	if initialCapacity <= 0 {
		initialCapacity = 4
	}
	return &DynamicArray{
		data:     make([]string, 0, initialCapacity),
		capacity: initialCapacity,
	}
}

func (a *DynamicArray) PushBack(value string) {
	a.data = append(a.data, value)
}

func (a *DynamicArray) InsertAt(index int, value string) error {
	if index < 0 || index > len(a.data) {
		return errors.New("индекс вне границ")
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = value
	return nil
}

func (a *DynamicArray) GetAt(index int) (string, error) {
	if index < 0 || index >= len(a.data) {
		return "", errors.New("индекс вне границ")
	}
	return a.data[index], nil
}

func (a *DynamicArray) SetAt(index int, value string) error {
	if index < 0 || index >= len(a.data) {
		return errors.New("индекс вне границ")
	}
	a.data[index] = value
	return nil
}

func (a *DynamicArray) RemoveAt(index int) error {
	if index < 0 || index >= len(a.data) {
		return errors.New("индекс вне границ")
	}
	a.data = append(a.data[:index], a.data[index+1:]...)
	return nil
}

func (a *DynamicArray) GetSize() int { return len(a.data) }
func (a *DynamicArray) IsEmpty() bool { return len(a.data) == 0 }