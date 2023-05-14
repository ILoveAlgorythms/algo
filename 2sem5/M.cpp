#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
// я не хочу быть красивым, я не хочу быть богатым
// я хочу быть автоматом
class SuffixAutomaton {
  static constexpr int64_t kBeforeRoot = -1;
  struct State {
    std::unordered_map<char, int64_t> go; // переходы
    int64_t len;
    int64_t suffix_link;
  };

 public:
  int CountAdd(std::string& s) {
    std::cout << s << "\n";
    int ans = 0;
    for (auto i : s) {
     int tmp= AddChar(i);
      ans += tmp;
      std::cout << i << ": " << tmp <<"  ans:  "<< ans <<"\n";
    }
    return ans;
  }

  bool Chek(std::string& s) {
    auto tmp = use_state_;
    use_state_ = 0;
    for (auto c : s) {
      if (!Step(c)) {
        use_state_ = tmp;
        return false;
      }
    }
    return true;
  }

  void ResetState() {
    use_state_ = 0;
  }

  bool Step(char symbol) {
    if (states_[use_state_].go.count(symbol) > 0) { // шланг ругается на contains
      use_state_ = states_[use_state_].go[symbol];
      return true;
    }
    return false;
  }

  SuffixAutomaton() : states_(1, {{}, 0, kBeforeRoot}) {}

  int AddChar(char symbol) {
    int ans = 0;
    int64_t new_state = MakeState(
      states_[last_state_].len + 1,
      0
    );

    int64_t p = last_state_;
    while (p != kBeforeRoot && states_[p].go.count(symbol) == 0) {
      states_[p].go[symbol] = new_state;
      p = states_[p].suffix_link;
    }

    if (p == kBeforeRoot) { // очевный
      states_[new_state].suffix_link = 0;
    } else {
      int64_t q = states_[p].go[symbol];
      ans += states_[p].len + 1;
      if (states_[p].len + 1 == states_[q].len) { // случай когда не появляется новых классов
        states_[new_state].suffix_link = q;
      } else {
        int64_t clone_id = MakeState(
          states_[p].len + 1, // s0 - лонгест
          states_[q].suffix_link // суфлинк
        );
        states_[clone_id].go = states_[q].go;
        while (p != kBeforeRoot && states_[p].go[symbol] == q) {
          states_[p].go[symbol] = clone_id;
          p = states_[p].suffix_link;
        }
        states_[q].suffix_link = states_[new_state].suffix_link = clone_id;
      }
    }

    last_state_ = new_state; // longest класса [S + c]
    return ans;
  }
 private:
  int64_t MakeState(int64_t len, int64_t suffix_link) {
    int64_t id = states_.size();
    states_.push_back({{}, len, suffix_link});
    return id;
  }
  int64_t last_state_{0};
  std::vector<State> states_;

  int64_t use_state_{0};
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SuffixAutomaton automaton;

  std::string buffer;
  std::cin >> buffer;
  std::cout << automaton.CountAdd(buffer);
  return 0;
}