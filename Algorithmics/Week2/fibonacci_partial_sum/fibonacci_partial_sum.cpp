#include <iostream>
#include <cassert>

const unsigned long long MAX = 100000000000000; // 10^14
const int MODULO = 10;
const int PISANO_PERIOD_LENGTH_MOD10 = 60;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;
    unsigned long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % MODULO;
        sum = (sum + current) % MODULO;
    }

    return sum;
}

unsigned long long fibonacci_fast(long long n) {

    if (n == 0)
      return 0;
    else if (n == 1)
      return 1;
    
    unsigned long long temp_fib = 1L;
    unsigned long long temp_fib_n_1 = 0L;
    unsigned long long temp_fib_n_2 = 1L;

    for (long long i = 2; i < n; ++i)
    {
      temp_fib_n_1 = temp_fib_n_2;
      temp_fib_n_2 = temp_fib;
      temp_fib = (temp_fib_n_1 + temp_fib_n_2);
    }

    return temp_fib;
}

int calculate_pisano_period_length(int m)
{
    int cur_fib = 1;
    int prev_fib = 0;
    int period_length = 3; // default when m <= 2

    for (int i = 0; i < m*m; i++)
    {
        int tmp = cur_fib;
        cur_fib = (cur_fib + prev_fib) % m;
        prev_fib = tmp;
        
        //std::cout << "F_i=" << i << " mod " << m << " = " << cur_fib << "\n";
        if (prev_fib == 0 && cur_fib == 1) {
            period_length = i+1;
            break;
        }
    }
    return period_length;
}

int fibonacci_sum_fast(long long n, int pisano_period_length)
{
    
    // Find the remainder of n mod pisano_period_length
    int r = n % pisano_period_length;
    return (fibonacci_fast(r+2) - 1) % MODULO;
}

long long fibonacci_partial_sum_fast(long long m, long long n)
{
    assert(m <= n);

    int pisano_period_length = calculate_pisano_period_length(MODULO);
    if (m == n) {
        // Find the remainder of n mod pisano_period_length
        int r = n % pisano_period_length;
        return fibonacci_fast(r) % MODULO;
    }

    long long F_m = 0;
    long long F_n = 0;
    int diff = 0;

    if (m == 0)
        F_m = 0;
    else if (m == 1)
        F_m = 0;
    else
        F_m = fibonacci_sum_fast(m-1, pisano_period_length);

    if (n == 0)
        F_n = 0;
    else if (n == 1)
        F_n = 1;
    else
        F_n = fibonacci_sum_fast(n, pisano_period_length);

    diff = F_n - F_m; 
    if (diff < 0)
        diff += MODULO;

    //std::cout << "[Fast] sum(F_" << n << ") = " << F_n << " diff[F_" << m << "] = " << F_m << " => (F_n - F_m) = " << diff << std::endl;
    return diff;
}

unsigned long long fibonacci_partial_sum_naive(long long m, long long n)
{
    assert(m <= n);

    unsigned long long diff = fibonacci_sum_naive(m-1);
    unsigned long long sum = fibonacci_sum_naive(n);

    //std::cout << "[Naive] sum(" << n << ") = " << sum << " diff = " << diff << " => (sum - diff) = " << (sum-diff) << std::endl;
    return (sum - diff) % 10;
}

void test_solution()
{
    assert(calculate_pisano_period_length(MODULO)==60);
    
    assert(fibonacci_fast(10)==55);

    assert(fibonacci_sum_fast(3, PISANO_PERIOD_LENGTH_MOD10)==4);
    assert(fibonacci_sum_fast(100, PISANO_PERIOD_LENGTH_MOD10)==5);
    assert(fibonacci_sum_fast(1234, PISANO_PERIOD_LENGTH_MOD10)==1);
    assert(fibonacci_sum_fast(12345, PISANO_PERIOD_LENGTH_MOD10)==2);
    
    assert(fibonacci_partial_sum_fast(0, 1)==1);
    assert(fibonacci_partial_sum_fast(1,2)==2);
    assert(fibonacci_partial_sum_fast(3,7)==1);
    assert(fibonacci_partial_sum_fast(10,10)==5);
    assert(fibonacci_partial_sum_fast(1234,12345)==8);
    assert(fibonacci_partial_sum_fast(10,200)==2);

    /*
    for (int i = 0; i < 20; i++) {
        unsigned long long a,b;
        a = rand() % MAX;
        b = rand() % MAX;
        if (a > b)
            continue;

        std::cout << "m = " << a << " n = " << b << std::endl;
        assert(fibonacci_partial_sum_fast(a,b)==fibonacci_partial_sum_naive(a,b));
   }
   */
    std::cout << "Success!" << "\n";

}

int main() {

    //test_solution();

    long long n, m = 0;
    std::cin >> m;
    std::cin >> n;
    std::cout << fibonacci_partial_sum_fast(m, n) << std::endl;
}
