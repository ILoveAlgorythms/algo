#include <deque>
#include <iostream>
#include <vector>
//расстояние между любыми двумя вершинами

class Graph {
 protected:
  int n_;
  int m_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;
 public:
  Graph(int n, int m) : n_(n), m_(m) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindWays() {
    dist_.resize(n_, std::vector<int>(n_, 110000));
    std::vector<std::vector<std::vector<int>>> dp;
    dp.resize(n_, std::vector<std::vector<int>>(n_, std::vector<int>(2, 110000)));
    for (int i = 0; i < n_; ++i) {
      dp[i][i][0] = 0;
    }
    for (int j = 0; j < n_; ++j) {
      for (auto i : verticies_[j]) {
        dp[j][i.first][0] = i.second;
      }
    }
    for (int k = 0; k < n_; ++k) { //n_ -1?
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          // std::cout << k << " _ " << u << " _ " << v << " _ " << dp[u][k][k % 2] + dp[k][v][k % 2] << " ";
          dp[u][v][(k + 1) % 2] = std::min(dp[u][k][k % 2] + dp[k][v][k % 2], dp[u][v][k % 2]);
        }
      }
      // std::cout << "\n";
    }

    for (int u = 0; u < n_; ++u) {
      for (int v = 0; v < n_; ++v) {
        dist_[u][v] = dp[u][v][(n_ )% 2];
      }
    }
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int x;
  int y;
  int w;
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y >> w;
    --x;
    --y;
    if (x == y) {
      continue;
    }
    g.verticies_[x].push_back(std::make_pair(y, w));
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
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  g.FindWays();
  std::cout << g;
  return 0;
}
