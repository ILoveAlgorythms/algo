#include <deque>
#include <iostream>
#include <vector>
// floyd-uorshell

class Graph {
 protected:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;
  std::deque<int> ans_;
  void Print() {
    std::cout << "YES\n" << ans_.size();
    for (auto i : ans_) {
      std::cout << i + 1 << " ";
    }
  }

  void FindTrace(int start, std::vector<std::vector<int>> previous) {
    int i = start;
    do {
      ans_.push_back(i);
      i = previous[start][i];
    } while (i != start);
  }

  int FindVertexInCycle(std::vector<std::vector<int>>& v) const {
    for (int i = 0; i < n_; ++i) {
      if (v[i][i] < 0) {
        return i;
      }
    }
    return -1;
  }

 public:
  const int kInf{100000};
  Graph(int n) : n_(n) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    // previous_in_loop_.resize(n, std::vector<int>(n, -1));
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  bool FindWays() {
  std::cout << "231432414";
    dist_.resize(n_, std::vector<int>(n_, kInf));
    std::vector<std::vector<std::vector<int>>> dp;
    std::vector<std::vector<std::vector<int>>> previous_in_loop;
    dp.resize(n_, std::vector<std::vector<int>>(n_, std::vector<int>(2, kInf)));
    previous_in_loop.resize(n_, std::vector<std::vector<int>>(n_, std::vector<int>(2, kInf)));
    for (int i = 0; i < n_; ++i) {
      dp[i][i][1] = 0;
      previous_in_loop[i][i][1] = i;
    }
    for (int i = 0; i < n_; ++i) {
      for (auto j : verticies_[i]) {
        dp[i][j.first][1] = j.second;
        previous_in_loop[i][j.first][1] = i;
      }
    }
    int k = 0;
    for (; k < n_; ++k) { // k -- номер первой вершины, которая есть помимо u и v
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          // std::cout << "u, v, k:" << u << " " << v << " " << k << "\n   " <<dp[u][k][k % 2]  << " " <<  dp[k][v][k % 2] << "\n";
          if (dp[u][k][(k + 1) % 2] + dp[k][v][(k + 1) % 2] < dp[u][v][(k + 1) % 2]) {
            dp[u][v][k % 2] = dp[u][k][(k + 1) % 2] + dp[k][v][(k + 1) % 2];
            previous_in_loop[u][v][(k) % 2] = (v == k ? previous_in_loop[u][v][(k + 1) % 2] 
                                                      : previous_in_loop[k][v][(k + 1) % 2]);
            continue;
          }
          previous_in_loop[u][v][(k) % 2] = previous_in_loop[u][v][(k + 1) % 2];
          dp[u][v][k % 2] = dp[u][v][(k + 1) % 2];
        }
      }
    }
    --k;
    for (int u = 0; u < n_; ++u) {
      for (int v = 0; v < n_; ++v) {
        dist_[u][v] = dp[u][v][(k) % 2];
      }
    }
    int start = FindVertexInCycle(dist_);
    if (start == -1) {
      return true;
    }
    std::cout << "---";
    FindTrace(start, previous_in_loop[k & 2]);
    std::cout << "dalsmdsal"; 
    Print();
    return false;
  }

};

std::istream& operator>>(std::istream& is, Graph& g) {
  int w;
  int i = 0;
  for (; i < g.n_; ++i) {
    for (int j = 0; j < g.n_; ++j) {
      is >> w;
      if (w == g.kInf || i == j) {
        continue;
      }
      g.verticies_[i].push_back(std::make_pair(j, w));
      // std::cout << "i: " << i << "  j :  " << j << g.n_ - 1<< "\n";
    }
  }
  // std::cout << "finish";
  return is;
}


int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  Graph g(n);
  std::cin >> g;
  std::cout << "2312";
  int a = 4;
  std::cin >> a;
  g.FindWays();
  // if (g.FindWays()) {
    // std::cout << "NO\n";
  // }
  return 0;
}
