#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
  int verticies_number_;
  int m_;
  enum Color { White, Grey, Black };
  int time_ = 0;
  std::vector<Color> vert_colors_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<int> tup_;
  std::vector<int> tin_;
  std::vector<bool> bridges_;

  int Dfs(int vert, int edge_id) {
    tup_[vert] = time_;
    tin_[vert] = time_;
    ++time_;
    vert_colors_[vert] = Grey;

    for (auto& i : verticies_[vert]) {
      if ((i.first == vert) || (i.second == edge_id) ||
          (vert_colors_[i.first] == Black)) {
        continue;
      }
      if (vert_colors_[i.first] == Grey) {
        tup_[vert] = std::min(tup_[vert], tin_[i.first]);
        continue;
      }
      auto ans = Dfs(i.first, i.second);
      tup_[vert] = std::min(ans, tup_[vert]);
      if (tup_[i.first] == tin_[i.first]) {
        bridges_[i.second] = true;
      }
    }
    vert_colors_[vert] = Black;
    return tup_[vert];
  }

  int CountBridgesDfs(int vert, int edge_id) {
    vert_colors_[vert] = Grey;
    int kolvo_mostov = 0;
    for (auto& i : verticies_[vert]) {
      if (bridges_[i.second]) {
        ++kolvo_mostov;
        continue;
      }
      if ((i.first == vert) || (i.second == edge_id) ||
          (vert_colors_[i.first] != White)) {
        continue;
      }
      kolvo_mostov += CountBridgesDfs(i.first, i.second);
    }
    vert_colors_[vert] = Black;
    return kolvo_mostov;
  }

 public:
  Graph(int n, int m) : verticies_number_(n), m_(m) {
    vert_colors_.resize(n, White);
    tup_.resize(n, -1);
    tin_.resize(n, -1);
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    bridges_.resize(m_ + 1, false);
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);

  void Do() {
    int kolvo_listov = 0;
    for (int i = 0; i < verticies_number_; ++i) {
      if (vert_colors_[i] == White) {
        Dfs(i, -1);
      }
    }
    for (int i = 0; i < verticies_number_; ++i) {
      vert_colors_[i] = White;
    }

    for (int i = 0; i < verticies_number_; ++i) {
      if (vert_colors_[i] != White) {
        continue;
      }
      int ans = CountBridgesDfs(i, 0);
      kolvo_listov += ((ans == 1) ? 1 : 0);
    }
    std::cout << kolvo_listov / 2 + ((kolvo_listov % 2 == 0) ? 0 : 1) << "\n";
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
