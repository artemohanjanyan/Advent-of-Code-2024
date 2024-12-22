#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

struct point
{
  int x, y;
};

bool operator==(point const &a, point const &b)
{
  return a.x == b.x && a.y == b.y;
}

vector<point> decode_numpad(string const &code)
{
  vector<point> ans;
  for (char c : code)
    if (c == 'A')
      ans.push_back({2, 3});
    else if (c == '0')
      ans.push_back({1, 3});
    else if (c >= '7')
      ans.push_back({c - '7', 0});
    else if (c >= '4')
      ans.push_back({c - '4', 1});
    else if (c >= '1')
      ans.push_back({c - '1', 2});
  return ans;
}

vector<point> decode_arrowpad(string const &code)
{
  vector<point> ans;
  for (char c : code)
    if (c == 'A')
      ans.push_back({2, 0});
    else if (c == '^')
      ans.push_back({1, 0});
    else if (c == '<')
      ans.push_back({0, 1});
    else if (c == 'v')
      ans.push_back({1, 1});
    else if (c == '>')
      ans.push_back({2, 1});
  return ans;
}

string go_from_to(point a, point b, point point_to_avoid)
{
  string ans1;
  while (a.x != b.x)
    if (a.x > b.x)
    {
      ans1 += '<';
      --a.x;
    }
    else
    {
      ans1 += '>';
      ++a.x;
    }
  bool fl = a == point_to_avoid;
  string ans2;
  while (a.y != b.y)
    if (a.y > b.y)
    {
      ans2 += '^';
      --a.y;
    }
    else
    {
      ans2 += 'v';
      ++a.y;
    }
  return fl ? ans2 + ans1 : ans1 + ans2;
}

string go_from_to_2(point a, point b, point point_to_avoid)
{
  string ans1;
  while (a.y != b.y)
    if (a.y > b.y)
    {
      ans1 += '^';
      --a.y;
    }
    else
    {
      ans1 += 'v';
      ++a.y;
    }
  bool fl = a == point_to_avoid;
  string ans2;
  while (a.x != b.x)
    if (a.x > b.x)
    {
      ans2 += '<';
      --a.x;
    }
    else
    {
      ans2 += '>';
      ++a.x;
    }
  return fl ? ans2 + ans1 : ans1 + ans2;
}

uint64_t numeric_part(string const &code)
{
  return static_cast<uint64_t>(code[0] - '0') * 100 +
      static_cast<uint64_t>(code[1] - '0') * 10 +
      static_cast<uint64_t>(code[2] - '0');
}

vector<string> arrow_sequences(vector<point> const &points_to_press, point a_point, point point_to_avoid)
{
  vector<string> paths;
  paths.push_back("");
  point current_point = a_point;
  for (point const &p : points_to_press)
  {
    string path1 = go_from_to(current_point, p, point_to_avoid);
    string path2 = go_from_to_2(current_point, p, point_to_avoid);
    if (path1 == path2)
      for (auto &path : paths)
        path += path1 + 'A';
    else
    {
      int path_n = ssize(paths);
      for (int i = 0; i < path_n; ++i)
        paths.push_back(paths[i]);
      for (int i = 0; i < path_n; ++i)
        paths[i] += path1 + 'A';
      for (int i = 0; i < path_n; ++i)
        paths[i + path_n] += path2 + 'A';
    }
    current_point = p;
  }
  return paths;
}

vector<string> extract_sections(string const &sequence)
{
  vector<string> sections;
  if (sequence.back() != 'A')
  {
    cerr << "bad arrow sequence " << sequence << endl;
    return sections;
  }

  auto section_start = sequence.begin();
  for (auto it = sequence.begin(); it != sequence.end(); ++it)
    if (*it == 'A')
    {
      sections.push_back(string(section_start, next(it)));
      section_start = next(it);
    }
  return sections;
}

struct solver
{
  map<pair<int, string>, uint64_t> dp;

  uint64_t get(int n, string const &section)
  {
    if (n == 0)
      return section.size();
    if (dp.contains({n, section}))
      return dp[{n, section}];
    vector<point> points_to_press = decode_arrowpad(section);
    vector<string> sequences = arrow_sequences(points_to_press, {2, 0}, {0, 0});
    uint64_t best = numeric_limits<uint64_t>::max();
    for (string const &sequence : sequences)
    {
      uint64_t ans = 0;
      vector<string> sections = extract_sections(sequence);
      for (string const &section_2 : sections)
        ans += get(n - 1, section_2);
      best = min(ans, best);
    }
    dp[{n, section}] = best;
    return best;
  }
};

int main()
{
  vector<string> codes;
  for (string str; cin >> str; )
    codes.push_back(str);

  solver s;

  auto solve = [&codes, &s](int const arrowpad_n)
  {
    uint64_t ans = 0;
    for (string const &code : codes)
    {
      vector<point> points_to_press = decode_numpad(code);
      vector<string> sequences = arrow_sequences(points_to_press, {2, 3}, {0, 3});
      uint64_t best = numeric_limits<uint64_t>::max();
      for (string const &sequence : sequences)
      {
        vector<string> sections = extract_sections(sequence);
        uint64_t current = 0;
        for (string const &section : sections)
          current += s.get(arrowpad_n, section);
        best = min(best, current);
      }
      ans += numeric_part(code) * best;
    }
    return ans;
  };

  cout << solve(2) << endl;
  cout << solve(25) << endl;

  return 0;
}
