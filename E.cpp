#include <deque>
#include <iostream>
#include <vector>

class Graph {
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors;
  std::vector<std::vector<int>> verticies;
  int verticies_number;

  bool Dfs(int vert, std::deque<int>& s) {
    if (vert_colors[vert] == Grey) {
      return true;
    }
    vert_colors[vert] = Grey;
    for (auto i : verticies[vert]) {
      if (i == vert || vert_colors[i] == Black) {
        continue;
      }
      if (Dfs(i, s)) {
        return true;
      }
    }
    vert_colors[vert] = Black;
    s.push_back(vert);
    return false;
  }

  void Print(std::deque<int>& s) {
    while (!s.empty()) {
      std::cout << s.back() + 1 << " ";
      s.pop_back();
    }
    std::cout << "\n";
  }

  public:
  Graph(int n, int m) : verticies_number(n) {
    vert_colors.resize(n, White);
    verticies = std::vector<std::vector<int>>(n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
      int x;
      int y;
      std::cin >> x >> y;
      --x;
      --y;
      verticies[x].push_back(y);
    }
  }

  bool Do() {
    std::deque<int> sorted_verticies;
    for (int i = 0; i < verticies_number; ++i) {
      if (vert_colors[i] != White) {
        continue;
      }
      if (Dfs(i, sorted_verticies)) {
        return true;
      }
    }
    Print(sorted_verticies);
    return false;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  if (g.Do()) {
    std::cout << "-1\n";
    return 0;
  }
  return 0;
}
