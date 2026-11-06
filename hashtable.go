package main

import (
	"errors"
	"strconv"
)

type HashTable struct {
	slots  *DynamicArray
	used   *DynamicArray
	size   int
	count  int
	method int
}

func NewHashTable(size int, method int) *HashTable {
	ht := &HashTable{
		slots:  NewDynamicArray(size),
		used:   NewDynamicArray(size),
		size:   size,
		count:  0,
		method: method,
	}
	for i := 0; i < size; i++ {
		ht.slots.PushBack("")
		ht.used.PushBack("0")
	}
	return ht
}

func (ht *HashTable) hash1(key string) uint {
	var h uint64 = 14695981039346656037
	for i := 0; i < len(key); i++ {
		h ^= uint64(key[i])
		h *= 1099511628211
	}
	return uint(h % uint64(ht.size))
}

func (ht *HashTable) hash2(key string) uint {
	var h uint64 = 5381
	for i := 0; i < len(key); i++ {
		h = (h << 5) + h + uint64(key[i])
	}
	return uint(h%uint64(ht.size-1)) + 1
}

func (ht *HashTable) FoldHash(key string) int {
	sum := 0
	part := ""
	for i := 0; i < len(key); i++ {
		part += string(key[i])
		if len(part) == 3 {
			num, _ := strconv.Atoi(part)
			sum += num
			part = ""
		}
	}
	if part != "" {
		num, _ := strconv.Atoi(part)
		sum += num
	}
	return sum % ht.size
}

func (ht *HashTable) getHash(key string) int {
	if ht.method == 2 {
		return ht.FoldHash(key)
	}
	return int(ht.hash1(key))
}

func (ht *HashTable) Insert(key string) bool {
	if ht.count >= ht.size {
		return false
	}
	idx := ht.getHash(key)
	step := 1
	if ht.method == 2 {
		step = int(ht.hash2(key))
	}
	for i := 0; i < ht.size; i++ {
		cur := (idx + i*step) % ht.size
		usedVal, _ := ht.used.GetAt(cur)
		if usedVal == "0" {
			ht.slots.SetAt(cur, key)
			ht.used.SetAt(cur, "1")
			ht.count++
			return true
		}
		slotVal, _ := ht.slots.GetAt(cur)
		if slotVal == key {
			return false
		}
	}
	return false
}

func (ht *HashTable) Search(key string) bool {
	idx := ht.getHash(key)
	step := 1
	if ht.method == 2 {
		step = int(ht.hash2(key))
	}
	for i := 0; i < ht.size; i++ {
		cur := (idx + i*step) % ht.size
		usedVal, _ := ht.used.GetAt(cur)
		if usedVal == "0" {
			return false
		}
		slotVal, _ := ht.slots.GetAt(cur)
		if slotVal == key {
			return true
		}
	}
	return false
}

func (ht *HashTable) Remove(key string) error {
	idx := ht.getHash(key)
	step := 1
	if ht.method == 2 {
		step = int(ht.hash2(key))
	}
	for i := 0; i < ht.size; i++ {
		cur := (idx + i*step) % ht.size
		usedVal, _ := ht.used.GetAt(cur)
		if usedVal == "0" {
			return errors.New("ключ не найден")
		}
		slotVal, _ := ht.slots.GetAt(cur)
		if slotVal == key {
			ht.slots.SetAt(cur, "")
			ht.used.SetAt(cur, "0")
			ht.count--
			return nil
		}
	}
	return errors.New("ключ не найден")
}

func (ht *HashTable) GetSize() int {
	return ht.size
}

func (ht *HashTable) GetCount() int { return ht.count }
func (ht *HashTable) IsEmpty() bool { return ht.count == 0 }