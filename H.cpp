#include <algorithm>
#include <iostream>
#include <vector>
void Print(std::vector<int>& s) {
  std::sort(s.begin(), s.end());
  std::vector<int> ans;
  for (long unsigned int i = 0; i < s.size(); ++i) {
    if (i != 0 && s[i] == s[i - 1]) {
      continue;
    }
    ans.push_back(s[i]);
  }
  std::cout << ans.size() << "\n";
  for (long unsigned int i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] + 1 << "\n";
  }
}

class Graph {
  int verticies_number_;
  int m_;
  enum Color { White, Grey, Black };
  enum IsBridge { Bridge, NotBridge };
  int time_ = 0;
  std::vector<Color> vert_colors_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<int> tup_;
  std::vector<int> tin_;
  std::vector<int> bridges_;

  int Dfs(int vert, int edge_id) {
    int neigboors = 0;
    tup_[vert] = time_;
    tin_[vert] = time_;
    ++time_;
    vert_colors_[vert] = Grey;

    for (auto i : verticies_[vert]) {
      if ((i.first == vert) || (i.second == edge_id) ||
          (vert_colors_[i.first] == Black)) {
        continue;
      }
      if (vert_colors_[i.first] == Grey) {
        tup_[vert] = std::min(tup_[vert], tin_[i.first]);
        continue;
      }
      ++neigboors;
      auto ans = Dfs(i.first, i.second);
      tup_[vert] = std::min(ans, tup_[vert]);
      if (tup_[i.first] >= tin_[vert] && edge_id != -1) {
        bridges_.push_back(vert);
      }
    }
    vert_colors_[vert] = Black;
    if (edge_id == -1 && neigboors > 1) {
      bridges_.push_back(vert);
    }
    return tup_[vert];
  }

 public:
  Graph(int n, int m) : verticies_number_(n), m_(m) {
    vert_colors_.resize(n, White);
    tup_.resize(n, -1);
    tin_.resize(n, -1);
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);

  void Do() {
    for (int i = 0; i < verticies_number_; ++i) {
      if (vert_colors_[i] == White) {
        Dfs(i, -1);
      }
    }
    Print(bridges_);
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int x;
  int y;
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y;
    --x;
    --y;
    if (x == y) {
      continue;
    }
    g.verticies_[x].push_back(std::make_pair(y, i + 1));
    g.verticies_[y].push_back(std::make_pair(x, i + 1));
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  g.Do();
  return 0;
}
