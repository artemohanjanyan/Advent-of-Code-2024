#include <iostream>
#include <string>
#include <vector>

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

int numeric_part(string const &code)
{
  return static_cast<int>(code[0] - '0') * 100 +
      static_cast<int>(code[1] - '0') * 10 +
      static_cast<int>(code[2] - '0');
}

string arrow_sequence(vector<point> const &points_to_press, point a_point, point point_to_avoid)
{
  string ans;
  point current_point = a_point;
  for (point const &p : points_to_press)
  {
    ans += go_from_to(current_point, p, point_to_avoid);
    ans += 'A';
    current_point = p;
  }
  return ans;
}

string arrow_sequence_2(vector<point> const &points_to_press, point a_point, point point_to_avoid)
{
  string ans;
  point current_point = a_point;
  for (point const &p : points_to_press)
  {
    ans += go_from_to_2(current_point, p, point_to_avoid);
    ans += 'A';
    current_point = p;
  }
  return ans;
}

int main()
{
  vector<string> codes;
  for (string str; cin >> str; )
    codes.push_back(str);

  int ans = 0;
  for (string const &code : codes)
  {
    vector<point> points_to_press = decode_numpad(code);
    string buttons_to_press = arrow_sequence(points_to_press, {2, 3}, {0, 3});
    points_to_press = decode_arrowpad(buttons_to_press);
    buttons_to_press = arrow_sequence(points_to_press, {2, 0}, {0, 0});
    points_to_press = decode_arrowpad(buttons_to_press);
    buttons_to_press = arrow_sequence(points_to_press, {2, 0}, {0, 0});
    ans += numeric_part(code) * ssize(buttons_to_press);
  }

  cout << ans << endl;

  return 0;
}
