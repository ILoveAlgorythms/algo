#include <iostream>
#include <set>
#include <vector>
class Graph {
  struct Cmp {
    bool operator()(const std::pair<int, int>& a,
                    const std::pair<int, int>& b) const {
      if (a.second == b.second) {
        return a.first < b.first;
      }
      return (a.second < b.second);
    }
  };
  struct Edge {
    int id;
    int from;
    int to;
    int capacity;
    int currentflow;
  };

 protected:
  int n_;
  int m_;
  std::vector<std::vector<Edge>> edges_;
  std::vector<int> cost_;
 public:
  int inf = 2'009'000'999;
  Graph(int n, int m) : n_(n), m_(m) {
    edges_.resize(n, std::vector<Edge>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  
};


class Net {
 public:
  Graph G;
  int start;
  int finish;

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
    g.verticies_[x].push_back(std::make_pair(y, w));
    g.verticies_[y].push_back(std::make_pair(x, w));
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
  for (int j = 0; j < g.n_; ++j) {
    os << g.dist_[j] << " ";
  }
  os << "\n";
  return os;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  int calls;
  std::cin >> calls;
  int start;
  for (int i = 0; i < calls; ++i) {
    std::cin >> n >> m;
    Graph g(n, m);
    std::cin >> g;
    std::cin >> start;
    // --start;
    g.FindWays(start);
    std::cout << g;
  }
  return 0;
}
