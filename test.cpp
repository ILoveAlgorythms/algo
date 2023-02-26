#include<vector>
#include<deque>
#include<iostream>

int main() {
  std::vector<std::vector<std::vector<int>>> dp;
  dp.resize(1, std::vector<std::vector<int>>(2, std::vector<int>(3)));
  dp[0][1][2];
  return 0;
}