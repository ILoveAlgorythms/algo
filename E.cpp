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

  bool Same (int a, int b) {
    return FindSet(a) == FindSet(b);
  }
  int FindSet(int elem) {
    if (elem == ancestors_[elem]) {
      return elem;
    }
    ancestors_[elem] = FindSet(ancestors_[elem]);  // ?
    return ancestors_[elem];
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

struct Edge {
  static constexpr int kInf = 201;
  int id;
  int v1;
  int v2;
  int w;
  Edge() = default;
  Edge(const Edge& e) = default;
  void Make(int idd, int v11, int v22, int ww) {
    id = idd;
    v1 = v11;
    v2 = v22;
    w = ww;
  }
  bool operator<(const Edge& e) const { return w > e.w; }
};

class Graph {
 protected:
  int n_;
  int m_;
  std::vector<Edge> edges_;

 public:
  Graph(int n, int m) : n_(n), m_(m) { edges_.resize(m); }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);
  int FindStream(int a, int b) {
    int ans = Edge::kInf;
    DSU all_edges(n_);
    for (auto& i : edges_) {
      all_edges.Sex(i.v1, i.v2);
      ans = std::min(ans, i.w);
      if (all_edges.Same(a, b))
        return ans;
    }
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int x;
  int y;
  int w;
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y >> w;
    if (x == y) {
      continue;
    }
    g.edges_[i].Make(i, x - 1, y - 1, w);
  }
  std::sort(g.edges_.begin(), g.edges_.end());
  return is;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  Graph g(n, m);
  std::cin >> g;
  int a;
  int b;
  for (int i = 0; i < k; ++i) {
    std::cin >> a >> b;
    std::cout << g.FindStream(a - 1, b - 1) << "\n";
  }
  return 0;
}
