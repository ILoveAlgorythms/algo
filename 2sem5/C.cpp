#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
const size_t kModul = 2966104235357;
const size_t kDeg = 30;

using vec = std::vector<size_t>;
using map = std::unordered_map<size_t, int>;

vec degs;

void CountDegs(vec& degs) {
  degs[0] = 1;
  for (size_t i = 1; i < degs.size(); ++i) {
    degs[i] = (degs[i - 1] * kDeg) % kModul;
  }
}

size_t Hash(const std::string& str) {
  // std::cout << "hash from: " << str <<"\n"; 
  size_t ans = 0;
  size_t current_deg = 1;
  for (size_t i = 0; i < str.size(); ++i) {
    ans = (((str[i] - 'a' + 1) * current_deg) % kModul + ans) % kModul;
    current_deg = (current_deg * kDeg) % kModul;
  }
  return ans;
}

size_t Hash(char c, size_t mnozhitel) {
  return ((c - 'a' + 1) * mnozhitel) % kModul;
}

vec PrefixHash(std::string str, vec& degs) {
  vec ans(str.size());
  ans[0] = Hash(str[0], 1);
  for (size_t i = size_t(1); i < str.size(); ++i) {
    ans[i] = (Hash(str[i], degs[i]) + ans[i - 1]) % kModul;
  }
  return ans;
}

size_t SubHash(std::string& hash, size_t l, size_t size) {
  size_t hash_l = (l == 0 ? 0 : hash[l - 1]);
  return (hash[l + size] - hash_l * degs[size]) % kModul;
}

int main() {
  std::string pat;
  std::string text;
  std::cin >> pat >> text;
  if (pat.size() > text.size()) {
    std::cout << 0;
    return 0;
  }
  degs.resize(text.size());
  CountDegs(degs);

  map hash;
  size_t current_pat_hash = Hash(pat);
  for (size_t i = 0; i < pat.size(); ++i) {
    hash.insert({current_pat_hash, i});
    current_pat_hash += kModul - Hash(pat[pat.size() - 1 - i], degs[pat.size() - 1]);
    current_pat_hash *= degs[1];
    current_pat_hash += Hash(pat[pat.size() - 1 - i], degs[0]);
    current_pat_hash = current_pat_hash % kModul;
  }
  int ans = 0;
  size_t currenthash = Hash(text.substr(text.size() - pat.size(), pat.size()));
  for (size_t i = text.size() - 1; i >= pat.size(); --i) {
    if (hash.count(currenthash) > 0) {
      ++ans;
    }
    currenthash += kModul - Hash(text[i], degs[pat.size() - 1]);
    currenthash *= degs[1];
    currenthash += Hash(text[i - pat.size()], degs[0]);
    currenthash = currenthash % kModul;
    current_pat_hash = current_pat_hash % kModul;
  }
  if (hash.count(currenthash) > 0) {
    ++ans;
  }
  std::cout << ans;
  return 0;
}
