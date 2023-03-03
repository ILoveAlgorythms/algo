#include<iostream>

int main() {
  std::pair<int, int> a[3] = {{1,11}, {2, 22},{3,33}};
  for (auto [vertex, edge] : a) {
    for (int i = 0; i < 10; ++i) {
      if (i == 4) {
        break;
      }
      std::cout << "3";
    }
    std::cout <<"\n";
  }
  return 0;
}