#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

uint64_t concat(uint64_t a, uint64_t b)
{
  uint64_t c = b;
  while (c > 0)
  {
    a *= 10;
    c /= 10;
  }
  return a + b;
}

bool try_solve(uint64_t const target, vector<uint64_t> const &arguments, uint64_t const i, uint64_t acc)
{
  if (i == arguments.size())
    return target == acc;
  return try_solve(target, arguments, i + 1, acc + arguments[i]) ||
      try_solve(target, arguments, i + 1, acc * arguments[i]);
}

bool try_solve(pair<uint64_t, vector<uint64_t>> const &equation)
{
  return try_solve(equation.first, equation.second, 1, equation.second[0]);
}

bool try_solve_2(uint64_t const target, vector<uint64_t> const &arguments, uint64_t const i, uint64_t acc)
{
  if (i == arguments.size())
    return target == acc;
  return try_solve_2(target, arguments, i + 1, acc + arguments[i]) ||
      try_solve_2(target, arguments, i + 1, acc * arguments[i]) ||
      try_solve_2(target, arguments, i + 1, concat(acc, arguments[i]));
}

bool try_solve_2(pair<uint64_t, vector<uint64_t>> const &equation)
{
  return try_solve_2(equation.first, equation.second, 1, equation.second[0]);
}

int main()
{
  vector<pair<uint64_t, vector<uint64_t>>> equations;

  string str;
  while (getline(cin, str))
  {
    istringstream line_stream(str);
    char c;
    equations.push_back({});
    line_stream >> equations.back().first >> c;
    uint64_t n;
    while (line_stream >> n)
      equations.back().second.push_back(n);
  }

  uint64_t ans = 0;
  for (auto const &equation: equations)
    if (try_solve(equation))
      ans += equation.first;
  cout << ans << endl;
 
  ans = 0;
  for (auto const &equation: equations)
    if (try_solve_2(equation))
      ans += equation.first;
  cout << ans << endl;

  return 0;
}
