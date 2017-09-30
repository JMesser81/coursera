#include <iostream>
#include <cassert>

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

long long lcm_optimized(int a, int b)
{
  long long tmp = (long long) a / gcd_euclid(a,b);
  return (long long) tmp * b;
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

void test_solution() {
    assert(lcm_optimized(6, 8) == 24);
    assert(lcm_optimized(28851538, 1183019) == 1933053046LL);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_optimized(a, b) << std::endl;
  //test_solution();
  return 0;
}
