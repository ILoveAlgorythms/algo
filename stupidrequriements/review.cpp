#include <iostream>
#include <unordered_map>
#include <vector>

template<class T>
class DSU {
 public:
  DSU(int n) {
    ancestors_.resize(n);
    for (int i = 0; i < n; ++i) {
      ancestors_[i] = i;
      hash_[i] = i;
    }
    depth_.resize(n, 0);
    friendship_.resize(n, 0);
  }
  DSU(const std::vector<T>& input) {
    ancestors_.resize(input.size());
    for (int i = 0; i < input.size(); ++i) {
      hash_[input[i]] = i;
      ancestors_[i] = i;
    }
    depth_.resize(input.size(), 0);
    friendship_.resize(input.size(), 0);
  }
  DSU() = default;
  ~DSU() = default;

  int FindSet(const T& elem) {
    return FastFindSet(hash_[elem]);
  }

  void Union(T first, T second, int w) {
    auto a = hash_[first];
    auto b = hash_[second];
    a = FastFindSet(a);
    b = FastFindSet(b);
    if (a == b) {
      friendship_[a] += w;
      return;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    friendship_[a] += friendship_[b] + w;
    ancestors_[b] = a;
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
  }
  int FindFriendshipstrongness(T x) {
    return friendship_[FindSet(x)];
  }
 private:
  int FastFindSet(int elem) {
     if (elem == ancestors_[elem]) {
      return elem;
    }
    ancestors_[elem] = FastFindSet(ancestors_[elem]);
    return ancestors_[elem];
  }
  std::unordered_map<T, int> hash_;
  std::vector<int> ancestors_;
  std::vector<int> depth_;
  std::vector<int> friendship_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int calls;
  std::cin >> n >> calls;
  DSU<int> dcma(n);
  int command;
  int x;
  int y;
  int w;
  for (int i = 0; i < calls; ++i) {
    std::cin >> command;
    switch (command) {
      case 1:
        std::cin >> x >> y >> w;
        dcma.Union(x - 1, y - 1, w);
        break;
      case 2:
        std::cin >> x;
        std::cout << dcma.FindFriendshipstrongness(x - 1) << "\n";
        break;
    }
  }
  return 0;
}
