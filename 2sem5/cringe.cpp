#include <iostream>
#include <vector>
#include <string>

int main() {
  size_t left_z_block = 0;
  size_t right_z_block = 0;
  std::string s = "AAA_AAA--AAA_AAA_AAA";
  std::vector<size_t> z(s.length(), 0);
  for (size_t i = 1; i < s.length(); ++i) {
    if (i < right_z_block) {
      z[i] = std::min(right_z_block - i + 1, z[i - left_z_block]);
    }
    while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > right_z_block) {
      left_z_block = i;
      right_z_block = i + z[i] - 1;
    }
  }
  std::cout << s << "\n";
  for (auto i : z) {
    std::cout << i;
  }
}