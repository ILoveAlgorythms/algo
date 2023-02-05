#include<iostream>
#include<vector>
#include<stack>

void foo(std::deque<int> &s) {
  for (auto i: s) {
    std::cout << i << " ";
  }
}


int main() {
  std::deque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  foo(d);
  return 0;
}
