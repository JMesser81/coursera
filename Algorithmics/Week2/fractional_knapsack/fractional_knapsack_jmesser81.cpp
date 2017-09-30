#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;

bool is_items_available(vector<int> weights) {

  bool has_items = false;

  for (int i = 0; i < weights.size(); ++i) {
    if (weights[i] > 0) {
      has_items = true;
      break;
    }
  }
  return has_items;
}
int get_index_max_fractional_value(vector<double> fractional_values) {
  int max_fractional_value_index = 0;
  double max_fractional_value = 0.0;

  for (int i = 0; i < fractional_values.size(); ++i) {
    if (fractional_values[i] > max_fractional_value) {
      max_fractional_value = fractional_values[i];
      max_fractional_value_index = i;
    }
  }
  //std::cout.precision(10);
  //std::cout << "Item " << max_fractional_value_index << " has max fractional value = " << fractional_values[max_fractional_value_index] << std::endl;

  return max_fractional_value_index;
}

void calculate_value_per_unit_weight(vector<int> weights, vector<int> values, vector<double> &fractional_values)
{
  for (int i = 0; i < weights.size(); ++i)
  {
    if (weights[i] != 0) {
      fractional_values[i] = (double)values[i] / (double)weights[i];
    }
    else {
      fractional_values[i] = 0.0;
    }
  }
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  double max_fractional_value = 0.0;
  int current_weight = 0;

  if (capacity == 0)
  {
    return 0.0;
  }
  // write your code here
  vector<double> fractional_values;
  fractional_values.resize(weights.size());
  calculate_value_per_unit_weight(weights, values, fractional_values);

  //std::cout << "Calculated fractional value for item 0 as " << fractional_values[0] << std::endl;

  while ( (current_weight < capacity) && is_items_available(weights)) {
    int index = get_index_max_fractional_value(fractional_values);

    if (weights[index] + current_weight <= capacity)
    {
      //std::cout << "Taking all items from item " << index << std::endl;
      current_weight += weights[index];
      value += values[index];
      weights[index] = 0;
      calculate_value_per_unit_weight(weights, values, fractional_values);
    }
    else {
      int num_kgs = capacity - current_weight;
      //std::cout << "Taking " << num_kgs << " kgs from item " << index << std::endl;
      current_weight += num_kgs;
      value += num_kgs * fractional_values[index];
      //weights[index] -= num_kgs;
      //calculate_value_per_unit_weight(weights, values, fractional_values);
      break;
    }
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

  //std::cout.precision(10);
  std::cout << std::fixed;
  std::cout << std::setprecision(4);
  std::cout << optimal_value << std::endl;
  return 0;
}
