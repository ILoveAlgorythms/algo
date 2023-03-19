#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

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
  std::vector<Edge> edges_;
  

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
    std::set<int> s;
    s.insert(0);
    std::vector<Edge> mst;
    std::set<Edge> edges;
    for (int i = 1; i < n_; ++i) {
      for (int j = 0; )
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
    edges_.push_back(Edge(y, x, w));
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
