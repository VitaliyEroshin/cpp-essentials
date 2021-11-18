/*
  Determined Quick Sort algorithm
*/

#include <iostream>
#include <vector>
#include <utility>

std::pair<int, int> partition(std::vector<int>& a, int l, int r, int value) {
  int less = 0, equal = 0;
  for (int i = l; i < r; i++) {
    if (a[i] < value) {
      less++;
    } else if (a[i] == value) {
      equal++;
    }
  }
  std::vector<int> b(r - l);
  int i_less = 0, i_equal = less, i_bigger = less + equal;
  for (int i = l; i < r; i++) {
    if (a[i] < value) {
      b[i_less++] = a[i];
    } else if (a[i] == value) {
      b[i_equal++] = a[i];
    } else {
      b[i_bigger++] = a[i];
    }
  }
  for (int i = l; i < r; i++) {
    a[i] = b[i - l];
  }
  return {less, equal};
}

void bubble_sort_block(std::vector<int>& a, int l, int r) {
  for (int i = l; i < r; i++) {
    for (int j = i + 1; j < r; j++) {
      if (a[j] < a[i]) {
        std::swap(a[i], a[j]);
      }
    }
  }
}

int find_median(std::vector<int>& a, int l, int r) {
  bubble_sort_block(a, l, r);
  int m = (r + l) / 2;
  return a[m];
}

int kth_order_statistic(std::vector<int>& a, int k) {
  int n = a.size();

  if (n <= 5) {
    find_median(a, 0, n);
    return a[k];
  }

  std::vector<int> medians;
  for (int i = 0; i < n; i += 5) {
    int l = i, r = std::min(i + 5, n);
    medians.push_back(find_median(a, l, r));
  }
  
  int pivot = kth_order_statistic(medians, k / 5);
  std::pair<int, int> lequal = partition(a, 0, n, pivot);
  int less = lequal.first;
  int equal = lequal.second;
  if (k < less) {
    std::vector<int> segment(less);
    for (int i = 0; i < less; i++) {
      segment[i] = a[i];
    }
    return kth_order_statistic(segment, k);
  } else if (k < less + equal) {
    return a[less];
  } else {
    std::vector<int> segment(n - less - equal);
    for (int i = less + equal; i < n; i++) {
      segment[i - less - equal] = a[i];
    }
    return kth_order_statistic(segment, k - less - equal);
  }
}

void quick_sort(std::vector<int>& a, int l, int r) {
  if (r - l <= 1) {
    return;
  }
  std::vector<int> segment (r - l);
  for (int i = l; i < r; i++) {
    segment[i - l] = a[i];
  }

  int pivot = kth_order_statistic(segment, (r - l) / 2);

  std::pair<int, int> lequal = partition(a, l, r, pivot);
  int less = lequal.first;
  int equal = lequal.second;
  quick_sort(a, l, l + less);
  quick_sort(a, l + less + equal, r);
}
