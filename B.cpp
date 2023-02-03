#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> v;
  std::string s;
  while (std::cin >> s)  {
    v.push_back(s);
  }
  int words = 1;
  std::cout << v[0];
  for (size_t i = 1; i < v.size() - 1; ++i) {
    if (v[i] == "and" || v[i] == "or") {

      continue;
    }
    ++words;
    if (v[])
  }
  
  return 0;
}
