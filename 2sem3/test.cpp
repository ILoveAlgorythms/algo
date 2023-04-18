#include <iostream>
#include <queue>
#include <algorithm>

struct hui {
  int x;
  int y;
  hui(int x, int y) : x(x), y(y) {}
};

bool operator< (const hui& h, const hui& h2) {
  return h.x * h.y < h2.x * h2.y;
}

int main() {
  hui h1(2, 4);
  hui h2(2, 5);
  hui h3(3, 3);
  std::priority_queue<hui> d;
  d.push(h1);
  d.push(h2);
  d.push(h3);
  for (int i =0; i< 3; ++i) {
    std::cout << d.top().x << " " << d.top().y << "\n";
    d.pop();
  }
  return 0;
}