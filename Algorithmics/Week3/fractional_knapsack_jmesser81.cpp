#include <iostream>
#include <vector>

using std::vector;

double[] get_fractional_values(vector<int> weights, vector<int> values) {

  double fractional_values[weights.size()];

  for (int i = 0; i < weights.size(); ++i)
  {
    if (weights[i] == 0.0)
    {
      continue;
    }

    fractional_values[i] = (double)(values[i] / weights[i]);
  }

  return fractional_values;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int num_items = weights.size();

  // Find greatest fractional value - O(n)
  double fractional_values[num_items];
  fractional_values = get_fractional_values(weights, values);

  // Sort fractional values - O(n log n)
  // TODO - Need to save original indices to get weight

  double max_fractional_value;
  while (capacity > 0) {

    max_fractional_value = 0.0;

    // Find next largest fractional index - O(n)
    int greatest_fractional_value_index = -1;
    for (int i = 0; i < num_items; ++i) {
      if ( (weights[i] > 0) && (fractional_values[i] > max_fractional_value) ) {
        max_fractional_value = fractional_values[i];
        greatest_fractional_value_index = i;
      }
    }

    // Determine how much of w_i we can take
    int a = std::min(weights[greatest_fractional_value_index], capacity);
    value += a*(max_fractional_value);

    // Reduce a from w_i
    weights[greatest_fractional_value_index] -= a;
    capacity -= a;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
