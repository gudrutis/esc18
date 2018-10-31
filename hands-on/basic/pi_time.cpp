#include <iostream>
#include <chrono>
#include <cassert>
#include <utility>
#include <cstdlib>

using Duration = std::chrono::duration<float>;

constexpr std::pair<double, Duration> pi(int n,bool b= true)
{
  assert(n > 0);
  if (b){
    std::chrono::high_resolution_clock::now();
  }

  auto const step = 1. / n;
  auto sum = 0.;
  for (int i = 0; i != n; ++i) {
    auto x = (i + 0.5) * step;
    sum += 4. / (1. + x * x);
  }

  if (b){
    std::chrono::high_resolution_clock::now();
  }

  return { step * sum, Duration{0}};
}

//template <int n>
//constexpr std::pair<double, Duration> pi(bool b){
//  std::chrono::time_point  start;
//  std::chrono::time_point  end;
//  if (b){
//    start = std::chrono::high_resolution_clock::now();
//  }
//
//  auto const step = 1. / n;
//  auto sum = 0.;
//  for (int i = 0; i != n; ++i) {
//    auto x = (i + 0.5) * step;
//    sum += 4. / (1. + x * x);
//  }
//
//if (b){
//end = std::chrono::high_resolution_clock::now();
//}
//
//  return { step * sum, end - start };
//}


int main(int argc, char* argv[])
{
  int const n = (argc > 1) ? std::atoi(argv[1]) : 10;
  int const m = 1000'000;

  auto const [value, time] = pi(n);
  auto const [value2, time2] = pi(m, false);

  std::cout << "pi = " << value
            << " for " << n << " iterations"
            << " in " << time.count() << " s\n";

  std::cout << "pi = " << value2
            << " for " << m << " iterations"
            << " in " << time2.count() << " s\n";
}
