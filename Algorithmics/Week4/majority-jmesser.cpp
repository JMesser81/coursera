#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int CheckMajority(vector<int> &a, int left, int right) {
	if (left == right) return -1;
	
	if (left + 1 == right) {
		if (a[left] == a[right]) {
			return a[left];
		}
		else {
			return -1;
		}
	}
	
	int mid = left + ((right - left) / 2);
	std::cout << "Sending first half from a[" << left << "] " << a[left] << " to a[" << mid << "] " << a[mid] << std::endl;
	int left_majority = CheckMajority(a, left, mid);
	std::cout << "Sending second half from a[" << mid+1 << "] " << a[mid+1] << " to a[" << right << "] " << a[right] << std::endl;
	int right_majority = CheckMajority(a, mid + 1, right);
	
	std::cout << "left_majority = " << left_majority << " right_majority = " << right_majority << std::endl;
	if ( (left_majority > 0) && (right_majority > 0) ) {
		return ( (left_majority == right_majority) ? 1 : -1);
	}
	else if ( (left_majority > 0) || (right_majority > 0) ) {
		return ( (left_majority > 0) ? left_majority : right_majority);
	}
	else {
		return -1;
	}
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) {
	  return a[left];
  }
  
  //write your code here
  return CheckMajority(a, left, right-1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
