#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
 
int main() {
  std::unordered_map<int, std::vector<int>> s;
  s[1].push_back(5);
  std::cout << s[1][0];
}