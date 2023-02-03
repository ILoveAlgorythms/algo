#include <iostream>
#include<cmath>
#include<string>

int log10(int x) {
  int ans = 0;
  for (; x >= 1; x = x / 10) { ++ ans; }
  return ans;
}

int kolvo_cifr(int x) {
  int log = log10(x);
  int ans = 0;
  int j = 9;
  for (int i = 1; i < log; ++i) {
    ans += j * i;
    j = j * 10;
  }
  ans += log * (x - pow(10, log - 1) + 1);
  return ans;
}

int find(std::string& s, int i, int m, int finding) {
  for (int  j = 0; j < m + 1; ++j) {
    if (s[j + i + 1] - '0' == finding)
      return j + i + 1; 
  }
  return -1;
}


int main() {// DODELAT'
  int n, m;
  std::cin >> m >> n; 
  int kol = kolvo_cifr(n);
  std::string s;
  //std::cout << kol << "\n";
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 0; j < std::to_string(i).size(); ++j) {
      s.push_back(std::to_string(i)[j]);
    }
  }
  int it = -1;


  while(it < kol - 1 - m) {
    //std::cout << " it: " << it << " m:" << m  << "\n";
    for (int i = 0; i <= 9; ++i) {
      int g = find(s, it, m, i);
      if (g != -1) {
        std::cout << i;
        m -= g - it - 1;
        it = g;
        break;
      }
    }
  }
  
  return 0;
}
