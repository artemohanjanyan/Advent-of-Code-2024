#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using p = pair<int64_t, int64_t>;

struct machine
{
  p a, b, prize;
};

int main()
{
  vector<machine> machines;
  for (string str; cin >> str; )
  {
    machines.push_back({});
    char c;
    cin >> str >> c >> c;
    cin >> machines.back().a.first;
    cin >> str >> c >> c;
    cin >> machines.back().a.second;
    cin >> str >> str >> c >> c;
    cin >> machines.back().b.first;
    cin >> str >> c >> c;
    cin >> machines.back().b.second;
    cin >> str >> c >> c;
    cin >> machines.back().prize.first;
    cin >> str >> c >> c;
    cin >> machines.back().prize.second;
  }

  int64_t ans = 0;
  for (auto const &m : machines)
  {
    int64_t min_cost = numeric_limits<int64_t>::max();
    for (int64_t an = 0; an <= 100; ++an)
      for (int64_t bn = 0; bn <= 100; ++bn)
        if (m.a.first * an + m.b.first * bn == m.prize.first &&
            m.a.second * an + m.b.second * bn == m.prize.second &&
            an * 3 + bn < min_cost)
          min_cost = an * 3 + bn;
    if (min_cost != numeric_limits<int64_t>::max())
      ans += min_cost;
  }
  cout << ans << endl;

  ans = 0;
  for (auto &m : machines)
  {
    m.prize.first += 10000000000000;
    m.prize.second += 10000000000000;
    int64_t nb = (m.prize.second * m.a.first - m.prize.first * m.a.second) /
      (m.a.first * m.b.second - m.b.first * m.a.second);
    int64_t na = (m.prize.first - m.b.first * nb) / m.a.first;
    if (m.a.first * na + m.b.first * nb == m.prize.first &&
        m.a.second * na + m.b.second * nb == m.prize.second)
      ans += na * 3 + nb;
  }
  cout << ans << endl;

  return 0;
}
