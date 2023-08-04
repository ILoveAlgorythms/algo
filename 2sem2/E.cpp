#include <iostream>
#include <vector>
// floyd-uorshell
#define kInf 20'000'000
class Graph {
 protected:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;
  std::vector<std::vector<int>> fastest_way_;
  std::vector<int> ans_;

 public:
  std::vector<bool> incycle;
  Graph(int n) : n_(n) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    incycle.resize(n, false);
  }
  friend int operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindWays() { // есть ли отрицательный вес
    dist_.resize(n_, std::vector<int>(n_, kInf));
    fastest_way_.resize(n_, std::vector<int>(n_, -1));
    std::vector<std::vector<std::vector<int>>> dp;
    dp.resize(n_, std::vector<std::vector<int>>(n_, std::vector<int>(2, kInf)));
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
          dp[u][v][(k + 1) % 2] = std::min(dp[u][k][k % 2] + dp[k][v][k % 2], dp[u][v][k % 2]);
          if (dp[u][k][k % 2] + dp[k][v][k % 2] < dp[u][v][k % 2]) {
            if (v == k) {
              fastest_way_[u][v] = -1;
            } else {
              fastest_way_[u][v] = k;
            }
          }
        }
      }
    }
    for (int u = 0; u < n_; ++u) {
      for (int v = 0; v < n_; ++v) {
        dist_[u][v] = dp[u][v][n_% 2];
      }
    }
  }

  bool FindCycle() {
    int start = -1;
    for (int i = 0; i < n_; ++i) {
      if (dist_[i][i] < 0) {
        start = i;
        incycle[i] = true;
      }
    }
    if (start == -1) {
      return false;
    }
    std::vector<bool> used(n_, false);
    int next = fastest_way_[start][start];
    FindTrace(  )
    return true;
  }

  void FindTrace(int from, int to, std::vector<bool>& used) {
    // std::cout << from << " " << to << "\n";
    if (incycle[to] || incycle[from]) {
      return;
    }
    int middlepoint = fastest_way_[from][to];
    if (middlepoint == -1) {
      ans_.push_back(to);
      return;
    }
    if (incycle[middlepoint]) {
      return;
    }
    FindTrace(from, middlepoint, used);
    FindTrace(middlepoint, to, used);
  }

  void Print() {
    int start = ans_.back();
    int offset = 0;
    for (; ans_[offset] != start; ++offset) {}

    std::cout << "YES\n" << ans_.size() - offset << "\n";
    for (; offset < int(ans_.size()); ++offset) {
      std::cout << ans_[offset] + 1 << " ";
    }
  }
};

int operator>>(std::istream& is, Graph& g) {
  int w;
  int flag = -1;
  for (int i = 0; i < g.n_; ++i) {
    for (int j = 0; j < g.n_; ++j) {
      is >> w;
      if (i == j && w < 0) {
        flag = i;
      }
      if (w == 100'000 || i == j) {
        continue;
      }
      g.verticies_[i].push_back(std::make_pair(j, w));
    }
  }
  return flag;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr); 
  int n;
  std::cin >> n;
  Graph g(n);
  int flag = std::cin >> g;
  if (flag != -1) {
    std::cout << "YES\n" << 2 << "\n" << flag + 1 << " " << flag + 1;
    return 0;
  }
  g.FindWays();
  if (!g.FindCycle()) {
    std::cout << "NO\n";
    return 0;
  }
  g.Print();
  return 0;
}
