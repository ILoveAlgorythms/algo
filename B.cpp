#include <deque>
#include <iostream>
#include <vector>
#define inf 123456789
struct Edge {
  int to;
  int mass;
};

std::istream& operator >> (std::istream& is, Edge& e) {
  int to;
  int mass;
  is >> to >> mass;
  --to;
  e.to = to;
  e.mass = mass;
  return is;
}

std::ostream& operator << (std::ostream& os, Edge& e) {
  return (os << " " << e.to + 1 << " " << e.mass << "\n");
}


class Graph {
  std::vector<bool> was_used;
  std::vector<std::vector<Edge>> verticies;
  int verticies_number;
  public:
  Graph(int n, int m) : verticies_number(n) {
    was_used.resize(n, false);
    verticies = std::vector<std::vector<Edge>>(n, std::vector<Edge>());
    for (int i = 0; i < m; ++i) {
      int from;
      Edge e;
      std::cin >> from >> e;
      --from;
      verticies[from].push_back(e);
    }
  }

  void Bfs(int vert, std::deque<int>& deq, std::vector<int> length) {
    was_used[vert] = true;
    for (auto i : verticies[vert]) {
      length[i.to] = std::min(length[i.to], length[vert] + i.mass);
      if (was_used[i.to])
        continue;
      deq.push_back(i.to);
    }
    Bfs(deq.front(), deq, length);
    deq.pop_front();
  }

  bool FindLength(int start, int finish) {
    std::vector<int> length(verticies_number, inf);
    std::deque<int> deq;

  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  int start;
  int finish;
  --start;
  --finish;
  std::cout << g.FindLength(start, finish);
  return 0;
}
