#include <iostream>
#include <cassert>

const unsigned long long MAX = 100000000000000; // 10^14
const int PISANO_PERIOD_LENGTH_MOD10 = 60;
const int MODULO = 10;

/*
F0 = 0
F1 = 1 => 1
F2 = 1 => 1
F3 = 2 => 4
F4 = 3 => 9
F5 = 5 => 25
F6 = 8 => 64
F7 = 13 => 169

273

*/

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += (current * current) % 10;
    }

    return sum % 10;
}

int fibonacci_fast(unsigned long long n) {
    
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
      temp_fib = (temp_fib_n_1 + temp_fib_n_2) % 10;
    }

    return temp_fib;
}

int fibonacci_sum_squares_fast(unsigned long long n)
{
    int r = n % PISANO_PERIOD_LENGTH_MOD10;
    unsigned long long Fn = fibonacci_fast(r);
    //std::cout << "Fn = " << Fn << std::endl;

    r = (n - 1) % PISANO_PERIOD_LENGTH_MOD10;
    unsigned long long Fn_minus_1 = fibonacci_fast(r);
    //std::cout << "Fn_minus_1 = " << Fn_minus_1 << std::endl; 

    return (Fn* (Fn+Fn_minus_1 )) % 10;
}

void test_solution()
{
    assert(fibonacci_sum_squares_fast(1)==1);
    assert(fibonacci_sum_squares_fast(2)==2);
    assert(fibonacci_sum_squares_fast(7)==3);
    assert(fibonacci_sum_squares_fast(47)==8);
    assert(fibonacci_sum_squares_fast(73)==1);
    assert(fibonacci_sum_squares_fast(1234567890)==0);
    //assert(fibonacci_sum_squares_fast(832564823476)==1);

    /*
    for (int i = 0; i < 20; i++) {
        unsigned long long n;
        n = rand() % MAX;
        assert(fibonacci_sum_squares_fast(n)==fibonacci_sum_squares_naive(n));
    }
    */
    std::cout << "Success!" << "\n";
}

int main() {

    //test_solution();
    unsigned long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n) << std::endl;
}