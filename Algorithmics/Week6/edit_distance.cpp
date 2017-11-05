#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::min;
using std::string;
using std::vector;


int edit_distance(const string &str1, const string &str2) {

  int n = str1.length();
  int m = str2.length();

  // Init Table
  vector<vector<int>> distance(n+1, vector<int>(m+1));
  for (int i = 0; i <= n; ++i)
  {
    distance[i][0] = i;
  }

  for (int j = 0; j <= m; ++j)
  {
    distance[0][j] = j;
  }

  for (int j = 1; j <= m; ++j)
  {
    for (int i = 1; i <= n; ++i)
    {
      int insertion_cost = distance[i][j-1] + 1;
      int deletion_cost = distance[i-1][j] + 1;
      int match_cost = distance[i-1][j-1];
      int mismatch_cost = distance[i-1][j-1] + 1;

      if (str1[i-1] == str2[j-1])
      {
        distance[i][j] = std::min(insertion_cost, deletion_cost);
        distance[i][j] = std::min(distance[i][j], match_cost);
      } 
      else 
      {
        /*
        std::cout << "Comparing str1[" << i << "] = " << str1[i] << " with str2[" << j << "] = " << str2[j] << std::endl;
        std::cout << "  insertion_cost = " << insertion_cost << std::endl;
        std::cout << "  deletion_cost = " << deletion_cost << std::endl;
        std::cout << "  mismatch_cost = " << mismatch_cost << std::endl;
        */
        distance[i][j] = std::min(insertion_cost, deletion_cost);
        distance[i][j] = std::min(distance[i][j], mismatch_cost);

        //std::cout << "D[" << i << "][" << j << "] = " << distance[i][j] << std::endl;
      }
    }
  }

  return distance[n][m];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
