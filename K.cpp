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

class Graph {
  enum Color { White, Grey, Black };
  int verticies_number_;
  int m_;
  std::vector<Color> vert_colors_;
  std::vector<std::vector<int>> verticies_;

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

 public:
  Graph(int n, int m) : verticies_number_(n), m_(m) {
    vert_colors_.resize(n, White);
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);


  void Do() {
    std::deque<int> s;
    for (int i = 0; i < verticies_number_; ++i) {
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
  if (!g.ExistsCycle()) {
    std::cout << "NO\n";
  }
  return 0;
}
