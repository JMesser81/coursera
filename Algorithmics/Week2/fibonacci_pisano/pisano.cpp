#include <iostream>
#include <vector>
#include <cassert>

/*

Sample 1.
Input:
239 1000
Output:
161
𝐹239 mod 1 000 = 39 679 027 332 006 820 581 608 740 953 902 289 877 834 488 152 161 (mod 1 000) = 161.

Sample 2.
Input:
2816213588 239
Output:
151
𝐹2816213588 does not fit into one page of this file, but 𝐹2816213588 mod 239 = 151.

*/
const unsigned long long MAX_N = 100000000000000ULL; // 10^14
const unsigned int MAX_M = 1000; // 10^3

unsigned long long fibonacci_fast(int n, int m) {
    // iterative solution

    if (n == 0)
      return 0;
    else if (n == 1)
      return 1;
    
    long long temp_fib = 1L;
    long long temp_fib_n_1 = 0L;
    long long temp_fib_n_2 = 1L;
    for (int i = 2; i < n; ++i)
    {
      temp_fib_n_1 = temp_fib_n_2;
      temp_fib_n_2 = temp_fib;
      temp_fib = (temp_fib_n_1 + temp_fib_n_2) % m;
    }

    return temp_fib;
}

int calculate_pisano_period(int m)
{
    int cur_fib = 1;
    int prev_fib = 0;
    for (int i = 0; i < m*m; i++)
    {
        int tmp = cur_fib;
        cur_fib = (cur_fib + prev_fib) % m;
        prev_fib = tmp;
        
        //std::cout << "F_i=" << i << " mod " << m << " = " << cur_fib << "\n";
        if (prev_fib == 0 && cur_fib == 1)
            return i+1;
    }

    return 3;
}

unsigned long long get_fibonacci_huge_fast(unsigned long long n, unsigned int m)
{
  // Compute the Pisano period length - max length is m*m
  int pisano_period_length = calculate_pisano_period(m);
  //std::cout << "Pisano Period Length = " << pisano_period_length << std::endl;
  
  // Find the remainder of n mod pisano_period_length
  int r = n % pisano_period_length;
  //std::cout << "Remainder = " << r << std::endl;

  unsigned long long fib = fibonacci_fast(r, m);
  //std::cout << "Fibonacci " << r << " => " << fib << std::endl;

  return fib;
}

unsigned long long get_fibonacci_huge_naive(unsigned long long n, unsigned long long m) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;

    for (unsigned long long i = 0; i < n - 1; ++i) {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

void test_solution() {
    // Check pisano period length calculations first
    assert(calculate_pisano_period(2) == 3);
    assert(calculate_pisano_period(3) == 8);

    assert(get_fibonacci_huge_fast(2015, 3)==fibonacci_fast(2015, 3));
    assert(get_fibonacci_huge_fast(239, 1000)==fibonacci_fast(239, 1000));
    //assert(get_fibonacci_huge_fast(2816213588, 239)==fibonacci_fast(2816213588, 239));
    //std::cout << "F_2816213588 mod 239 = " << get_fibonacci_huge_fast(2816213588,239) << "\n";

    for (int i = 0; i < 100; i++) {
      unsigned long long a,b;
      a = rand() % MAX_N;
      b = rand() % MAX_M;
      assert(get_fibonacci_huge_fast(a, b)==fibonacci_fast(a, b));
   }
    std::cout << "Success!" << "\n";
}

int main() {
    
  //test_solution();

  long long n, m;
  std::cin >> n >> m;
  
  // F_n % m = F_r % m
  std::cout << get_fibonacci_huge_fast(n,m) << '\n';
  return 0;
}
