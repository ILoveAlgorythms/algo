#include <iostream>
#include <set>
#include <vector>
//система непересекающихся множеств
class DSU {
 private:
  std::vector<int> ancestors_;
  std::vector<int> depth_;
 public:
  DSU(int n) {
    ancestors_.resize(n);
    for (int i = 0; i < n; ++i) {
      ancestors_[i] = i;
    }
    depth_.resize(n, 0);
  }
  friend std::ostream& operator<<(std::ostream& os, DSU& g);

  int FindSet(int elem) {
    if (elem == ancestors_[elem]) {
      return elem;
    }
    ancestors_[elem] =  FindSet(ancestors_[elem]); // ?
    return ancestors_[elem];
  }
  bool Same(int a, int b) {
    return FindSet(a) == FindSet(b);
  }
  void Unite(int a, int b) {
    a = FindSet(a);
    b = FindSet(b);
    if (a == b) {
      return;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    ancestors_[b] = a; // родитель меньшего -- большее
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
  }
};

std::ostream& operator<<(std::ostream& os, DSU& g) {
  for (int j = 0; j < g.depth_.size(); ++j) {
    os << "\n---   " << j << ":\n ";
    for (int i = 0; i < g.depth_.size(); ++i) {
      if (g.ancestors_[i] == j) {
        os << i << " ";
      }
    }
  }
  os << "\n";
  return os;
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  return 0;
}
