#include "cpp_algs.cpp"
using namespace std;

int main(int argc, char **argv) {
  vector<vector<int>> M = {{2, 1, 3}, {3, 1, 2}, {3, 2, 1}};
  vector<vector<int>> W = {{2, 1, 3}, {3, 2, 1}, {3, 1, 2}};

  vector<string> results = GaleShapley(M, W);

  // format output
  cout << "found output =    [";
  for (int i = 0; i < results.size(); i++) {
    cout << results[i];
    if (i < results.size() - 1) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
  cout << "expected output = [(M, W), (1, 2), (2, 1), (3, 3)]" << endl;
}