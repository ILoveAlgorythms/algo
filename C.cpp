#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <deque>

struct Edge {
  int v1, v2;
  int w = 0;
  Edge(int v1, int v2, int w) : v1(v1), v2(v2), w(w) {};
};


class Graph {
  struct Cmp {
    bool operator()(const Edge& a,
                    const Edge& b) const {
      if (a.w == b.w) {
        if (a.v1 == b.v1) {
          return a.v2 < b.v2;
        }
        return a.v1 < b.v1;
      }
      return (a.w < b.w);
    }
  };

 protected:
  int n_;
  int m_;
  std::vector<std::vector<Edge>> verticies_;
  std::vector<int> dist_;

 public:
  const int kInf = 2'009'000'999; 
  Graph(int n, int m) : n_(n), m_(m) {  
    verticies_.resize(n, std::vector<Edge>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindMst() {
    for (int i = 0; i < n_; ++i) {
      std::sort(verticies_[i].begin(), verticies_[i].end(), Cmp());
    }
    std::vector<Edge> mst;
    std::deque<int> s;
    s.push_back(0);
    std::set<Edge, Cmp> edges;
    std::vector<bool> used(n_, false);
    used[0] = true;
    for (int i = 1; i < n_; ++i) {
      auto vert = s.front();
      s.push_front(vert);
      used[vert] = true;
      for (auto j : verticies_[vert]) {
        if (!used[j.v2]) 
        edges.insert(j);
      }

      mst.push_back(*edges.begin());
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
    g.verticies_[x].push_back(Edge(x, y, w));
    g.verticies_[y].push_back(Edge(y, x, w));
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
  os << "\n";
  return os;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  g.FindMst();
  return 0;
}
