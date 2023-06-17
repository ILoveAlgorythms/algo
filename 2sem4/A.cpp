#include <iostream>
#include <set>
#include <vector>
enum Color {White, Grey, Black};
const int kInf = 2'009'000'999;

struct EType {
  static int id_counter;
  int id;
  int from;
  int to;
  int residualcapacity;
  int flow = 0; // in main net
  int maxcapacity = -1;
  EType* brother = nullptr;
  EType() {}
  EType(const EType&) = default;
  EType(int from, int to, int capacity) : from(from), to(to), residualcapacity(capacity) {
    id = id_counter;
    ++id_counter;
    maxcapacity = capacity;
  }
  EType Residual() {
    EType ans(to, from, 0);
    brother = &ans;
    ans.brother = this;
    return ans;
  }
};

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
 public: 
 protected:
  int n_;
  int m_;
  std::vector<std::vector<EType>> edges_;
 public:
  Graph(int n, int m) : n_(n), m_(m) {
    edges_.resize(n, std::vector<EType>());
  }
  int N() {
    return n_;
  }

  void InsertEdge(int from, int to, int capacity) {
    edges_[from].push_back(EType(from, to, capacity));
    edges_[to].push_back(edges_[from].back().Residual());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);
  friend std::ostream& operator<<(std::ostream& os, Graph& g);
  friend class Net;

  void Dfs(int vert, int goal, std::vector<Color>& vert_colors, std::vector<EType>& trace) {
    vert_colors[vert] = Grey;
    for (auto i : edges_[vert]) {
      if (vert_colors[i.to] != White || i.residualcapacity == i.flow) {
        continue;
      }
      if (i.to == goal) {
        return;
      }
      if (vert_colors[i.to] == White) {
        trace.push_back(i);
        Dfs(i.to, goal, vert_colors, trace);
        trace.pop_back();
      }
    }
    vert_colors[vert] = Black;
  }
};


class Net {
  Graph graph_;
  Graph residualgraph_;
 public:
  int start;
  int finish;
  Net(Graph g, int start, int finish) : graph_(g), residualgraph_(g), start(start), finish(finish) {}
  Net(const Net& n) = delete;

  std::vector<EType> FindWay() {
    std::vector<EType> ans;
    std::vector<Color> colors(graph_.N(), White);
    graph_.Dfs(start, finish, colors, ans);
    return ans;
  }

  void Update(std::vector<EType>& trace, int addflow) {
    for (auto& i : trace) {
      i.flow += addflow;
      i.residualcapacity -= addflow;
      i.brother->residualcapacity += addflow;
    }
  }

  int da() {
    auto newtrace = FindWay();
    while (!newtrace.empty()) {
      int newflow = kInf;
      for (auto i : newtrace) {
        newflow = std::max(newflow, i.residualcapacity - i.flow);
      }
      Update(newtrace, newflow);
    }
    int ans = 0;
    for (auto i : graph_.edges_[start]) {
      ans += i.flow;
      ans -= i.brother->flow;
    }
    return ans;
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  std::vector<std::vector<bool>> connected;
  connected.resize(g.n_, std::vector<bool>(g.n_, false));
  int x;
  int y;
  int w;

  int iters = g.m_;
  for (int i = 0; i < iters; ++i) {
    is >> x >> y >> w;
    --x;
    --y;
    if (x == y) {
      continue;
    } if (connected[y][x]) {
      ++(g.m_);
      ++(g.n_);
      g.edges_.push_back(std::vector<EType>());
      g.InsertEdge(g.m_ - 1, y, w);
      g.InsertEdge(x, g.m_ - 1, w);
      continue;
    }
    g.InsertEdge(x, g.m_ - 1, w);
    connected[x][y] = true;
  }
  return is;
}

int EType::id_counter = 0;

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  std::cout << "cmon lets go" << "\n";

  Net net(g, 0, m - 1);
  std::cout << net.da();
  return 0;
}
