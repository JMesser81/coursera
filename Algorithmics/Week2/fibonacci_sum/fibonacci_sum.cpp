#include <iostream>
#include <cassert>

const unsigned long long MAX = 100000000000000ULL;
const int PISANO_PERIOD_LENGTH_MOD10 = 60;
const int MODULO = 10;

unsigned long long fibonacci_sum_naive(unsigned long long n) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0ULL;
    unsigned long long current  = 1ULL;
    unsigned long long sum      = 1ULL;

    for (long long i = 0; i < n - 1; ++i) {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum = (sum + current) % 10;
    }

    //std::cout << sum << std::endl;
    return sum;
}

unsigned long long fibonacci_fast(unsigned long long n) {

    if (n == 0)
      return 0;
    else if (n == 1)
      return 1;
    
    unsigned long long temp_fib = 1L;
    unsigned long long temp_fib_n_1 = 0L;
    unsigned long long temp_fib_n_2 = 1L;

    for (unsigned long long i = 2; i < n; ++i)
    {
      temp_fib_n_1 = temp_fib_n_2;
      temp_fib_n_2 = temp_fib;
      temp_fib = (temp_fib_n_1 + temp_fib_n_2);
    }

    return temp_fib;
}

unsigned long long fibonacci_sum_fast(unsigned long long n)
{
    //return ((2*fibonacci_fast(n) + fibonacci_fast(n-1)) - 1) % 10;
    //std::cout << "Calling fibonacci_fast for n + 2 = " << n+2 << std::endl;
    //return (fibonacci_fast(n+2) - 1) % 10;

    int r = n % PISANO_PERIOD_LENGTH_MOD10;
    return (fibonacci_fast(r+2) - 1) % MODULO;
}

void test_solution()
{
    
    for (int i = 0; i < 20; i++)
    {
        assert(fibonacci_sum_fast(i)==fibonacci_sum_naive(i));
    }

    assert(fibonacci_sum_fast(239)==fibonacci_sum_naive(239));
    assert(fibonacci_sum_fast(100)==fibonacci_sum_naive(100));
    assert(fibonacci_sum_fast(832564823476)==fibonacci_sum_naive(832564823476));

    
    for (int i = 0; i < 20; i++) {
        unsigned long long a,b;
        a = rand() % MAX;
        assert(fibonacci_sum_fast(a)==fibonacci_sum_naive(a));
    }
    
    std::cout << "Success!" << "\n";

}

int main() {

    //test_solution();
    unsigned long long n = 0;
    std::cin >> n;
    assert(n >= 0);
    assert(n <= MAX);

    std::cout << fibonacci_sum_fast(n) << std::endl;
}