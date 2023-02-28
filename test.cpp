#include<vector>
#include<set>
#include<iostream>

struct Cmp {
  bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) const {
    return (a.second < b.second);
  }
};

int main() {
  std::set<std::pair<int, int>, Cmp> s; // first -- вершина, second -- *d[first]
  s.insert({3, 2});
  s.insert({1, 42});
  s.insert({2, 41});
  std::cout << (*s.begin()).second << " ";
  s.erase(*s.begin());
  std::cout << (*s.begin()).second;
  return 0;
}