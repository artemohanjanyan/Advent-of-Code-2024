#include <iostream>
#include <sstream>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

bool check(vector<int> const &report)
{
  bool increasing = report[0] < report[1];
  for (size_t i = 1; i < report.size(); ++i)
  {
    int diff = abs(report[i - 1] - report[i]);
    if (increasing != (report[i - 1] < report[i]) || diff < 1 || diff > 3)
      return false;
  }
  return true;
}

bool check_with_tolerance(vector<int> &report)
{
  if (check(report))
    return true;
  for (size_t i = 0; i < report.size(); ++i)
  {
    int level = report[i];
    report.erase(report.begin() + i);
    bool result = check(report);
    report.insert(report.begin() + i, level);
    if (result)
      return true;
  }
  return false;
}

int main()
{
  vector<vector<int>> reports;
  string str;
  while (getline(cin, str))
  {
    istringstream line_stream(str);
    reports.push_back({});
    int x;
    while (line_stream >> x)
      reports.back().push_back(x);
  }

  int ans = 0;
  for (auto const &report: reports)
  {
    if (check(report))
      ++ans;
  }
  cout << ans << endl;

  ans = 0;
  for (auto &report: reports)
  {
    if (check_with_tolerance(report))
      ++ans;
  }
  cout << ans << endl;

  return 0;
}
