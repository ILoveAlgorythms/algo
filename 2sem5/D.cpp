#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
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

bool IsPalindrom(const std::string& s) {
  const size_t len = s.size();
  for (size_t i = 0; i < len / 2; ++i) {
    if (s[i] != s[len - 1 - i]) {
      return false;
    }
  }
  return true;
}

void FindSuitablePrefix(const std::string& s, std::vector<std::pair<size_t, size_t>>& ans) {
  // std::cout << "\n" << s << " checking sufs:\n";
  ans.resize(0);
  std::string tmp;
  for (size_t i = 0; i <= s.size(); ++i) {
      // std::cout << s.substr(i, s.size() - i) << "  <- checking\n";
    if (IsPalindrom(s.substr(i, s.size() - i))) {
      // std::cout << s.substr(i, s.size() - i) << "  <- !!!suf palindrom\n";
      tmp = s.substr(0, i);
      std::reverse(tmp.rbegin(), tmp.rend());
      ans.push_back({Hash(s.substr(0, i)), Hash(tmp)});
    }
  }
}

void FindSuitableSuffix(const std::string& s, std::vector<std::pair<size_t, size_t>>& ans) {
  // std::cout << "\n" << s << " checking prefs:\n";
  ans.resize(0);
  std::string tmp;
  for (size_t i = 0; i <= s.size(); ++i) {
    // std::cout << s.substr(0, i) << "  <- checking\n";
    if (IsPalindrom(s.substr(0, i))) {
      // std::cout << s.substr(0, i) << "  <- pref palindrom\n";
      tmp = s.substr(i, s.size() - i);
      std::reverse(tmp.rbegin(), tmp.rend());
      // std::cout << tmp << "---\n";
      ans.push_back({Hash(s.substr(i, s.size() - i)), Hash(tmp)});
    }
  }
}

int main() {
  degs.resize(10);
  CountDegs(degs);
  int n;
  std::cin >> n;
  std::vector<std::string> s(n);
  std::vector<std::pair<size_t, size_t>> tmp;
  using pair = std::pair<int, int>;
  std::set<pair> ans;
  std::unordered_map<size_t, std::vector<int>> hashs_prefix;
  std::unordered_map<size_t, std::vector<int>> hashs_sufix;
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    FindSuitablePrefix(s[i], tmp);
    for (auto& j : tmp) {
      hashs_prefix[j.first].push_back(i);
    }
    hashs_prefix[Hash(s[i])].push_back(i);

    FindSuitableSuffix(s[i], tmp);
    for (auto& j : tmp) {
      hashs_sufix[j.second].push_back(i);
    }
  }

  for (int i = 0; i < n; ++i) { // answering cycle
    if (hashs_sufix.count(Hash(s[i])) > 0) {
      for (auto j : hashs_sufix[Hash(s[i])]) {
        if (j != i) {
          ans.insert({i, j});
        }
      }
    }

    std::reverse(s[i].rbegin(), s[i].rend());
    if (hashs_prefix.count(Hash(s[i])) > 0) {
      for (auto j : hashs_prefix[Hash(s[i])]) {
        if (j != i) {
          ans.insert({j, i});
        }
      }
      // ans.insert({
      //   hashs_prefix[Hash(s[i])], i
      // });
      // std::cout << "pref: " << hashs_prefix[Hash(s[i])] << "  " << i <<"\n";
    }
  }


  std::cout << ans.size() << "\n";
  for (auto i : ans) {
    std::cout << i.first + 1<< " " << i.second + 1<< "\n";
  }
  return 0;
}
