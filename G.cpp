#include <deque>
#include <iostream>
#include <vector>
#include <math>
//система непересекающихся множеств
class DSU {
 private:
  std::vector<int> ancestors_;
  std::vector<int> depth_;
 public:
  DSU(int n) {
    ancestors_.resize(n);
    for (int i = 0; i < n; ++i) {
      ancestors_[i] = i;
    }
    depth_.resize(n, 0);
  }
  friend std::ostream& operator<<(std::ostream& os, DSU& g);

  int FindSet(int elem) {
    if (elem == ancestors_[elem]) {
      return elem;
    }
    ancestors_[elem] =  FindSet(ancestors_[elem]); // ?
    return ancestors_[elem];
  }
  bool Same(int a, int b) {
    return FindSet(a) == FindSet(b);
  }
  void Unite(int a, int b) {
    a = FindSet(a);
    b = FindSet(b);
    if (a == b) {
      return;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    ancestors_[b] = a; // родитель меньшего -- большее
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
  }
};

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
  void PredPr() {
    dp_.resize(n_, std::vector<int> (std::log(n_) / std::log(2) + 1));
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
