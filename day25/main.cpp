#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
  vector<uint32_t> locks;
  vector<uint32_t> keys;
  for (string str; cin >> str; )
  {
    uint32_t value = 0;
    string str1;
    for (int i = 0; i < 5; ++i)
    {
      cin >> str1;
      for (int j = 0; j < 5; ++j)
        value += ((str1[j] == '#') << (j * 4));
    }
    if (str == "#####")
      locks.push_back(value);
    else
      keys.push_back(value);
    cin >> str;
  }

  int ans = 0;
  for (auto const &lock : locks)
    for (auto const &key : keys)
    {
      bool fl = true;
      for (int sum = lock + key; sum > 0 && fl; sum >>= 4)
        fl &= ((sum & 0xF) <= 5);
      ans += fl;
    }
  cout << ans << endl;

  return 0;
}
