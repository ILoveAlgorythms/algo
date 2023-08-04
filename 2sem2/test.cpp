#include<iostream>

class test { 
 private:
  int a;
  friend int f(test& t);
};

int main()  {
  std::pair<int, int> a;
  std::cin >> a;
  std::cout << a;
  return 0;
}
