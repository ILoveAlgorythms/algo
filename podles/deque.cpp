#include<iostream>
#include<vector>
const int BLOCKSIZE = 8;

template<typename T>
class Deque {
 public:
  Deque() {}
  Deque(int n) {}
  Deque(int n, const T& t) {}
  int size() {} // NOLINT
  T& operator[] (int n) {}
  T& at(int n) {} // NOLINT

 private:
  struct Block {
    std::vector<T> things;
    
  };
  
  std::vector<Block> blocks_;
};

int main() {
  std::cout << "ad";
  return 0;
}