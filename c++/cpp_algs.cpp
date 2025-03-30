#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> inverseArray(const vector<vector<int>> &arr, int N) {
  vector<vector<int>> inverse;
  for (int i = 0; i < N; i++) {
    vector<int> row(N, 0);
    for (int j = 0; j < N; j++) {
      row[arr[i][j] - 1] = j;
    }
    inverse.push_back(row);
  }
  return inverse;
}
vector<string> GaleShapley(const vector<vector<int>> &M,
                           const vector<vector<int>> &W) {
  int N = M[0].size();

  queue<int> MQueue;  // maintain a list of free M entries
  for (int i = 0; i < N; i++) {
    MQueue.push(i);
  }

  vector<int> WtoM(N, -1);  // found pairs
  vector<int> MtoW(N, -1);
  vector<int> count(N);  // num of proposals by M

  // preprocess W preference in O(N) time
  vector<vector<int>> inverse = inverseArray(W, N);

  while (!MQueue.empty() && count[MQueue.front()] < N) {
    int m = MQueue.front();
    MQueue.pop();
    int w = M[m][count[m]] - 1;  // first choice on m list not yet proposed to
    count[m] += 1;

    if (WtoM[w] == -1) {
      // assign m and w to be engaged
      WtoM[w] = m;
      MtoW[m] = w;
    } else if (inverse[w][m] < inverse[w][WtoM[w]]) {
      // assign m and w to be engaged, and m' to be free
      MQueue.push(WtoM[w]);
      WtoM[w] = m;
      MtoW[m] = w;
    } else {
      // w rejects m
      MQueue.push(m);
    }
  }

  vector<string> output;
  output.push_back("(M, W)");
  for (int i = 0; i < MtoW.size(); i++) {
    output.push_back("(" + to_string(i + 1) + ", " + to_string(MtoW[i] + 1) +
                     ")");
    // cout << to_string(MtoW[i] + 1) << endl;
  }

  return output;
}