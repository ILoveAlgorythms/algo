#include <iostream>
#include <set>
#include <vector>

class Graph {
  struct Cmp {
    bool operator()(const std::pair<int, int64_t>& a,
                    const std::pair<int, int64_t>& b) const {
      if (a.second == b.second) {
        return a.first < b.first;
      }
      return (a.second < b.second);
    }
  };

 protected:
  int n_;
  int m_;
  int k_;
  std::vector<std::vector<std::pair<int, int64_t>>> verticies_;
  std::vector<int64_t> wneh_been_hazard_;
  std::vector<int> viruses_;
  std::vector<int64_t> dist_viruse_;

 public:
  int64_t inf = 9'222'372'036'854'770'000;
  Graph(int n, int m, int k) : n_(n), m_(m), k_(k) {
    verticies_.resize(n, std::vector<std::pair<int, int64_t>>());
    wneh_been_hazard_.resize(n_, inf);
    viruses_.resize(k);
    dist_viruse_.resize(n_, inf);
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);

  void Hazard() {
    std::vector<int64_t> d(n_, inf);
    std::set<std::pair<int, int64_t>, Cmp> not_s;
    std::vector<bool> checked(n_, false);
    for (auto i : viruses_) {
      d[i] = 0;
      dist_viruse_[i] = 0;
      checked[i] = true;
      for (auto j : verticies_[i]) {
        d[j.first] = std::min(d[j.first], j.second);
      }
    }
    for (int i = 0; i < n_; ++i) {
      not_s.insert({i, d[i]});
    }
    while (!not_s.empty()) {
      auto i = not_s.begin()->first;
      not_s.erase(*not_s.begin());
      dist_viruse_[i] = std::min(d[i], dist_viruse_[i]);
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
  };

  int64_t FindWays(int start, int finish) {
    if (dist_viruse_[start] == 0) {
      return -1;
    }
    std::vector<int64_t> d(n_, inf);
    std::vector<int64_t> dist(n_, inf);
    std::set<std::pair<int, int64_t>, Cmp> not_s;
    std::vector<bool> checked(n_, false);
    d[start] = 0;
    dist[start] = 0;
    checked[start] = true;
    for (auto i : verticies_[start]) {
      d[i.first] = i.second;
    }
    for (int i = 0; i < n_; ++i) {
      not_s.insert({i, d[i]});
    }
    while (!not_s.empty()) {
      auto i = not_s.begin()->first;
      not_s.erase(*not_s.begin());
      dist[i] = d[i];
      checked[i] = true;
      for (auto j : verticies_[i]) {
        if (checked[j.first] || (d[i] + j.second >= d[j.first])) {
          continue;
        }
        if (d[i] + j.second >= dist_viruse_[j.first]) {
          dist[j.first] = -1;
          not_s.erase({j.first, d[j.first]});
          continue;
        }
        not_s.erase({j.first, d[j.first]});
        d[j.first] = d[i] + j.second;
        not_s.insert({j.first, d[i] + j.second});
      }
    }
    return (dist[finish] == inf) || (dist[finish] >= dist_viruse_[finish])
               ? -1
               : dist[finish];
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int x;
  int y;
  int64_t w;
  for (int i = 0; i < g.k_; ++i) {
    is >> x;
    g.viruses_[i] = x - 1;
  }
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y >> w;
    --x;
    --y;
    if (x == y) {
      continue;
    }
    g.verticies_[x].push_back(std::make_pair(y, w));
    g.verticies_[y].push_back(std::make_pair(x, w));
  }
  return is;
}

int main() {
  int n;
  int m;
  int k;
  int start;
  int finish;
  std::cin >> n >> m >> k;
  Graph g(n, m, k);
  std::cin >> g;
  std::cin >> start >> finish;
  --start;
  --finish;
  g.Hazard();
  std::cout << g.FindWays(start, finish);
  return 0;
}
