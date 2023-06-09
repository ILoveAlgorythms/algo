#include <deque>
#include <iostream>
#include <vector>

struct Graph {
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors;
  std::vector<std::vector<int>> verticies;
  int verticies_number;
  bool petli = false;
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

  static void Print(std::deque<int>& s) {
    while (!s.empty()) {
      std::cout << s.back() + 1 << " ";
      s.pop_back();
    }
    std::cout << "\n";
  }

  Graph(int n, int m) : verticies_number(n) {
    vert_colors.resize(n, White);
    verticies = std::vector<std::vector<int>>(n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
      int x;
      int y;
      std::cin >> x >> y;
      --x;
      --y;
      petli = petli || (x == y);
      verticies[x].push_back(y);
    }
  }

  bool Do() {
    if (petli) {
      return true;
    }
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
  }
  return 0;
}
