#include<iostream>
#include<vector>
#include<string>
// MUHAHA

int main() {
  std::string pat;
  std::string s;
  std::cin >> s >> pat;
  std::string a (pat + "0" + s);
  std::vector<size_t> pref(a.size(), 0);
  for (size_t i = 1; i < a.size(); ++i) {
    pref[i] = a[i] == pat[pref[i - 1]] ? pref[i - 1] + 1 : (pref[i - 1] == 0 ? 0 : (a[i] == pat[pref[pref[i - 1] - 1]] ? pref[i] = pref[pref[i - 1] - 1] + 1 : 0));
  }
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << (pref[i] == pat.size() ? std::to_string(i - 2 * pat.size()) + "\n" : "");
  }
  return 0;
}
