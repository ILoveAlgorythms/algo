#include <deque>
#include <iostream>
#include <vector>

class Graph {
 protected:
  int n_;
  int m_;
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors_;
  std::vector<int> dist_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;
  std::vector<std::deque<int>> q_;
  int max_w_ = 1;

  void OneKBfs(int v) {
    q_[0].push_back(v);
    int tec = 0;
    int vert_in_q = 1;
    while (vert_in_q != 0) {
      for (; q_[tec % (max_w_ + 1)].empty(); ++tec) {
      }
      auto& tec_q = q_[tec % (max_w_ + 1)];

      auto j = tec_q.front();
      tec_q.pop_front();
      --vert_in_q;
      if (vert_colors_[j] == Black) {
        continue;
      }
      vert_colors_[j] = Black;

      for (auto i : verticies_[j]) {
        if (vert_colors_[i.first] != White) {
          continue;
        }
        if ((dist_[j] + i.second) > dist_[i.first]) {
          continue;
        }
        dist_[i.first] = dist_[j] + i.second;
        ++vert_in_q;
        q_[dist_[i.first] % (max_w_ + 1)].push_back(i.first);
      }
    }
  }

 public:
  Graph(int n, int m) : n_(n), m_(m) {
    vert_colors_.resize(n, White);
    dist_.resize(n, 1100000);
    verticies_.resize(n, std::vector<std::pair<int, int>>());
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);

  int FindWay(int start, int finish) {
    q_.resize(max_w_ + 1, std::deque<int>{});
    dist_[start] = 0;
    int dist0 = dist_[finish];
    OneKBfs(start);
    return ((dist0 == dist_[finish]) ? (-1) : dist_[finish]);
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int max_w = 0;
  int x;
  int y;
  int w;
  for (int i = 0; i < g.m_; ++i) {
    is >> x >> y >> w;
    --x;
    --y;
    if (x == y) {
      continue;
    }
    g.verticies_[x].push_back(std::make_pair(y, w));
    max_w = std::max(max_w, w);
  }
  g.max_w_ = max_w;
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  int start;
  int finish;
  std::cin >> n >> m >> start >> finish;
  --start;
  --finish;
  Graph g(n, m);
  std::cin >> g;
  if (start == finish) {
    std::cout << "0\n" << start;
    return 0;
  }
  std::cout << g.FindWay(start, finish);
  return 0;
}
