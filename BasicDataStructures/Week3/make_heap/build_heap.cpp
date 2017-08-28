#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftDown(int index)
  {
    int minIndex = index;
    int leftChildIndex = (2*index) + 1;
    int rightChildIndex = (2*index) + 2;

    if (leftChildIndex < data_.size() && data_[leftChildIndex] < data_[minIndex])
    {
      minIndex = leftChildIndex;
    }

    if (rightChildIndex < data_.size() && data_[rightChildIndex] < data_[minIndex])
    {
      minIndex = rightChildIndex;
    }

    if (index != minIndex)
    {
      swap(data_[index], data_[minIndex]);
      swaps_.push_back(make_pair(index, minIndex));
      SiftDown(minIndex);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //

    for (int i = data_.size() / 2; i >= 0; --i)
    {
      SiftDown(i);
    }

    // TODO: replace by a more efficient implementation
    /*
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
    */
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
