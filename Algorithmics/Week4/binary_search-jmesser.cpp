#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int BinarySearch(const vector<int> &a, int low, int high, int key) {
  if (high < low) {
    return -1;
  }

  int mid = low + ( (high-low) / 2);
  if (key == a[mid]) {
    return mid;
  } else if (key < a[mid]) {
    return BinarySearch(a, low, mid-1, key);
  } else {
    return BinarySearch(a, mid+1, high, key);
  }

}

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size(); 

  if (right == 0) {
    return -1;
  }

  return BinarySearch(a, left, right, x);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    //std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
