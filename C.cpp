#include <deque>
#include <iostream>
#include <vector>
void Print(std::deque<int>& s) {
  while (s.front() != s.back()) {
    s.pop_front();
  }
  s.pop_front();
  while (!s.empty()) {
    std::cout << s.front() + 1 << " ";
    s.pop_front();
  }
  std::cout << "\n";
}

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
    }
  }

  bool Dfs(int vert, std::deque<int>& s) {
    s.push_back(vert);

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

    s.pop_back();

    return false;
  }

  bool ExistsCycle() {
    std::deque<int> s;
    for (int i = 0; i < verticies_number; ++i) {
      if (vert_colors[i] != White) {
        continue;
      }
      if (Dfs(i, s)) {
        std::cout << "YES\n";
        Print(s);
        return true;
      }
    }
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
  if (!g.ExistsCycle()) {
    std::cout << "NO\n";
  }
  return 0;
}
