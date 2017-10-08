#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

void printarray(const vector<int> &in) {
  for (auto ch : in) {
		std::cout << ch << ' ';
	}
	std::cout << std::endl;	
}

void printmidpoints(const vector<int> &in, int l, int r, int m1, int m2) {
  
  for (size_t i = 0; i <= (size_t)r; ++i) {
    if ( (i > 0) && (i == (size_t)l) ) {
      std::cout << "    ";
    }
    std::cout << in[i] << ' ';
  }
  std::cout << std::endl;

  for (size_t i = 0; i <= (size_t)r; ++i) {
    if ( (i > 0) && (i == (size_t)l) ) {
      std::cout << "    ";
    }

    if (i == (size_t)m1) {
      std::cout << "a";
    } else {
      std::cout << "  ";
    }
  }
  std::cout << std::endl;

  for (size_t i = 0; i <= (size_t)r; ++i) {
    if ( (i > 0) && (i == (size_t)l) ) {
      std::cout << "    ";
    }

    if (i == (size_t)m2) {
      std::cout << "b";
    } else {
      std::cout << "  ";
    }
  }
	std::cout << std::endl;	
}

void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
	int x = a[l];
	m1 = m2 = l;

  m1 = l+1;

	for (int k = l+1; k <= r; k++) {
		if (a[k] < x) {
      m1++;
      m2++;
      swap(a[k], a[(m1-1)]);

      if (a[k] < a[m2]) {
        swap(a[k], a[m2]);
      }

		}
		else if (a[k] == x) {			
			m2++;
      swap(a[k], a[m2]);
    }
  }
  
  swap(a[l], a[(m1-1)]);
  if (a[(m1-1)] == x) {
    m1--;
  }

  //printmidpoints(a, l, r, m1, m2);
	//printarray(a);
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
  //std::cout << "Swapping a[" << l << "] with pivot at location a[" << k << "] = " << a[k] << std::endl;
  swap(a[l], a[k]);
  //printarray(a);
  //int m = partition2(a, l, r);
  
  int m1, m2;
  partition3(a, l, r, m1, m2);
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
  printarray(a);
}
