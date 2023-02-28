#include <deque>
#include <iostream>
#include <vector>
// расстояние от одной вершины до всех остальных, 
// отицательные рёбра разрешены

class Graph {
  const int kInf = 2'009'000'999;

 protected:
  int n_;
  int m_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<int> dist_;
 public:
  Graph(int n, int m) : n_(n), m_(m) {
    verticies_.resize(n_, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindWays(int start) {
    dist_.resize(n_, kInf);
    std::vector<std::vector<int>> dp;
    dp.resize(n_, std::vector<int>(2, kInf));
    dp[start][0] = 0;
    dp[start][1] = 0;
    for (int k = 1; k < n_; ++k) {
      for (int i = 0; i < n_; ++i) {
        if (dp[i][(k - 1) % 2] == kInf) {
          continue;
        }
        for (auto j : verticies_[i]) {
          dp[j.first][k % 2] = std::min(dp[j.first][k % 2], dp[i][(k - 1) % 2] + j.second);
        }       
      }
    }

    for (int i = 0; i < n_; ++i) {
      dist_[i] = dp[i][(n_ - 1)% 2];
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
  for (int j = 0; j < g.n_; ++j) {
    os << g.dist_[j] << " ";
  }
  os << "\n";
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
  int start;
  std::cin >> start;
  --start;
  g.FindWays(start);
  std::cout << g;
  return 0;
}
