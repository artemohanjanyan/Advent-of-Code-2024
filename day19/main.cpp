#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
  string str;
  getline(cin, str);
  istringstream line_stream(str);
  vector<string> towels;
  while (line_stream >> str)
  {
    if (str.back() == ',')
      str.resize(str.size() - 1);
    towels.push_back(str);
  }
  vector<string> patterns;
  while (cin >> str)
    patterns.push_back(str);

  uint64_t ans1 = 0;
  uint64_t ans2 = 0;
  for (string const &pattern : patterns)
  {
    vector<uint64_t> dp;
    dp.resize(pattern.size() + 1);
    dp[0] = 1;
    for (int i = 1; i <= ssize(pattern); ++i)
      for (int j = 0; j < ssize(towels); ++j)
        if (ssize(towels[j]) <= i &&
            equal(towels[j].begin(), towels[j].end(), &pattern[i - ssize(towels[j])]))
          dp[i] += dp[i - ssize(towels[j])];
    ans1 += dp[pattern.size()] > 0;
    ans2 += dp[pattern.size()];
  }

  cout << ans1 << endl;
  cout << ans2 << endl;
  return 0;
}
