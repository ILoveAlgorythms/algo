#include<vector>
#include<deque>
#include<iostream>

class d {
  public:
  static const int G = 2;
};



int main() {
  std::cout << d::G;
  std::vector<int> a;
  std::cout << a.size();
  return 0;
}