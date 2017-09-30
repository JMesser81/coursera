#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
	int x = a[l];
	m1 = m2 = l;

	std::cout << "Pivot x = " << x << std::endl;
	for (int k = l + 1; k <= r; k++) {
		if (a[k] < x) {
			m1++;
			m2++;
			swap(a[k], a[m2]);			
		}
		else if (a[k] == x) {			
			m2++;
			swap(a[k], a[m1]);
		}		
	}
	swap(a[l], a[m2]);
	//swap(a[m2], a[m1]);
	
	std::cout << "m1 = " << m1 << " m2 = " << m2 << std::endl;	
	for (size_t i = l; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << std::endl;	
	
}

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  
  int m1, m2;
  partition3(a, l, r, m1, m2);
  //std::cout << "m1 = " << m1 << " m2 = " << m2 << std::endl;

  randomized_quick_sort(a, l, m1 - 1);
  randomized_quick_sort(a, m2 + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
