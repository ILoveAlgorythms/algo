#include <iostream>
#include <string>
#include <vector>
#include <deque>

struct Oper {
  enum Type {KAsk, KCut};
  Type type;
  int a;
  int b;
  void Make(Type t, int aa, int bb) {
    type = t;
    a = aa;
    b = bb;
  }
  Oper() = default;
};


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
  void Sex(int a, int b) {  // возращает предка
    a = FindSet(a);
    b = FindSet(b);
    if (a == b) {
      return;
    }
    if (depth_[a] < depth_[b]) {
      std::swap(a, b);
    }
    ancestors_[b] = a;  // родитель меньшего -- большее
    if (depth_[a] == depth_[b]) {
      ++depth_[a];
    }
  }
  bool Same(int a, int b) {
    return FindSet(a) == FindSet(b);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int m;
  int calls;
  std::cin >> n >> m >> calls;
  DSU dcma(n);
  std::vector<Oper> ops(calls);
  std::deque<std::string> ans;
  int u;
  int v;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
  }
  std::string s;
  for (int i = 0; i < calls; ++i) {
    std::cin >> s >> u >> v;
    switch (s[0] - 'a') {
    case 2: // cut
      ops[i].Make(Oper::KCut, u - 1, v - 1);
      break;
    case 0:
      ops[i].Make(Oper::KAsk, u - 1, v - 1);
      break;
    }
  }
  for (int j = calls - 1; j >= 0; --j) {
    auto& i = ops[j];
    switch (i.type) {
      case Oper::KCut:
        dcma.Sex(i.a, i.b);
        break;
      case Oper::KAsk:
        if (dcma.Same(i.a, i.b)) {
          ans.push_front("YES\n");
        } else {
          ans.push_front("NO\n");
        }
        break;
    }
  }
  for (auto i : ans) {
    std::cout << i;
  }
  return 0;
}
