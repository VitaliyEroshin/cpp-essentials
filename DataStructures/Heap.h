/*
  Binary Heap, that can handle queries:
    1. insert (x) - add x to the heap.
    2. getMin - get min element in the heap.
    3. extractMin - extract min element from the heap.
    4. decreaseKey (i, delta) - decrease element inserted in i-th query by delta.
*/

#include <iostream>
#include <vector>

class Heap {
  bool (*cmp) (long long, long long);
  std::vector<long long> heap;
  std::vector<int> pointer;
  std::vector<int> num;
  int heap_size = 0; 
  
  void swap(int x, int y) {
    int k = num[x];
    int m = num[y];
    std::swap(num[x], num[y]);
    std::swap(pointer[k], pointer[m]);
    std::swap(heap[x], heap[y]);
  }

  void siftUp(int x) {
    while (x != 1) {
      int y = x / 2;
      if (cmp(heap[x], heap[y])) {
        swap(x, y);
        x = y;
      } else {
        break;
      }
    }
  }

  void siftDown(int x) {
    int y = x * 2, z = x * 2 + 1;
    while (y <= heap_size) {
      if (z <= heap_size && cmp(heap[z], heap[y]) && cmp(heap[z], heap[x])) {
        swap(x, z);
        x = z;
      } else if (cmp(heap[y], heap[x])) {
        swap(x, y);
        x = y;
      } else {
        break;
      }
      y = x * 2;
      z = x * 2 + 1;
    }
  }

  public:
    void init(int max_heap_size, bool(*compare_function) (long long, long long)) {
      pointer.resize(max_heap_size);
      num.resize(max_heap_size);
      heap.resize(max_heap_size);
      cmp = compare_function;
    }
  
    void insert(long long x, int q) {
      heap[++heap_size] = x;
      pointer[q] = heap_size;
      num[heap_size] = q;
      siftUp(heap_size);
    }
  
    long long getRoot() {
      return heap[1];
    }
  
    void extractRoot() {
      swap(1, heap_size--);
      siftDown(1);
    }

    void decreaseKey(int i, long long delta) {
      int x = pointer[i];
      heap[x] -= delta;
      siftUp(x);
    }

    void clear() {
      heap.clear();
      num.clear();
      pointer.clear();
    }
};

bool less(long long x, long long y) {
  return x < y;
}