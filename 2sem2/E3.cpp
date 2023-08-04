#include <iostream>
#include <vector>

#define kInf 20'000'000
class Graph {
 protected:
  int n_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<int> dist_;
  std::vector<int> previous_;
  std::vector<int> ans_;

 public:
  std::vector<bool> incycle;
  Graph(int n) : n_(n) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    incycle.resize(n, false);
  }
  friend int operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FillLast() {
    for (int i = 0; i < n_ - 1; ++i) {
      verticies_.back().push_back({i, 0});
    }
  }

  void FindWays(int start) {
    dist_.resize(n_, kInf);
    previous_.resize(n_, -1);
    std::vector<std::vector<int>> dp;
    dp.resize(n_, std::vector<int>(2, kInf));
    dp[start][0] = 0;
    // dp[start][1] = 0;
    for (int k = 1; k < n_; ++k) {
      for (int i = 0; i < n_; ++i) {
        if (dp[i][(k - 1) % 2] == kInf) {
          continue;
        }
        for (auto j : verticies_[i]) {
          dp[j.first][k % 2] = std::min(dp[j.first][k % 2], dp[i][(k - 1) % 2] + j.second);
          if (dp[j.first][k % 2] < dp[i][(k - 1) % 2] + j.second) {
            previous_[j.first] = 
          }
        }       
      }
    }

    for (int i = 0; i < n_; ++i) {
      dist_[i] = dp[i][(n_ - 1) % 2];
      if (dist_[i] < dp[i][(n_ - 2) % 2]) {

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
    FindTrace(    )
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
  if (n == 1) {
    std::cout << "NO\n";
    return 0;
  }
  Graph g(n + 1);
  int flag = std::cin >> g;
  if (flag != -1) {
    std::cout << "YES\n" << 2 << "\n" << flag + 1 << " " << flag + 1;
    return 0;
  }
  g.FillLast();
  g.FindWays(n);
  if (!g.FindCycle()) {
    std::cout << "NO\n";
    return 0;
  }
  g.Print();
  return 0;
}
