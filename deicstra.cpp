#include <iostream>
#include <set>
#include <vector>
//расстояния от одной до всех
#define inf 2'009'000'999

class Graph {
  struct Cmp {
    bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) const {
      if (a.second == b.second) { // set считает элементы равными, если !(a < b) && !(b < a)
        return a.first < b.first;
      }
      return (a.second < b.second);
    }
  };
 protected:
  int n_;
  int m_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<int> dist_;
 public:
  Graph(int n, int m) : n_(n), m_(m) {
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void FindWays(int start) {
    std::vector<int> d(n_, inf);
    std::set<std::pair<int, int>, Cmp> not_s; // first -- вершина, second -- d[first]
    dist_.resize(n_, inf);
    std::vector<bool> checked(n_, false); // попадала ли вершина в s
    d[start] = 0;
    dist_[start] = 0;
    checked[start] = true;
    for (auto i: verticies_[start]) {
      d[i.first] = i.second;
    }
    for (int i = 0; i < n_; ++i) {
      not_s.insert({i, d[i]});
    }
    while (!not_s.empty()) {
      auto i = not_s.begin()->first;
      not_s.erase(*not_s.begin());
      dist_[i] = d[i];
      checked[i] = true;
      for (auto j : verticies_[i]) {
        if (checked[j.first] || (d[i] + j.second >= d[j.first])) {
          continue;
        }
        not_s.erase({j.first, d[j.first]});
        d[j.first] = d[i] + j.second;
        not_s.insert({j.first, d[i] + j.second});
      }
    }
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int x;
  int y;
  int w;
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y >> w;
    // --x;
    // --y;
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
  int N;
  std::cin >> N;
  int start;
  for (int i = 0; i < N; ++i) {
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
