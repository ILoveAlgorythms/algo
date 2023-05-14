#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
// я не хочу быть красивым, я не хочу быть богатым
// я хочу быть автоматом
class SuffixAutomaton {
  static constexpr int64_t kBeforeRoot = -1;
  struct State {
    std::unordered_map<char, int64_t> go; // переходики
    int64_t len; // размер longest
    int64_t suffix_link; // суфлинк ведет в класс где лежит самый большой
                         // суффикс longest-а, который лежит в другом классе
                         // (класс эквивалентности состоит из longest и нескольких его самых длинных суффиксов)
  };
public:
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

  // добавляем по символу и перестраиваем автомат
  void AddChar(char symbol) {
    // создадим класс соответствующий [Sc]
    int64_t new_state = MakeState( 
      states_[last_state_].len + 1, 
      0
    );

    int64_t p = last_state_;
    // пока нет переходов добавляем новые переходы в класс [S + c]
    while (p != kBeforeRoot && states_[p].go.count(symbol) == 0) {
      states_[p].go[symbol] = new_state; 
      p = states_[p].suffix_link; 
    }

    if (p == kBeforeRoot) { // случай когда мы ушли за корень - символ был в нашей строке впервые
      states_[new_state].suffix_link = 0;
    } else {
      int64_t q = states_[p].go[symbol];
      if (states_[p].len + 1 == states_[q].len) { // случай когда не появляется новых классов
        states_[new_state].suffix_link = q;
      } else {
        int64_t clone_id = MakeState(
          states_[p].len + 1, // s0 - лонгест
          states_[q].suffix_link // суфлинк 
        );
        states_[clone_id].go = states_[q].go;
        // нужно перенаправить переходы в клона
        while (p != kBeforeRoot && states_[p].go[symbol] == q) {
          states_[p].go[symbol] = clone_id;
          p = states_[p].suffix_link;
        }
        states_[q].suffix_link = states_[new_state].suffix_link = clone_id;
      }
    }

    last_state_ = new_state; // longest класса [S + c]
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
  std::string a = "abbab";
  std::string b = "bb";
  // проверка на вхождениях подстроки
  SuffixAutomaton automaton;
  for (auto ch : a) {
    automaton.AddChar(ch);
  }

  automaton.ResetState();
  auto cnt = 0LU;
  for (auto ch : b) {
    if (automaton.Step(ch)) {
      ++cnt;
    } else{
      break;
    }
  }
  std::cout << cnt << std::endl;
  if (cnt == b.length()) {
    std::cout << cnt << " " << "REALLY\n";
  }

  return 0;
}