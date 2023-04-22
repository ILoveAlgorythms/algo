#include<iostream>
#include<vector>
#include<string>
// КМП

int main() {
  std::string pat;
  std::string s;
  std::cin >> s >> pat;
  std::string a (pat + "0" + s);
  std::vector<int> ans(a.size());
  ans[s.size()] = 0;
  int patsize = pat.size();
  for (int i = patsize; i < a.size(); ++i) {
    ans[i] = a[ans[i - 1]] == s[ans[i - 1]] ? ans[i - 1] + 1 : 0;
  }
  for (int i = patsize; i < a.size(); ++i) {
    if (ans[i] == patsize) {
      std::cout << i << "\n";
    }
  }
  return 0;
}
