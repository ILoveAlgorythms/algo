#include <deque>
#include <iostream>
#include <vector>

class Graph {
 protected:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;

 public:
  Graph(int n) : n_(n) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindWays() {
    dist_.resize(n_, std::vector<int>(n_, 110000));
    std::vector<std::vector<std::vector<int>>> dp;
    dp.resize(n_,
              std::vector<std::vector<int>>(n_, std::vector<int>(2, 110000)));
    for (int i = 0; i < n_; ++i) {
      dp[i][i][0] = 0;
    }
    for (int j = 0; j < n_; ++j) {
      for (auto i : verticies_[j]) {
        dp[j][i.first][0] = i.second;
      }
    }
    for (int k = 0; k < n_; ++k) {
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          dp[u][v][(k + 1) % 2] =
              std::min(dp[u][k][k % 2] + dp[k][v][k % 2], dp[u][v][k % 2]);
        }
      }
    }

    for (int u = 0; u < n_; ++u) {
      for (int v = 0; v < n_; ++v) {
        dist_[u][v] = dp[u][v][n_ % 2];
      }
    }
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int w;
  for (int x = 0; x < g.n_; ++x) {
    for (int y = 0; y < g.n_; ++y) {
      is >> w;
      if (x == y) {
        continue;
      }
      if (w == 1) {
        g.verticies_[x].push_back(std::make_pair(y, w));
      }
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
  for (int i = 0; i < g.n_; ++i) {
    for (int j = 0; j < g.n_; ++j) {
      os << (g.dist_[i][j] == 110000 ? 0 : 1) << " ";
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
  g.FindWays();
  std::cout << g;
  return 0;
}
