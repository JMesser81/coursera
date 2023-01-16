#include <iostream>
#include <cassert>
#include <cstdlib>

const unsigned long long MAX = 2000000000;
int gcd_euclid(int a, int b)
{
  int r = 0;
  while (a != b)
  {
    if (b > a)
    {
      int tmp = a;
      a = b;
      b = tmp;
    }
    r = a % b;
    a = r;

    if (r == 0)
      break;
  }

  return b;
}

unsigned long long gcd_euclid_recursive(unsigned long long a, unsigned long long b)
{
  if (a == b)
    return a;

  if (b > a)
  {
    unsigned long long tmp = a;
    a = b;
    b = tmp;
  }

  unsigned long long r = a % b;
  if (r == 0)
    return b;

  return gcd_euclid_recursive(r, b);
}

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

void test_gcd()
{
  assert(gcd_euclid_recursive(18ULL,35ULL)==1ULL);
  assert(gcd_euclid_recursive(28851538ULL,1183019ULL)==17657ULL);
  assert(gcd_euclid_recursive(1ULL, 1ULL)==1);
  
  for (int i = 0; i < 100; i++) {
    unsigned long long a,b;
    a = rand() % MAX;
    b = rand() % MAX;
    assert(gcd_euclid_recursive(a, b)==gcd_naive(a, b));
  }
}

int main() {
  srand(time(0));
  //test_gcd();
  //std::cout << "Success!" << "\n";
  
  unsigned long long a, b;
  std::cin >> a >> b;
  std::cout << gcd_euclid_recursive(a, b) << std::endl;

  return 0;
}
