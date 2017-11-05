#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath> // for ceil
#include <climits> // for LLONG_MIN, LLONG_MAX
#include <algorithm> // std::min, std::max

using std::vector;
using std::string;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

void CalcMinAndMax(int i, int j, const vector<char> &op, vector<vector<long long>> &m, vector<vector<long long>> &M)
{
  long long min = LLONG_MAX; // +inf
  long long max = LLONG_MIN; // -inf

  long long a, b, c, d = 0LL;

  for (int k = i; k < j; ++k)
  {
    a = eval(M[i][k], M[k+1][j], op[k]);
    b = eval(M[i][k], m[k+1][j], op[k]);
    c = eval(m[i][k], M[k+1][j], op[k]);
    d = eval(m[i][k], m[k+1][j], op[k]);

    min = std::min(min, a);
    min = std::min(min, b);
    min = std::min(min, c);
    min = std::min(min, d);
    
    max = std::max(max, a);
    max = std::max(max, b);
    max = std::max(max, c);
    max = std::max(max, d);
  }

  m[i][j] = min;
  M[i][j] = max;

}

void parse_expression(const string &exp, vector<int> &d, vector<char> &op)
{
  for (int i = 0; i < exp.length(); ++i)
  {
    if (i%2==0)
      d.push_back(std::stoi(&(exp[i]), nullptr));
    else
      op.push_back(exp[i]);
  }

}

long long get_maximum_value(const string &exp) {
  
  int n = ceil((float)exp.length() / (float)2.0);

  // Parse expression
  vector<int> d;
  vector<char> op;
  parse_expression(exp, d, op);

  /*
  std::cout << "exp.length() = " << exp.length() << std::endl;
  std::cout << "n = " << n << std::endl;
  std::cout << "d.size() = " << d.size() << std::endl;
  */
  
  assert(n==d.size());

  // Min and Max tables
  vector<vector<long long>> m(n, vector<long long>(n));
  vector<vector<long long>> M(n, vector<long long>(n));

  for (int i = 0; i < n; ++i)
  {
    m[i][i] = d[i];
    M[i][i] = d[i];
  }

  for (int s = 1; s < n; ++s)
  {
    for (int i = 0; i < n - s; ++i)
    {
      int j = i + s;
      CalcMinAndMax(i, j, op, m, M);
    }
  }
  
  return M[0][n-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
