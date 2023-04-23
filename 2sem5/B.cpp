#include<iostream>
#include<vector>
#include<string>

size_t Kmp (std::string& pat, std::string& str) {
  size_t min_len = std::min(pat.size(), str.size());
  const std::string kA (pat.substr(pat.size() - min_len) + "0" + str.substr(str.size() - min_len));

  std::vector<size_t> pref(kA.size(), 0);
  for (size_t i = 1; i < kA.size(); ++i) {
    if (kA[i] == pat[pref[i - 1]]) {
      pref[i] = pref[i - 1] + 1; 
    } else {
      if (pref[i - 1] == 0) {
        pref[i] = 0;
        continue;
      }
      if (kA[i] == pat[pref[pref[i - 1] - 1]]) {
        pref[i] = pref[pref[i - 1] - 1] + 1;
        continue;
      } 
      if (kA[i] == pat[0]) {
        pref[i] = 1;
        continue;
      }
      pref[i] = 0;
    }
  }
  return pref.back();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  std::string current_res;
  std::cin >> current_res;
  std::string term;
  for (size_t i = 1; i < n; ++i) {
    std::cin >> term;
    size_t maxpreflen = Kmp(term, current_res);
    for (size_t j = maxpreflen; j < term.size(); ++j) {
      current_res.push_back(term[j]);
    }
    // current_res = current_res + term.substr(maxpreflen);
  }
  std::cout << current_res << "\n";
  return 0;
}
