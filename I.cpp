#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

struct Graph {
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors;
  std::vector<std::vector<int>> verticies;
  std::vector<std::vector<int>> transposed_verticies;
  std::vector<int> components;
  std::deque<int> tout;
  int verticies_number;
  Graph(int n, int m) : verticies_number(n) {
    vert_colors.resize(n, White);
    components.resize(n);
    verticies = std::vector<std::vector<int>>(n, std::vector<int>());
    transposed_verticies = std::vector<std::vector<int>>(n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
      int x;
      int y;
      std::cin >> x >> y;
      --x;
      --y;
      verticies[x].push_back(y);
      transposed_verticies[y].push_back(x);
    }
  }

  void Dfs(int vert, int comp = 0, bool transpose = false) {
    if (transpose) {
      components[vert] = comp;
    }
    vert_colors[vert] = Grey;
    std::vector<int>& neigbors =
        (transpose ? transposed_verticies[vert] : verticies[vert]);
    for (auto i : neigbors) {
      if (i == vert || vert_colors[i] != White) {
        continue;
      }
      Dfs(i, comp, transpose);
    }
    vert_colors[vert] = Black;
    if (!transpose) {
      tout.push_front(vert);
    }
  }

  void Do() {
    for (int i = 0; i < verticies_number; ++i) {
      if (vert_colors[i] != White) {
        continue;
      }
      Dfs(i);
    }
    int comp = 0;
    std::fill(vert_colors.begin(), vert_colors.end(), White);
    for (auto i : tout) {
      if (vert_colors[i] != White) {
        continue;
      }
      ++comp;
      Dfs(i, comp, true);
    }
    std::cout << std::max(comp - 2, 0);
  }
};

int main() {//строим граф конденсации, ищем мосты
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 10;
  int m;
  int b;
  std::cin >> n >> m;
  Graph g(n, m);
  g.Do();
  return 0;
}
