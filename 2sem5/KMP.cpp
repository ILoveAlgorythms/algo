#include<iostream>
#include<vector>
#include<string>
// Алгоритм Кнута-Морриса-Пратта

int main() {
  std::string pat;
  std::string s;
  std::cin >> s >> pat;
  std::string a (pat + "0" + s);
  std::vector<size_t> pref(a.size());
  pref[0] = 0;
  pref[pat.size()] = 0;
  for (size_t i = 1; i < a.size(); ++i) {
    if (a[i] == pat[pref[i - 1]]) {
      pref[i] = pref[i - 1] + 1; 
    } else {
      if (pref[i - 1] == 0) {
        pref[i] = 0;
        continue;
      }
      if (a[i] == pat[pref[pref[i - 1] - 1]]) {
        pref[i] = pref[pref[i - 1] - 1] + 1;
      } else if (a[i] == pat[0]) {
        pref[i] = 1;
      } else {
        pref[i] = 0;
      }
    }
  }
  // std::cout << a << "\n";
  for (size_t i = 0; i < a.size(); ++i) {
    if (pref[i] == pat.size()) {
      std::cout << i - 2 * pat.size() << "\n";
    }
    // std::cout << pref[i];
  }
  return 0;
}
