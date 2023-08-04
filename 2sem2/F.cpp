#include <iostream>
#include <vector>
#include <forward_list>
//расстояние между любыми двумя вершинами
#define kInf 100'000'000

class Graph {
 protected:
  int n_;
  int m_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> fastest_way_;
  std::vector<std::vector<int>> dist_;
 public:
  std::vector<std::vector<int>> numbers;
  std::vector<bool> incycle;
  std::vector<int> ans;
  Graph(int n, int m) : n_(n), m_(m) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    numbers.resize(n, std::vector<int>(n));
    incycle.resize(n, false);
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  bool FindWays() { // есть ли отрицательный вес
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
    return CheckCycle();
  }

  bool CheckCycle() {
    bool flag = false;
    for (int i = 0; i < n_; ++i) {
      if (dist_[i][i] < 0) {
        incycle[i] = true;
        flag = true;
      }
    }
    return flag;
  }

  void FindTrace(int from, int to, bool& corrupted) {
    // std::cout << from << " " << to << "\n";
    if (incycle[to] || incycle[from]) {
      corrupted = true;
      return;
    }
    int middlepoint = fastest_way_[from][to];
    if (middlepoint == -1) {
      ans.push_back(to);
      return;
    }
    if (incycle[middlepoint]) {
      corrupted = true;
      return;
    }
    FindTrace(from, middlepoint, corrupted);
    FindTrace(middlepoint, to, corrupted);
  }

  void Print() {
    for (auto i : fastest_way_) {
      for (auto j : i) {
        std::cout << j << " ";
      }
      std::cout << "\n";
    }
    for (auto i : dist_) {
      for (auto j : i) {
        std::cout << j << " ";
      }
      std::cout << "\n";
    }
  }

  bool DoubleCheck(int start, int finish) {
    for (int i = 0; i < n_; ++i) {
      if (incycle[i] && dist_[start][i] < kInf / 2 && dist_[i][finish] < kInf / 2) {
        return true;
      }
    }
    return false;
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
    g.verticies_[x].push_back(std::make_pair(y, -w)); // - чтобы искать отрицательный вес
    g.numbers[x][y] = i + 1;
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

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    is >> vec[i];
    --vec[i];
  }
  return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    os << vec[i] + 1 << " ";
  }
  return os;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  std::vector<int> lectures(k);
  Graph g(n, m);
  std::cin >> g >> lectures;
  g.FindWays();
  
  g.ans.push_back(lectures[0]);
  // bool corrupted = g.DoubleCheck(lectures[0], lectures.back());
  bool corrupted = false;
  g.Print();
  for (size_t i = 0; i < lectures.size() - 1; ++i) {
    if (lectures[i] == lectures[i + 1]) {
      continue;
    }
    if (g.incycle[lectures[i]] || g.incycle[lectures[i + 1]]) {
      corrupted = true;
      break;
    }
    g.FindTrace(lectures[i], lectures[i + 1], corrupted);
    if (corrupted) {
      break;
    }
  }
  if (corrupted) {
    std::cout << "infinitely kind";
    return 0;
  }
  std::cout << g.ans.size() - 1 << "\n";
  for (size_t i = 0; i < g.ans.size() - 1; ++i) {
    std::cout << g.numbers[g.ans[i]][g.ans[i + 1]] << " ";
  } 
  return 0;
}
