#include <iostream> 
class A {
  public:
  virtual int fo() {return 1; };
};
class B : public A{
  public:
  // int fo() override = delete;
};
int main() {
  A a;
  std::cout << a.fo();
  return 0;
}