#include <benchmark/benchmark.h>
#include <string>
#include <vector>
#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "rbtree.h"

using namespace std;

static void BM_DynamicArray_PushBack(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        DynamicArray arr;
        for (int i = 0; i < state.range(0); ++i) {
            arr.pushBack(item); //
        }
        benchmark::DoNotOptimize(arr);
    }
}
BENCHMARK(BM_DynamicArray_PushBack)->Range(100, 10000);

static void BM_ForwardList_PushHead(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        ForwardList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushHead(item); //[cite: 2]
        }
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_ForwardList_PushHead)->Range(100, 10000);

static void BM_DoublyLinkedList_PushTail(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        DoublyLinkedList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.pushTail(item); //[cite: 2]
        }
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_DoublyLinkedList_PushTail)->Range(100, 10000);

static void BM_Stack_Push(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        Stack s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(item); //[cite: 2]
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_Stack_Push)->Range(100, 10000);

static void BM_Stack_Pop(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        state.PauseTiming();
        Stack s;
        for (int i = 0; i < state.range(0); ++i) {
            s.push(item); //[cite: 2]
        }
        string out;
        state.ResumeTiming();
        
        for (int i = 0; i < state.range(0); ++i) {
            s.pop(out); //[cite: 2]
        }
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_Stack_Pop)->Range(100, 10000);

static void BM_Queue_Push(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < state.range(0); ++i) {
            q.push(item); //[cite: 2]
        }
        benchmark::DoNotOptimize(q);
    }
}
BENCHMARK(BM_Queue_Push)->Range(100, 10000);

static void BM_Queue_Pop(benchmark::State& state) {
    string item = "item";
    for (auto _ : state) {
        state.PauseTiming();
        Queue q;
        for (int i = 0; i < state.range(0); ++i) {
            q.push(item);
        }
        string out;
        state.ResumeTiming();
        
        for (int i = 0; i < state.range(0); ++i) {
            q.pop(out); 
        }
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_Queue_Pop)->Range(100, 10000);

static void BM_HashTable_Insert(benchmark::State& state) {
    vector<string> keys(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        keys[i] = "key" + to_string(i);
    }

    for (auto _ : state) {
        HashTable ht(state.range(0) * 2, 1); 
        for (int i = 0; i < state.range(0); ++i) {
            ht.insert(keys[i]); 
        }
        benchmark::DoNotOptimize(ht);
    }
}
BENCHMARK(BM_HashTable_Insert)->Range(100, 10000);

static void BM_RBTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        RBTree tree;
        for (int i = 0; i < state.range(0); ++i) {
            tree.insert(i); 
        }
        benchmark::DoNotOptimize(tree);
    }
}
BENCHMARK(BM_RBTree_Insert)->Range(100, 10000);

BENCHMARK_MAIN();