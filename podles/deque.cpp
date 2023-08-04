#include<iostream>
#include<vector>
const int kBlocksize = 8;

template<typename T>
class Deque {
 public:
  using BlockVec = std::vector<std::vector<T>*>;
  class iterator { //NOLINT
   public:
    iterator(size_t first_block, size_t index, size_t first_block_, size_t last_block, BlockVec& blocks_) : block_ind_(first_block), i_(index),
    first_block_(first_block_), last_block_index_(last_block_index_), blocks_(blocks_) {}
    
    iterator operator++() {
      if (i_ < kBlocksize - 1) {
        ++i_;
        return *this;
      }
      if (block_ind_ < last_block_index_) {
        block_ind_ = 0;
        ++i_;
        return *this;
      }
      return *this;
    }
    iterator operator--() {
      if (i_ > 0) {
        --i_;
        return *this;
      }
      if (block_ind_ < last_block_index_) {
        block_ind_ = 0;
        ++i_;
        return *this;
      }
      return *this;

    }
    iterator operator*() {
      return (*blocks_[block_ind_])[i_];
    }

   private:
    size_t block_ind_;
    size_t i_;
    BlockVec blocks_;
    size_t last_block_index_;
    size_t first_block_;
  };

  Deque() {}
  Deque(int n) {}
  Deque(int n, const T& t) {}
  Deque(const Deque<T>& deq) {}
  int size() const {} // NOLINT
  T& operator[] (int n) {}
  T& at(int n) {} // NOLINT
  iterator begin() {} // NOLINT
  iterator end() {} // NOLINT
  void push_back(const T& t) { //NOLINT
    auto lastblock = blocks_[last_block_index_];
    if(lastblock->size() < kBlocksize) {
      lastblock->push_back(t);
      return;
    }
    blocks_.push_back(new std::vector<T>(kBlocksize));
    blocks_.back()->push_back(t);
  }
  void pop_back() { //NOLINT
    auto lastblock = blocks_[last_block_index_];
    lastblock->pop_back();
    // if (lastblock->size() == 0) {
    //   blocks_.pop_back();
    // }
  }
  void pop_front() { //NOLINT
    auto firstblock = blocks_[first_block_index_];
    firstblock->pop_front();
  }
  void push_front(const T& t) { //NOLINT
    auto firstblock = blocks_[first_block_index_];
    if(firstblock->size() < kBlocksize) {
      firstblock->push_back(t);
      return;
    }
    blocks_.push_back(new std::vector<T>(kBlocksize));
    blocks_.back()->push_back(t);
  }

  T& back() { //NOLINT
    return blocks_[last_block_index_].back();
  }
  const T& back() const { //NOLINT
    return blocks_[last_block_index_].back();
  }
  T& front() { //NOLINT
    return blocks_[first_block_index_].front();
  }
  const T& front() const { //NOLINT
    return blocks_[first_block_index_].front();
  }


 private:
  BlockVec blocks_;
  size_t last_block_index_;
  size_t first_block_index_;
};

int main() {
  return 0;
}