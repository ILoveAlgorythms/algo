#include <deque>
#include <iostream>
#include <vector>
constexpr std::size_t operator "" _t ( unsigned long long n ) { return n; }

class Graph {
  enum Color { White, Grey, Black };
  int verticies_number_;
  int m_;
  int start_vert_ = 0;
  int start_offset_ = -1;
  std::vector<Color> vert_colors_;
  std::vector<int> offset_;
  std::vector<bool> minus_;
  std::vector<std::vector<std::pair<int, int>>> verticies_;

  void Dfs(int vert) {
    if (start_offset_ != -1) {
      return;
    }
    if (vert_colors_[vert] == Grey) {
      return;
    }

    vert_colors_[vert] = Grey;

    for (auto [i, j] : verticies_[vert]) {
      if (vert_colors_[i] == Black && minus_[i] == minus_[vert]) {
        start_offset_ = (offset_[i] + offset_[vert] - j) / 2;
        if (!minus_[i]) {
          start_offset_ = -start_offset_;
        }
        return;
      }
      if (i == vert || vert_colors_[i] == Black) {
        continue;
      }
      offset_[i] = j - offset_[vert];
      minus_[i] = !minus_[j];
      // std::cout << i << " " << offset_[i] << " " << offset_[vert] << " " << j << "\n";
      Dfs(i);
    }
    vert_colors_[vert] = Black;
  }  

 public:
  Graph(int n, int m) : verticies_number_(n), m_(m) {
    vert_colors_.resize(n, White);
    verticies_.resize(n, std::vector<std::pair<int, int>>());
    offset_.resize(n);
    minus_.resize(n);
  }
  friend std::istream& operator>>(std::istream& is, Graph& g);


  void Do(std::vector<int>& ans) {
    offset_[0] = 1;
    minus_[0] = false;
    Dfs(0);
    if (start_offset_ == -1) {
      int mn = 0;
      int minvert = 0;
      for (auto i =0_t; i < offset_.size(); ++i) {
        if (offset_[i] < mn) {
          mn = offset_[i];
          minvert = i;
        }
      }
    } 
    else if (verticies_number_ % 2 == 1) {
      int sum = 0;
      for (auto i : offset_) {
        sum += i;
      }
      start_offset_ = verticies_number_ * (verticies_number_ + 1) / 2 - sum;
    } else {

    }
    for (auto i = 0_t; i < ans.size(); ++i) {
      ans[i] = offset_[i];
    }
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
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
    g.verticies_[x].push_back({y, w});
    g.verticies_[y].push_back({x, w});
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  std::cin >> n >> m;
  Graph g(n, m);
  std::cin >> g;
  std::vector<int> ans(n);
  g.Do(ans);
  for (auto i : ans) {
    std::cout << i << " ";
  }
  return 0;
}
