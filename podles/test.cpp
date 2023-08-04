#include<iostream>
#include<vector>
const int kBlocksize = 8;

template<typename T>
class Deque {
 public:
  using BlockVec = std::vector<std::vector<T>*>;
  Deque() {}
  Deque(int n) {}
  Deque(int n, const T& t) {}
  Deque(const Deque<T>& deq) {}
  int size() const {} // NOLINT
  T& operator[] (int n) {}
  T& at(int n) {} // NOLINT
  void push_back(const T& t) { //NOLINT
    auto lastblock = blocks_.back();
    if(lastblock->size() < kBlocksize) {
      lastblock->push_back(t);
      return;
    }
    blocks_.push_back(new std::vector<T>(kBlocksize));
    blocks_.back()->push_back(t);
  }
  void pop_back() { //NOLINT
    auto lastblock = blocks_.back();
    lastblock->pop_back();
    if (lastblock->size() == 0) {
      blocks_.pop_back();
    }
  }
  void pop_front(); //NOLINT
  // void push_front(const T& t) { //NOLINT
  //   auto firstblock = blocks_.front();
  //   if(firstblock->size() < kBlocksize) {
  //     lastblock->push_back(t);
  //     return;
  //   }
  //   blocks_.push_back(new std::vector<T>(kBlocksize));
  //   blocks_.back()->push_back(t);
  // }

//  private:
  BlockVec blocks_;
  size_t last_block_index_;
};

int main() {
  Deque<int> d;
  d.push_back(1);
  d.push_back(2);
  std::cout 
  return 0;
}