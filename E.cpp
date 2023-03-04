#include <deque>
#include <iostream>
#include <vector>
// floyd-uorshell

class Graph {
 protected:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;
  std::vector<std::vector<int>> previous_in_loop_;
  static void Print(std::vector<int>& trace) {
    std::cout << "YES\n" << trace.size();
    for (auto i : trace) {
      std::cout << i + 1 << " ";
    }
  }

  void FindTrace(int v1, int v2, std::vector<int>& trace) {
    int k = previous_in_loop_[v1][v2];
    if (k == v2) {
      trace.push_back(k);
      return;
    }
    FindTrace(v1, k, trace);
    trace.push_back(k);
    FindTrace(k, v2, trace);
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
    previous_in_loop_.resize(n, std::vector<int>(n, -1));
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  bool FindWays() {
    dist_.resize(n_, std::vector<int>(n_, kInf));
    std::vector<std::vector<std::vector<int>>> dp;
    dp.resize(n_, std::vector<std::vector<int>>(n_, std::vector<int>(2, kInf)));
    for (int i = 0; i < n_; ++i) {
      dp[i][i][1] = 0;
      previous_in_loop_[i][i] = i;
    }
    for (int i = 0; i < n_; ++i) {
      for (auto j : verticies_[i]) {
        dp[i][j.first][1] = j.second;
        // std::cout << dp[i][j.first][0];
        previous_in_loop_[i][j.first] =j.first;
      }
    }
    int k = 0;
    for (; k < n_; ++k) { // k -- номер первой вершины, которая есть помимо u и v
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          // std::cout << "u, v, k:" << u << " " << v << " " << k << "\n   " <<dp[u][k][k % 2]  << " " <<  dp[k][v][k % 2] << "\n";
          if (dp[u][k][(k + 1) % 2] + dp[k][v][(k + 1) % 2] < dp[u][v][(k + 1) % 2]) {
            previous_in_loop_[u][v] = k;
            dp[u][v][k % 2] = dp[u][k][(k + 1) % 2] + dp[k][v][(k + 1) % 2];
            continue;
          }
          dp[u][v][k % 2] = dp[u][v][(k + 1) % 2];
        }
      }
    }

    // for (int k = 0; k <2; ++k) {
    //   std::cout << "----- k = " << k << "\n";
    //   for (int u = 0; u < n_; ++u) {
    //     for (int v = 0; v < n_; ++v) {
    //       std::cout  <<dp[u][v][k % 2] <<  " ";
    //     }
    //     std::cout << "\n";
    //   }
    // }

    for (int u = 0; u < n_; ++u) {
      for (int v = 0; v < n_; ++v) {
        dist_[u][v] = dp[u][v][(k + 1) % 2];
      }
    }
    return false;
    int start = FindVertexInCycle(dist_);
    if (start == -1) {
      return true;
    }
    std::vector<int> ans;
    FindTrace(start, start, ans);
    Print(ans);
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int w;
  for (int i = 0; i < g.n_; ++i) {
    for (int j = 0; j < g.n_; ++j) {
      is >> w;
      if (w == g.kInf || i == j) {
        continue;
      }
      g.verticies_[i].push_back(std::make_pair(j, w));
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
  for (int i = 0; i < g.n_; ++i) {
    for (int j = 0; j < g.n_; ++j) {
      os << g.dist_[i][j] << " ";
    }
    os << "\n";
  }
  return os;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  Graph g(n);
  std::cin >> g;
  if (g.FindWays()) {
    std::cout << "NO\n";
  }
  std::cout << g;
  return 0;
}
