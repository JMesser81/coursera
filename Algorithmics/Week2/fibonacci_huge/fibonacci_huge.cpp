#include <iostream>
#include <cassert>

const int modulo = 10;

int get_fibonacci_last_digit(int n, int m) {
    if (n <= 1)
        return n;

    
    int last_digit = 1;     // for n = 2, f(2) = 1 so we'll use this to start
    int temp_fib_n_1 = 1;   // f(2-1) = f(1) = 1;
    int temp_fib_n_2 = 0;   // f(2-2) = f(0) = 0;

    for (int i = 2; i < n; ++i)
    {
        temp_fib_n_2 = temp_fib_n_1;
        temp_fib_n_1 = last_digit;
        last_digit = (temp_fib_n_2 + temp_fib_n_1) % m;
    }

    return last_digit;
}

long long fibonacci_fast(int n) {
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
      temp_fib = temp_fib_n_1 + temp_fib_n_2;
    }

    return temp_fib;
}

void test_solution() {
    assert(get_fibonacci_last_digit(3,10) == 2);
    assert(get_fibonacci_last_digit(10,10) == 5);
    assert(get_fibonacci_last_digit(139,10) == 1);
    assert(get_fibonacci_last_digit(91239,10) == 6);
    assert(get_fibonacci_last_digit(327305,10) == 5);

    for (int n = 0; n < 45; ++n)
        assert(fibonacci_fast(n) % modulo == get_fibonacci_last_digit(n,modulo));

    std::cout << "Successful" << "\n";
}

int main() {

    //test_solution();

    int n;
    std::cin >> n;
    std::cout << get_fibonacci_last_digit(n, modulo) << '\n';
}

// f(n-2) + f(n-1)
// f(2) = f(0) + f(1) => last_digit = 1;
//         0   +   1
// f(3) = f(1) + f(2) => last_digit = 2;
//         1  +  1
// f(4) = f(2) + f(3) => last_digit = 3;
//         1   +  2
// f(5) = f(3) + f(4) => last_digit = 5
//         2   +  3