#include <vector>

int mergeSort(std::vector<int>& a, std::vector<int>& buffer, int left, int right) {
  int inversions = 0;

  if (right - left == 1) 
    return 0;

  int mid = (right + left) / 2;

  inversions += mergeSort(a, buffer, left, mid);
  inversions += mergeSort(a, buffer, mid, right);

  int j_left = left, j_right = mid;
  
  for (int i = 0; i < right - left; i++) {
    if (j_right == right) {
      buffer[i] = a[j_left];
      j_left++;
    } else if (j_left == mid) {
      buffer[i] = a[j_right];
      j_right++;
    } else if (a[j_left] <= a[j_right]) {
      buffer[i] = a[j_left];
      j_left++;
    } else {
      buffer[i] = a[j_right];
      inversions += mid - j_left;
      j_right++;
    }
  }

  for (int i = 0; i < right - left; i++) {
    a[left + i] = buffer[i];
  }

  return inversions;
}