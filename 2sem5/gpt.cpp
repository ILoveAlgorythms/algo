#include <cmath>
#include <complex>
#include <vector>
#include <iostream>
// фурье
using cplx = std::complex<double>;
const double kPi = 3.141592653589793238462643383279;

void Fft(std::vector<cplx>& vec, bool obratnoe) {
    long long int n = vec.size();
    if (n == 1) {
      return;
    }
    
    std::vector<cplx> even(n/2);
    std::vector<cplx> odd(n/2);
    for (long long int i = 0; i < n; i += 2) {
      even[i / 2] = vec[i];
      odd[i / 2] = vec[i + 1];
    }
    
    Fft(even, obratnoe);
    Fft(odd, obratnoe);
    
    double ang = 2*kPi/n * (obratnoe ? -1 : 1);
    cplx omega(1);
    cplx mnozh(cos(ang), sin(ang));
    const cplx kObratnoeflag = (obratnoe ? 0.5 : 1);

    for (long long int i = 0; i < n/2; ++i) {
      vec[i] = (even[i] + omega * odd[i]) * kObratnoeflag;
      vec[i+n/2] = (even[i] - omega * odd[i]) * kObratnoeflag;
      omega *= mnozh;
    }
}

void Umnozh(std::vector<long long int>& p, std::vector<long long int>& q, std::vector<long long int>& ans) {
  auto n = 1LU;
  while (n < p.size() + q.size()) {
    n *= 2;
  }
  std::vector<cplx> discret_a(p.begin(), p.end());
  discret_a.resize(n);
  Fft(discret_a, false);
  std::vector<cplx> discret_b(q.begin(), q.end());
  discret_b.resize(n);
  Fft(discret_b, false);
  
  for (auto i = 0LU; i < n; ++i) {
    discret_a[i] *= discret_b[i];
  }
  
  Fft(discret_a, true);

  ans.resize(n);
  for (auto i = 0LU; i < n; ++i) {
    ans[i] = round(discret_a[i].real());
  }
}

int main() {
  std::vector<long long int> p;
  std::vector<long long int> q;
  std::vector<long long int> ans;

  long long int n;
  std::cin >> n;
  p.resize(n + 1);
  for(long long int i = 0; i < n + 1; ++i) {
    std::cin >> p[i];
  }
  long long int m;
  std::cin >> m;
  q.resize(n + 1);
  for(long long int i = 0; i < m + 1; ++i) {
    std::cin >> q[i];
  }

  Umnozh(p, q, ans);
  std::cout << n + m << " ";
  for (long long int i = 0; i < n + m + 1; ++i) {
    std::cout << ans[i] << " ";
  }
  return 0;
}
