#include <iostream>

#include <string>
#include <string_view>
#include <cctype>
#include <iterator>
#include <vector>

using namespace std;

int calc(string &section)
{
  size_t i = 0;
  int result = 0;
  while (i < section.size())
  {
    if (string_view{&*(section.begin() + i), 4} == "mul(")
    {
      i += 4;

      if (!isdigit(section[i]))
        continue;
      int a = 0;
      while (i < section.size() && isdigit(section[i]))
      {
        a = a * 10 + section[i] - '0';
        ++i;
      }

      if (i == section.size())
        return result;
      if (section[i] != ',')
        continue;
      ++i;

      if (i == section.size())
        return result;
      if (!isdigit(section[i]))
        continue;
      int b = 0;
      while (i < section.size() && isdigit(section[i]))
      {
        b = b * 10 + section[i] - '0';
        ++i;
      }

      if (i == section.size())
        return result;
      if (section[i] != ')')
        continue;

      result += a * b;
    }
    else
      ++i;
  }
  return result;
}

bool is_enabled = true;
int calc2(string &section)
{
  size_t i = 0;
  int result = 0;
  while (i < section.size())
  {
    if (string_view{&*(section.begin() + i), 4} == "mul(")
    {
      i += 4;

      if (!isdigit(section[i]))
        continue;
      int a = 0;
      while (i < section.size() && isdigit(section[i]))
      {
        a = a * 10 + section[i] - '0';
        ++i;
      }

      if (i == section.size())
        return result;
      if (section[i] != ',')
        continue;
      ++i;

      if (i == section.size())
        return result;
      if (!isdigit(section[i]))
        continue;
      int b = 0;
      while (i < section.size() && isdigit(section[i]))
      {
        b = b * 10 + section[i] - '0';
        ++i;
      }

      if (i == section.size())
        return result;
      if (section[i] != ')')
        continue;

      result += a * b * is_enabled;
    }
    else if (string_view{&*(section.begin() + i), 4} == "do()")
    {
      is_enabled = true;
      i += 4;
    }
    else if (string_view{&*(section.begin() + i), 7} == "don't()")
    {
      is_enabled = false;
      i += 7;
    }
    else
      ++i;
  }
  return result;
}

int main()
{
  vector<string> sections;
  string str;
  while (getline(cin, str))
    sections.push_back(str);

  int ans = 0;
  for (auto &section: sections)
    ans += calc(section);
  cout << ans << endl;

  ans = 0;
  for (auto &section: sections)
    ans += calc2(section);
  cout << ans << endl;

  return 0;
}
