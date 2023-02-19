#include <deque>
#include <iostream>
#include <vector>

class Graph {
 protected:
  int verticies_number_;
  int m_;
  enum Color { White, Grey, Black };
  std::vector<Color> vert_colors_;
  std::vector<int> dist_;
  std::vector<std::vector<int>> verticies_;
  std::deque<int> q_;

  void Print(int v) {
    int tec = dist_[v];
    std::cout << tec << "\n";
    std::deque<int> trace;
    trace.push_front(v);
    while (tec > 0) {
      for (auto i : verticies_[v]) {
        if (dist_[i] == tec - 1) {
          trace.push_front(i);
          v = i;
          --tec;
          break;
        }
      }
    }
    for (auto i : trace) {
      std::cout << i + 1 << " ";
    }
  }

  void Bfs(int& v) {
    q_.push_back(v);
    while (!q_.empty()) {
      auto j = q_.front();
      q_.pop_front();
      vert_colors_[j] = Black;
      for (auto i : verticies_[j]) {
        if (vert_colors_[i] != White) {
          continue;
        }
        dist_[i] = std::min(dist_[j] + 1, dist_[i]);
        q_.push_back(i);
      }
    }
  }

 public:
  Graph(int n, int m) : verticies_number_(n), m_(m) {
    vert_colors_.resize(n, White);
    dist_.resize(n, 1100000);
    verticies_.resize(n, std::vector<int>(0));
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);

  bool NoWay(int start, int finish) {
    dist_[start] = 0;
    int dist0 = dist_[finish];
    Bfs(start);
    if (dist_[finish] == dist0) {
      return true;
    }
    Print(finish);
    return false;
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  for (int i = 0; i < g.m_; ++i) {
    int x;
    int y;
    is >> x >> y;
    --x;
    --y;
    g.verticies_[x].push_back(y);
    g.verticies_[y].push_back(x);
  }
  return is;
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  int start;
  int finish;
  std::cin >> start >> finish;
  --start;
  --finish;
  Graph g(n, m);
  std::cin >> g;
  if (start == finish) {
    std::cout << "0\n" << start;
    return 0;
  }
  if (g.NoWay(start, finish)) {
    std::cout << -1;
  }
  return 0;
}
