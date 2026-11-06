package main

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

type Color bool

const (
	RED   Color = true
	BLACK Color = false
)

type rbNode struct {
	data   int
	color  Color
	left   *rbNode
	right  *rbNode
	parent *rbNode
}

type RBTree struct {
	root *rbNode
	nil  *rbNode
}

func NewRBTree() *RBTree {
	nilNode := &rbNode{color: BLACK}
	return &RBTree{root: nilNode, nil: nilNode}
}

func (t *RBTree) IsEmpty() bool {
	return t.root == t.nil
}

func (t *RBTree) rotateLeft(x *rbNode) {
	y := x.right
	x.right = y.left
	if y.left != t.nil {
		y.left.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nil {
		t.root = y
	} else if x == x.parent.left {
		x.parent.left = y
	} else {
		x.parent.right = y
	}
	y.left = x
	x.parent = y
}

func (t *RBTree) rotateRight(x *rbNode) {
	y := x.left
	x.left = y.right
	if y.right != t.nil {
		y.right.parent = x
	}
	y.parent = x.parent
	if x.parent == t.nil {
		t.root = y
	} else if x == x.parent.right {
		x.parent.right = y
	} else {
		x.parent.left = y
	}
	y.right = x
	x.parent = y
}

func (t *RBTree) fixInsert(k *rbNode) {
	for k.parent.color == RED {
		if k.parent == k.parent.parent.left {
			u := k.parent.parent.right
			if u.color == RED {
				k.parent.color = BLACK
				u.color = BLACK
				k.parent.parent.color = RED
				k = k.parent.parent
			} else {
				if k == k.parent.right {
					k = k.parent
					t.rotateLeft(k)
				}
				k.parent.color = BLACK
				k.parent.parent.color = RED
				t.rotateRight(k.parent.parent)
			}
		} else {
			u := k.parent.parent.left
			if u.color == RED {
				k.parent.color = BLACK
				u.color = BLACK
				k.parent.parent.color = RED
				k = k.parent.parent
			} else {
				if k == k.parent.left {
					k = k.parent
					t.rotateRight(k)
				}
				k.parent.color = BLACK
				k.parent.parent.color = RED
				t.rotateLeft(k.parent.parent)
			}
		}
	}
	t.root.color = BLACK
}

func (t *RBTree) Insert(key int) {
	node := &rbNode{data: key, color: RED, left: t.nil, right: t.nil, parent: t.nil}
	y := t.nil
	x := t.root

	for x != t.nil {
		y = x
		if node.data == x.data {
			return
		}
		if node.data < x.data {
			x = x.left
		} else {
			x = x.right
		}
	}

	node.parent = y
	if y == t.nil {
		t.root = node
	} else if node.data < y.data {
		y.left = node
	} else {
		y.right = node
	}

	if node.parent == t.nil {
		node.color = BLACK
		return
	}
	if node.parent.parent == t.nil {
		return
	}
	t.fixInsert(node)
}

func (t *RBTree) Search(key int) bool {
	curr := t.root
	for curr != t.nil {
		if key == curr.data {
			return true
		}
		if key < curr.data {
			curr = curr.left
		} else {
			curr = curr.right
		}
	}
	return false
}

func (t *RBTree) transplant(u, v *rbNode) {
	if u.parent == t.nil {
		t.root = v
	} else if u == u.parent.left {
		u.parent.left = v
	} else {
		u.parent.right = v
	}
	v.parent = u.parent
}

func (t *RBTree) minimum(node *rbNode) *rbNode {
	for node.left != t.nil {
		node = node.left
	}
	return node
}

func (t *RBTree) fixDelete(x *rbNode) {
	for x != t.root && x.color == BLACK {
		if x == x.parent.left {
			s := x.parent.right
			if s.color == RED {
				s.color = BLACK
				x.parent.color = RED
				t.rotateLeft(x.parent)
				s = x.parent.right
			}
			if s.left.color == BLACK && s.right.color == BLACK {
				s.color = RED
				x = x.parent
			} else {
				if s.right.color == BLACK {
					s.left.color = BLACK
					s.color = RED
					t.rotateRight(s)
					s = x.parent.right
				}
				s.color = x.parent.color
				x.parent.color = BLACK
				s.right.color = BLACK
				t.rotateLeft(x.parent)
				x = t.root
			}
		} else {
			s := x.parent.left
			if s.color == RED {
				s.color = BLACK
				x.parent.color = RED
				t.rotateRight(x.parent)
				s = x.parent.left
			}
			if s.right.color == BLACK && s.left.color == BLACK {
				s.color = RED
				x = x.parent
			} else {
				if s.left.color == BLACK {
					s.right.color = BLACK
					s.color = RED
					t.rotateLeft(s)
					s = x.parent.left
				}
				s.color = x.parent.color
				x.parent.color = BLACK
				s.left.color = BLACK
				t.rotateRight(x.parent)
				x = t.root
			}
		}
	}
	x.color = BLACK
}

func (t *RBTree) Remove(key int) bool {
	z := t.root
	for z != t.nil && z.data != key {
		if key < z.data {
			z = z.left
		} else {
			z = z.right
		}
	}
	if z == t.nil {
		return false
	}

	y := z
	var x *rbNode
	yOriginalColor := y.color

	if z.left == t.nil {
		x = z.right
		t.transplant(z, z.right)
	} else if z.right == t.nil {
		x = z.left
		t.transplant(z, z.left)
	} else {
		y = t.minimum(z.right)
		yOriginalColor = y.color
		x = y.right
		if y.parent == z {
			x.parent = y
		} else {
			t.transplant(y, y.right)
			y.right = z.right
			y.right.parent = y
		}
		t.transplant(z, y)
		y.left = z.left
		y.left.parent = y
		y.color = z.color
	}
	if yOriginalColor == BLACK {
		t.fixDelete(x)
	}
	return true
}

func (t *RBTree) printHelper(node *rbNode, indent string, last bool) {
	if node != t.nil {
		print(indent)
		if last {
			print("R----")
			indent += "     "
		} else {
			print("L----")
			indent += "|    "
		}
		sColor := "(BLK)"
		if node.color == RED {
			sColor = "(RED)"
		}
		print(node.data, " ", sColor, "\n")
		t.printHelper(node.left, indent, false)
		t.printHelper(node.right, indent, true)
	}
}

func (t *RBTree) Print() {
	if t.root == t.nil {
		print("[Пустое дерево]\n")
		return
	}
	t.printHelper(t.root, "", true)
}

func collectInOrder(node *rbNode, nilNode *rbNode, items *[]int) {
	if node != nilNode {
		collectInOrder(node.left, nilNode, items)
		*items = append(*items, node.data)
		collectInOrder(node.right, nilNode, items)
	}
}

func (t *RBTree) SaveToFile(filename string) error {
	items := []int{}
	collectInOrder(t.root, t.nil, &items)
	data, err := json.MarshalIndent(items, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, data, 0644)
}

func (t *RBTree) LoadFromFile(filename string) error {
	readData, err := os.ReadFile(filename)
	if err != nil {
		return err
	}
	var items []int
	if err := json.Unmarshal(readData, &items); err != nil {
		return err
	}
	for _, val := range items {
		t.Insert(val)
	}
	return nil
}

func (t *RBTree) SaveToFileBin(filename string) error {
	items := []int{}
	collectInOrder(t.root, t.nil, &items)
	binFile, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer binFile.Close()
	encoder := gob.NewEncoder(binFile)
	return encoder.Encode(items)
}

func (t *RBTree) LoadFromFileBin(filename string) error {
	binFile, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer binFile.Close()
	var items []int
	decoder := gob.NewDecoder(binFile)
	if err := decoder.Decode(&items); err != nil {
		return err
	}
	for _, val := range items {
		t.Insert(val)
	}
	return nil
}