#include<iostream>
#include<vector>
#include<deque>
void print(std::deque<int>& s) {
  while(!s.empty()) {
    std::cout << s.front() + 1 << " ";
    s.pop_front();
  }
  std::cout << "\n";
}

struct Graph {
  enum color {white, grey, black};
  std::vector<color> vert_colors;
  std::vector<std::vector<int>> verticies;
  Graph(int n, int m) {
    vert_colors.resize(n);
    verticies = std::vector<std::vector<int>> (n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
      int x;
      int y;
      std::cin >> x >> y;
      --x;
      --y;
      verticies[x].push_back(y);
      verticies[y].push_back(x);
    }
  }


  bool dfs(int vert, int finish, std::deque<int>& s) {
    s.push_back(vert);//
    
    if (vert_colors[vert] != white) {
      s.pop_back();
      return false;
    }

    if (vert == finish) {
      return true;
    }

    vert_colors[vert] = grey;


    for (auto i: verticies[vert]) {
      if (dfs(i, finish, s)) {
        return true;
      }
    }
    vert_colors[vert] = black;

    s.pop_back();//

    return false;
  }

  void findPath(int start, int finish) {
    vert_colors.resize(vert_colors.size(), white);
    std::deque<int> s;
    if (dfs(start, finish, s)) {
      print(s);
      return;
    }
    std::cout << -1;
  }
};



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
  g.findPath(start, finish);
  return 0;
}
