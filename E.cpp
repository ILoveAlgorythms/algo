#include <deque>
#include <iostream>
#include <vector>
// floyd-uorshell

class Graph {
 protected:
  int n_;
  int m_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::vector<int>> dist_;
  std::vector<std::vector<int>> previous_in_loop_;
  void PrintCycle(int v1, int v2, std::vector<int>& trace) {
    int k = previous_in_loop_[v1][v2];
    PrintCycle(v1, k, trace);
    trace.push_back(k);
    PrintCycle(k, v2, trace);
  }

  void Answer(std::vector<std::pair<int, int>>& cycle,
              std::vector<std::pair<bool, int>> used,
              int start) {
    std::cout << "YES\n";
    std::cout << cycle.size() - used[start].second << "\n";
    while(huevina) {
        
    }
  }

 public:
  const int kInf{100000};
  Graph(int n, int m) : n_(n), m_(m) {
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
      dp[i][i][0] = 0;
      previous_in_loop_[i][i] = i;
    }
    for (int i = 0; i < n_; ++i) {
      for (auto j : verticies_[i]) {
        dp[i][j.first][0] = j.second;
        previous_in_loop_[i][j.first] =j.first;
      }
    }
    for (int k = 1; k < n_; ++k) {
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          if (dp[u][k][k % 2] + dp[k][v][k % 2] < dp[u][v][k % 2]) {
            previous_in_loop_[u][v] = k;
            dp[u][v][(k + 1) % 2] = dp[u][k][k % 2] + dp[k][v][k % 2];
            continue;
          }
          dp[u][v][(k + 1) % 2] = dp[u][v][k % 2];;
        }
      }
    }

    int start;
    std::vector<std::vector<bool>> in_negative_cycle (n_, std::vector<bool> (n_, false));
    for (int k = 0; k < n_; ++k) {
      if (dp[k][k][n_ % 2] >= 0) {
        continue;
      }
      start = k;
      for (int u = 0; u < n_; ++u) {
        for (int v = 0; v < n_; ++v) {
          in_negative_cycle[u][v] = (dp[u][k][n_ % 2] < kInf && dp[k][u][n_ % 2] < kInf);
        }
      }
    }

    std::vector<std::pair<int, int>> cycle; // from, to
    std::vector<std::pair<bool, int>> used(n_, {false, -1}); // первое -- были ли, второе -- индекс вершины в cycle
    int vert = start;
    while (!used[vert].first) {
      used[vert] = {true, cycle.size()};
      for (auto i : verticies_[vert]) {
        if (in_negative_cycle[vert][i.first]) {
          cycle.push_back({vert, i.first});
          vert = i.first;
          break;
        }
      }
    }

    Answer(cycle, used, vert);
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

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  if (g.FindWays()) {
    std::cout << "NO\n";
  }
  return 0;
}
