#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  vector<pair<int, int>> rules;
  string str;
  char c;
  while (getline(cin, str))
  {
    if (str.empty())
      break;
    istringstream line_stream(str);
    rules.push_back({});
    line_stream >> rules.back().first >> c >> rules.back().second;
  }
  vector<vector<int>> updates;
  while (getline(cin, str))
  {
    istringstream line_stream(str);
    updates.push_back({});
    int page_number;
    line_stream >> page_number;
    updates.back().push_back(page_number);
    while (line_stream >> c >> page_number)
      updates.back().push_back(page_number);
  }

  int ans = 0;
  int ans2 = 0;
  for (auto &update: updates)
  {
    bool is_ok = true;
    for (int update_i = 0; update_i < ssize(update) && is_ok; ++update_i)
      for (int update_j = update_i + 1; update_j < ssize(update) && is_ok; ++update_j)
        for (auto const &rule: rules)
          if (rule.second == update[update_i] && rule.first == update[update_j])
          {
            is_ok = false;
            break;
          }
    if (is_ok)
      ans += update[update.size() / 2];
    else
    {
      is_ok = false;
      while (!is_ok)
      {
        int update_i, update_j;
        is_ok = true;
        for (update_i = 0; update_i < ssize(update) && is_ok; ++update_i)
        {
          for (update_j = update_i + 1; update_j < ssize(update) && is_ok; ++update_j)
          {
            for (auto const &rule: rules)
              if (rule.second == update[update_i] && rule.first == update[update_j])
              {
                is_ok = false;
                break;
              }
            if (!is_ok)
              break;
          }
          if (!is_ok)
            break;
        }
        if (!is_ok)
          swap(update[update_i], update[update_j]);
      }
      ans2 += update[update.size() / 2];
    }
  }
  cout << ans << endl;
  cout << ans2 << endl;

  return 0;
}
