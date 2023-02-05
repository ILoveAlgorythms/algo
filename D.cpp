#include <iostream>
#include <vector>
struct Graph {
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors;
  std::vector<std::vector<int>> verticies;
  int verticies_number;
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
      verticies[y].push_back(x);
    }
  }

  void Dfs(int vert, std::vector<int>& v) {
    vert_colors[vert] = Grey;
    v.push_back(vert);
    for (auto i : verticies[vert]) {
      if (vert_colors[i] == White) {
        Dfs(i, v);
      }
    }
    vert_colors[vert] = Black;
  }

  void Do() {
    std::vector<std::vector<int>> v;
    for (int i = 0; i < verticies_number; ++i) {
      if (vert_colors[i] != White) {
        continue;
      }
      v.push_back(std::vector<int>());
      Dfs(i, v.back());
    }

    std::cout << v.size() << "\n";
    for (auto i : v) {
      std::cout << i.size() << "\n";
      for (auto j : i) {
        std::cout << j + 1 << " ";
      }
      std::cout << "\n";
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  g.Do();
  return 0;
}
