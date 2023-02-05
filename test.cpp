#include<iostream>
#include<vector>
#include<deque>



int main() {
  std::vector<std::vector<int>> v;
  v.push_back(std::vector<int> ());
  v[0].push_back(1);
  std::cout << v[0][0];
  return 0;
}
