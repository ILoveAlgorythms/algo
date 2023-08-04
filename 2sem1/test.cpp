#include<iostream>
#include<vector>

int main() {
  std::vector<std::pair<int, int>> edges;
  edges.push_back({1, 2});
  for (const auto& [a, sec] : edges) {
    std::cout << a << "\n";
  }
  return 0;
}