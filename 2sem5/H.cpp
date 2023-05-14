// Вам нечего сказать, пока дед на печке в отставке
// Ась, старая школа,        КАРАСЬ!
// Я из Optik Russia, вы безобразней слова «залазь»
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Trie {
public:
  static constexpr const int64_t kNull = -1;
  struct Node {
    Node() = default;
    Node(int64_t parent, char symbol) : parent(parent), symbol(symbol){}

    bool HasChild(char symbol) {
      return children.find(symbol) != children.end();
    }

    std::unordered_map<char, int64_t> children;
    int64_t parent{-1};
    char symbol{};
    bool is_terminal{false};
  };

  Trie() : nodes_(1) {}

  int64_t Add(const std::string& key) {
    int64_t now = 0;
    for (auto symbol : key) {
      if (!nodes_[now].HasChild(symbol)) {
        nodes_.emplace_back(now, symbol);
        nodes_[now].children[symbol] = nodes_.size() - 1;
      }
      now = nodes_[now].children[symbol];
    }
    nodes_[now].is_terminal = true;
    return now;
  }

  Node& Get(int64_t index) {
    return nodes_.at(index);
  }

  size_t NodeCount() {
    return nodes_.size();
  }
private:
  std::vector<Node> nodes_; // вообще все вершины (ну и кринж)
};

class AhoKorasikAutomaton {
  public:
    AhoKorasikAutomaton(const std::vector<std::string>& patterns) 
      : patterns_(patterns) {
      int32_t i = 0;
      for (auto pattern : patterns) {
        pattern_mapper_[trie_.Add(pattern)] = i++;
      }
      suffix_links_.assign(trie_.NodeCount(), Trie::kNull);
      terminal_links_.assign(trie_.NodeCount(), Trie::kNull);
    }

    std::vector<std::string> MakeStep(char symbol) {
      state_ = CalcStep(state_, symbol);
      return ExtractMatches();
    }

    void ResetState() {
      state_ = 0;
    }

  private:
    std::vector<std::string> ExtractMatches() { // все патерны, которые входят в state
      std::vector<std::string> ans;
      size_t v = state_;
      while (v != 0) {
        auto& node = trie_.Get(v);
        if (node.is_terminal) {
          ans.push_back(patterns_[pattern_mapper_[v]]);
        }
        v = GetTerminalLink(v);
      }
      return ans;
    } 


    int64_t CalcStep(int64_t node, char symbol) {
      auto& v = trie_.Get(node);
      if (v.HasChild(symbol)) { // to(node, symbol) -- exists
        return v.children[symbol];
      }
      if (node == 0) { // root -> root
        return 0;
      }
      return CalcStep(GetSuffixLink(node), symbol);
    }

    int64_t GetTerminalLink(int64_t node) {
      if (terminal_links_[node] != Trie::kNull) { // уже вычислена
        return terminal_links_[node];
      }
      if (node == 0 || trie_.Get(node).parent == 0) { // корень или первая глубина
        terminal_links_[node] = 0;
        return 0;
      }
      int64_t v = GetSuffixLink(node);
      while (v != 0 && !trie_.Get(v).is_terminal) { // идём по суфиксным ссылкам пока не дойдём до терминала или корня
        v = terminal_links_[v] == Trie::kNull ? GetSuffixLink(v) : terminal_links_[v];
      }
      terminal_links_[node] = v;
      return v;
      
    }

    int64_t GetSuffixLink(int64_t node) {
      if (suffix_links_[node] != Trie::kNull) { // уже вычислена
        return suffix_links_[node];
      }
      if (node == 0 || trie_.Get(node).parent == 0) { // корень или первая глубина
        suffix_links_[node] = 0;
        return 0;
      }
      auto& v = trie_.Get(node);
      suffix_links_[node] = CalcStep(GetSuffixLink(v.parent), v.symbol); // link(to(v,c)) = to(link(v), c)
      return suffix_links_[node];
    }

    std::vector<int64_t> suffix_links_;
    std::vector<int64_t> terminal_links_;

    std::unordered_map<int64_t, size_t> pattern_mapper_;

    int64_t state_{0};
    Trie trie_;
    std::vector<std::string> patterns_;
};

class Matcher {
  public:
    Matcher(const std::vector<std::string>& patterns) 
      : automaton_(patterns) {}

    std::vector<std::pair<size_t, std::string>> FindMatches(const std::string& text) {
      automaton_.ResetState();
      std::vector<std::pair<size_t, std::string>> matches;
      for (auto i = 0UL; i < text.size(); ++i) {
        auto step_matches = automaton_.MakeStep(text[i]);
        for (auto& match : step_matches) {
          size_t pos = static_cast<size_t>(i - static_cast<int64_t>(match.length()) + 1);
          matches.emplace_back(pos, match);
        }
      }
      return matches;
    }

  private:
    AhoKorasikAutomaton automaton_;
};

int main() {
  std::string text;
  int n;
  std::cin >>  text >> n;
  std::vector<std::string> pats(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> pats[i];
  }
  std::unordered_map<std::string, std::vector<int>> ans;
  for (auto& i : pats) {
    ans.insert({i, std::vector<int>()});
  }
  Matcher matcher(pats);
  auto matchs = matcher.FindMatches(text);
  for (auto& i : matchs) {
    ans[i.second].push_back(i.first + 1);
  }
  for (auto& u : pats) {
    auto i = ans[u];
    std::cout << i.size();
    for (auto j : i) {
      std::cout << " " << j;
    }
    std::cout << "\n";
  }
}
