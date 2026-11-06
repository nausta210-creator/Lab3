package main

import (
	"encoding/gob"
	"encoding/json"
	"fmt"
	"os"
)

type ArrayJSON struct { Items []string `json:"items"` }
type FListJSON struct { Items []string `json:"items"` }
type DListJSON struct { Items []string `json:"items"` }
type StackJSON struct { Items []string `json:"items"` }
type QueueJSON struct { Items []string `json:"items"` }
type HashTableJSON struct {
	Slots  []string `json:"slots"`
	Used   []string `json:"used"`
	Size   int      `json:"size"`
	Count  int      `json:"count"`
	Method int      `json:"method"`
}

func main() {
	fmt.Println("СЕРИАЛИЗАЦИЯ И ДЕСЕРИАЛИЗАЦИЯ")
	fmt.Println()

	arr := NewDynamicArray(4)
	arr.PushBack("A"); arr.PushBack("B"); arr.PushBack("C")
	
	fmt.Println("1. МАССИВ")
	
	fmt.Printf("   [Текст] Сохранено: %v\n", arr.data)
	dataArr := ArrayJSON{Items: arr.data}
	jsonArr, _ := json.MarshalIndent(dataArr, "", "  ")
	os.WriteFile("array.json", jsonArr, 0644)
	
	var loadedArr ArrayJSON
	readArr, _ := os.ReadFile("array.json")
	json.Unmarshal(readArr, &loadedArr)
	fmt.Printf("   [Текст] Восстановлено: %v\n", loadedArr.Items)

	fmt.Printf("   [Бинарный] Сохранено: %v\n", arr.data)
	binArr, _ := os.Create("array.bin")
	gob.NewEncoder(binArr).Encode(arr.data)
	binArr.Close()

	var loadedArrBin []string
	readArrBin, _ := os.Open("array.bin")
	gob.NewDecoder(readArrBin).Decode(&loadedArrBin)
	readArrBin.Close()
	fmt.Printf("   [Бинарный] Восстановлено: %v\n\n", loadedArrBin)

	fl := NewForwardList()
	fl.PushTail("X"); fl.PushTail("Y")
	
	fmt.Println("2. ОДНОСВЯЗНЫЙ СПИСОК")
	
	flData := FListJSON{Items: []string{}}
	for i := 0; i < fl.GetSize(); i++ { val, _ := fl.GetAt(i); flData.Items = append(flData.Items, val) }
	fmt.Printf("   [Текст] Сохранено: %v\n", flData.Items)
	jsonFL, _ := json.MarshalIndent(flData, "", "  ")
	os.WriteFile("flist.json", jsonFL, 0644)
	
	var loadedFL FListJSON
	readFL, _ := os.ReadFile("flist.json")
	json.Unmarshal(readFL, &loadedFL)
	fmt.Printf("   [Текст] Восстановлено: %v\n", loadedFL.Items)

	fmt.Printf("   [Бинарный] Сохранено: %v\n", flData.Items)
	binFL, _ := os.Create("flist.bin")
	gob.NewEncoder(binFL).Encode(flData.Items)
	binFL.Close()

	var loadedFLBin []string
	readFLBin, _ := os.Open("flist.bin")
	gob.NewDecoder(readFLBin).Decode(&loadedFLBin)
	readFLBin.Close()
	fmt.Printf("   [Бинарный] Восстановлено: %v\n\n", loadedFLBin)

	dl := NewDoublyLinkedList()
	dl.PushTail("1"); dl.PushTail("2")
	
	fmt.Println("3. ДВУСВЯЗНЫЙ СПИСОК")
	
	dlData := DListJSON{Items: []string{}}
	for i := 0; i < dl.GetSize(); i++ { val, _ := dl.GetAt(i); dlData.Items = append(dlData.Items, val) }
	fmt.Printf("   [Текст] Сохранено: %v\n", dlData.Items)
	jsonDL, _ := json.MarshalIndent(dlData, "", "  ")
	os.WriteFile("dlist.json", jsonDL, 0644)
	
	var loadedDL DListJSON
	readDL, _ := os.ReadFile("dlist.json")
	json.Unmarshal(readDL, &loadedDL)
	fmt.Printf("   [Текст] Восстановлено: %v\n", loadedDL.Items)

	fmt.Printf("   [Бинарный] Сохранено: %v\n", dlData.Items)
	binDL, _ := os.Create("dlist.bin")
	gob.NewEncoder(binDL).Encode(dlData.Items)
	binDL.Close()

	var loadedDLBin []string
	readDLBin, _ := os.Open("dlist.bin")
	gob.NewDecoder(readDLBin).Decode(&loadedDLBin)
	readDLBin.Close()
	fmt.Printf("   [Бинарный] Восстановлено: %v\n\n", loadedDLBin)

	s := NewStack()
	s.Push("First"); s.Push("Second")
	
	fmt.Println("4. СТЕК")
	
	sData := StackJSON{Items: []string{}}
	tempS := NewStack()
	for !s.IsEmpty() { val, _ := s.Pop(); tempS.Push(val) }
	for !tempS.IsEmpty() { val, _ := tempS.Pop(); sData.Items = append(sData.Items, val); s.Push(val) }
	fmt.Printf("   [Текст] Сохранено: %v\n", sData.Items)
	jsonS, _ := json.MarshalIndent(sData, "", "  ")
	os.WriteFile("stack.json", jsonS, 0644)
	
	var loadedS StackJSON
	readS, _ := os.ReadFile("stack.json")
	json.Unmarshal(readS, &loadedS)
	fmt.Printf("   [Текст] Восстановлено: %v\n", loadedS.Items)

	fmt.Printf("   [Бинарный] Сохранено: %v\n", sData.Items)
	binS, _ := os.Create("stack.bin")
	gob.NewEncoder(binS).Encode(sData.Items)
	binS.Close()

	var loadedSBin []string
	readSBin, _ := os.Open("stack.bin")
	gob.NewDecoder(readSBin).Decode(&loadedSBin)
	readSBin.Close()
	fmt.Printf("   [Бинарный] Восстановлено: %v\n\n", loadedSBin)

	q := NewQueue()
	q.Push("One"); q.Push("Two")
	
	fmt.Println("5. ОЧЕРЕДЬ")
	
	qData := QueueJSON{Items: []string{}}
	tempQ := NewQueue()
	for !q.IsEmpty() { val, _ := q.Pop(); tempQ.Push(val) }
	for !tempQ.IsEmpty() { val, _ := tempQ.Pop(); qData.Items = append(qData.Items, val); q.Push(val) }
	fmt.Printf("   [Текст] Сохранено: %v\n", qData.Items)
	jsonQ, _ := json.MarshalIndent(qData, "", "  ")
	os.WriteFile("queue.json", jsonQ, 0644)
	
	var loadedQ QueueJSON
	readQ, _ := os.ReadFile("queue.json")
	json.Unmarshal(readQ, &loadedQ)
	fmt.Printf("   [Текст] Восстановлено: %v\n", loadedQ.Items)

	fmt.Printf("   [Бинарный] Сохранено: %v\n", qData.Items)
	binQ, _ := os.Create("queue.bin")
	gob.NewEncoder(binQ).Encode(qData.Items)
	binQ.Close()

	var loadedQBin []string
	readQBin, _ := os.Open("queue.bin")
	gob.NewDecoder(readQBin).Decode(&loadedQBin)
	readQBin.Close()
	fmt.Printf("   [Бинарный] Восстановлено: %v\n\n", loadedQBin)

	ht := NewHashTable(11, 1)
	ht.Insert("apple")
	ht.Insert("banana")
	ht.Insert("cherry")

	fmt.Println("6. ХЕШ-ТАБЛИЦА")

	htData := HashTableJSON{
		Slots:  []string{},
		Used:   []string{},
		Size:   ht.GetSize(),
		Count:  ht.GetCount(),
		Method: 1,
	}
	for i := 0; i < ht.GetSize(); i++ {
		v, _ := ht.slots.GetAt(i)
		u, _ := ht.used.GetAt(i)
		htData.Slots = append(htData.Slots, v)
		htData.Used = append(htData.Used, u)
	}

	fmt.Printf("   [Текст] Сохранено: %v\n", htData.Slots)
	jsonHT, _ := json.MarshalIndent(htData, "", "  ")
	os.WriteFile("hashtable.json", jsonHT, 0644)

	var loadedHT HashTableJSON
	readHT, _ := os.ReadFile("hashtable.json")
	json.Unmarshal(readHT, &loadedHT)

	htRestored := NewHashTable(loadedHT.Size, loadedHT.Method)
	for i := 0; i < loadedHT.Size; i++ {
		htRestored.slots.SetAt(i, loadedHT.Slots[i])
		htRestored.used.SetAt(i, loadedHT.Used[i])
	}
	htRestored.count = loadedHT.Count
	fmt.Printf("   [Текст] Восстановлено: size=%d count=%d\n",
		htRestored.GetSize(), htRestored.GetCount())

	fmt.Printf("   [Бинарный] Сохранено: %v\n", htData.Slots)
	binHT, _ := os.Create("hashtable.bin")
	gob.NewEncoder(binHT).Encode(htData)
	binHT.Close()

	var loadedHTBin HashTableJSON
	readHTBin, _ := os.Open("hashtable.bin")
	gob.NewDecoder(readHTBin).Decode(&loadedHTBin)
	readHTBin.Close()

	htBinRestored := NewHashTable(loadedHTBin.Size, loadedHTBin.Method)
	for i := 0; i < loadedHTBin.Size; i++ {
		htBinRestored.slots.SetAt(i, loadedHTBin.Slots[i])
		htBinRestored.used.SetAt(i, loadedHTBin.Used[i])
	}
	htBinRestored.count = loadedHTBin.Count
	fmt.Printf("   [Бинарный] Восстановлено: size=%d count=%d\n\n",
		htBinRestored.GetSize(), htBinRestored.GetCount())

	tree := NewRBTree()
	tree.Insert(10); tree.Insert(20); tree.Insert(5); tree.Insert(15)
	
	fmt.Println("7. КРАСНО-ЧЁРНОЕ ДЕРЕВО")
	
	fmt.Println("   [Текст] Сохранено: 10 20 5 15 (в порядке вставки)")
	tree.SaveToFile("tree.json")
	
	treeT := NewRBTree()
	treeT.LoadFromFile("tree.json")
	fmt.Println("   [Текст] Восстановлено:")
	treeT.Print()

	fmt.Println("   [Бинарный] Сохранено: 10 20 5 15")
	tree.SaveToFileBin("tree.bin")
	
	treeB := NewRBTree()
	treeB.LoadFromFileBin("tree.bin")
	fmt.Println("   [Бинарный] Восстановлено:")
	treeB.Print()
}