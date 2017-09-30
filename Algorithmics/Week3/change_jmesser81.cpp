#include <iostream>

int get_change(int m) {
  // Denominations in 1, 5, 10
  int num_10s = 0;
  int num_5s = 0;

  if (m >= 10) {
    num_10s = m / 10;
    m = m % 10;
  }

  if (m >= 5) {
    num_5s = m / 5;
    m = m % 5;
  }

  return num_10s + num_5s + m;
}

int main() {
  int m; // 1 < m < 10^3
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
