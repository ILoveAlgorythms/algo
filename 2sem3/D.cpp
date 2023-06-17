#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
// MST
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
  ~DSU() = default;
  DSU() = default;
  friend std::ostream& operator<<(std::ostream& os, DSU& g);

  int FindSet(int elem) {
    if (elem == ancestors_[elem]) {
      return elem;
    }
    // ancestors_[elem] = FindSet(ancestors_[elem]);  // ?
    // return ancestors_[elem];
    return FindSet(ancestors_[elem]);
  }
  bool Sex(int a, int b) {  // возращает true если уже
    a = FindSet(a);
    b = FindSet(b);
    if (a == b) {
      return true;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    ancestors_[b] = a;  // родитель меньшего -- большее
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
    return false;
  }
};

struct EType {
  int id;
  int v1;
  int v2;
  int64_t w;
  EType() = default;
  EType(const EType& e) = default;
  void Make(int idd, int v11, int v22, int ww) {
    id = idd;
    v1 = v11;
    v2 = v22;
    w = ww;
  }
  bool operator<(const EType& e) const { return w < e.w; }
};

std::ostream& operator<<(std::ostream& os, const EType& e) {
  os << e.id << ": " << e.v1 << ", " << e.v2 << "  w: " << e.w << "\n";
  return os;
}

class Graph {
 protected:
  int n_;
  int m_;
  std::vector<EType> edges_;

 public:
  Graph(int n, int m) : n_(n), m_(m) { edges_.resize(m); }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);
  int64_t FindMstWeight() {
    int64_t ans = 0;
    DSU all_edges(n_);
    std::sort(edges_.begin(), edges_.end());
    for (int i = 0; i < m_; ++i) {
      auto& edg = edges_[i];
      // std::cout << edg;
      if (edg.v1 == edg.v2 || all_edges.Sex(edg.v1, edg.v2)) {
        continue;
      }
      ans += edg.w;
      // std::cout << "  approve\n";
    }
    return ans;
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int64_t w;
  for (int i = 0; i < g.n_ - 1; ++i) { // тут можно оптимизировать
    for (int j = 0; j < g.n_ - 1; ++j) {
      is >> w;
      g.edges_[i * (g.n_ - 1) + j].Make(i * (g.n_ - 1) + j, i, j, w);
      // std::cout << g.edges_[i];
    }
  }
  for (int i = g.m_ - (g.n_ - 1); i < g.m_; ++i) {
    is >> w;
    g.edges_[i].Make(i, g.n_ - 1, i - (g.m_ - (g.n_ - 1)), w);
    // std::cout << g.edges_[i];
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  Graph g(n + 1, n * n + n);
  std::cin >> g;
  std::cout << g.FindMstWeight();
  return 0;
}
