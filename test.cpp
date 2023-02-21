#include<vector>
#include<deque>
#include<iostream>

int main() {
  std::pair<int, int> a = std::make_pair(1, 2);
  auto& i = a;
  i.first = 4;
  std::cout << (false ? 3 : 4);
  return 0;
}