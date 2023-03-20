#include <iostream>
#include <set>
#include <vector>

class DSU {
 private:
  std::vector<int> ancestors_;
  std::vector<int> depth_;
  std::vector<int> friendshipstrongness_;

 public:
  DSU(int n) {
    ancestors_.resize(n);
    for (int i = 0; i < n; ++i) {
      ancestors_[i] = i;
    }
    depth_.resize(n, 0);
    friendshipstrongness_.resize(n, 0);
  }
  ~DSU() = default;
  DSU() = default;
  friend std::ostream& operator<<(std::ostream& os, DSU& g);

  int FindSet(int elem) {
    if (elem == ancestors_[elem]) {
      return elem;
    }
    ancestors_[elem] = FindSet(ancestors_[elem]);  // ?
    return ancestors_[elem];
  }
  void Sex(int a, int b, int w) {  // возращает предка
    a = FindSet(a);
    b = FindSet(b);
    if (a == b) {
      friendshipstrongness_[a] += w;
      return;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    friendshipstrongness_[a] += friendshipstrongness_[b] + w;
    ancestors_[b] = a;  // родитель меньшего -- большее
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
  }
  int FindFriendshipstrongness(int x) {
    return friendshipstrongness_[FindSet(x)];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int calls;
  std::cin >> n >> calls;
  DSU dcma(n);
  int command;
  int x;
  int y;
  int w;
  for (int i = 0; i < calls; ++i) {
    std::cin >> command;
    switch (command) {
      case 1:
        std::cin >> x >> y >> w;
        dcma.Sex(x - 1, y - 1, w);
        break;
      case 2:
        std::cin >> x;
        std::cout << dcma.FindFriendshipstrongness(x - 1) << "\n";
        break;
    }
  }
  return 0;
}
