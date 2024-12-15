#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

using warehouse_t = vector<vector<char>>;

bool can_move_box(warehouse_t const &warehouse, int i, int j, int di)
{
  if (warehouse[i][j] == '.')
    return true;
  if (warehouse[i][j] == '#')
    return false;
  if (warehouse[i][j] == '@')
    return can_move_box(warehouse, i + di, j, di);
  if (warehouse[i][j] == '[')
    return can_move_box(warehouse, i + di, j, di) && can_move_box(warehouse, i + di, j + 1, di);
  if (warehouse[i][j] == ']')
    return can_move_box(warehouse, i + di, j - 1, di) && can_move_box(warehouse, i + di, j, di);
  cerr << "unexpected char " << warehouse[i][j] << endl;
  return false;
}

void move_box(warehouse_t &warehouse, char c, int i, int j, int di)
{
  if (warehouse[i][j] == '.')
  {
    warehouse[i][j] = c;
    return;
  }
  if (warehouse[i][j] == '@')
  {
    move_box(warehouse, '@', i + di, j, di);
    assert(c == '.');
    warehouse[i][j] = '.';
    return;
  }
  if (warehouse[i][j] == '[')
  {
    move_box(warehouse, '[', i + di, j, di);
    move_box(warehouse, ']', i + di, j + 1, di);
    warehouse[i][j] = c;
    warehouse[i][j + 1] = '.';
    return;
  }
  if (warehouse[i][j] == ']')
  {
    move_box(warehouse, '[', i + di, j - 1, di);
    move_box(warehouse, ']', i + di, j, di);
    warehouse[i][j - 1] = '.';
    warehouse[i][j] = c;
    return;
  }
  cerr << "unexpected char " << warehouse[i][j] << endl;
}

void try_move_box(warehouse_t &warehouse, int &fish_i, int &fish_j, int di, int dj)
{
  if (di == 0)
  {
    int j = fish_j + dj;
    while (warehouse[fish_i][j] == '[' || warehouse[fish_i][j] == ']')
      j += dj;
    if (warehouse[fish_i][j] == '#')
      return;
    assert(warehouse[fish_i][j] == '.');

    for (; j != fish_j; j -= dj)
      swap(warehouse[fish_i][j], warehouse[fish_i][j - dj]);
    warehouse[fish_i][fish_j] = '.';
    fish_j += dj;
  }
  else if (can_move_box(warehouse, fish_i, fish_j, di))
  {
    move_box(warehouse, '.', fish_i, fish_j, di);
    fish_i += di;
  }
}

int main()
{
  vector<string> warehouse;
  for (string str; getline(cin, str), !str.empty(); )
    warehouse.push_back(str);

  vector<char> instructions;
  for (char c; cin >> c; )
    instructions.push_back(c);

  vector<vector<char>> wide_warehouse;
  for (int i = 0; i < ssize(warehouse); ++i)
  {
    wide_warehouse.push_back({});
    for (int j = 0; j < ssize(warehouse[0]); ++j)
      if (warehouse[i][j] == '#')
      {
        wide_warehouse[i].push_back('#');
        wide_warehouse[i].push_back('#');
      }
      else if (warehouse[i][j] == 'O')
      {
        wide_warehouse[i].push_back('[');
        wide_warehouse[i].push_back(']');
      }
      else if (warehouse[i][j] == '.')
      {
        wide_warehouse[i].push_back('.');
        wide_warehouse[i].push_back('.');
      }
      else if (warehouse[i][j] == '@')
      {
        wide_warehouse[i].push_back('@');
        wide_warehouse[i].push_back('.');
      }
      else
      {
        cerr << "unexpected char " << warehouse[i][j] << endl;
        return 0;
      }
  }

  int fish_i = 0;
  int fish_j = 0;
  for (int i = 0; i < ssize(warehouse) && fish_i == 0; ++i)
    for (int j = 0; j < ssize(warehouse[0]) && fish_i == 0; ++j)
      if (warehouse[i][j] == '@')
      {
        fish_i = i;
        fish_j = j;
      }
  for (char c : instructions)
  {
    int di = c == '^' ? -1 : (c == 'v' ? 1 : 0);
    int dj = c == '<' ? -1 : (c == '>' ? 1 : 0);
    int i = fish_i + di;
    int j = fish_j + dj;
    while (warehouse[i][j] == 'O')
    {
      i += di;
      j += dj;
    }
    if (warehouse[i][j] == '#')
      continue;
    assert(warehouse[i][j] == '.');
    warehouse[i][j] = 'O';
    warehouse[fish_i + di][fish_j + dj] = '@';
    warehouse[fish_i][fish_j] = '.';
    fish_i += di;
    fish_j += dj;
  }
  int ans = 0;
  for (int i = 0; i < ssize(warehouse); ++i)
    for (int j = 0; j < ssize(warehouse[0]); ++j)
      if (warehouse[i][j] == 'O')
        ans += i * 100 + j;
  cout << ans << endl;

  fish_i = 0;
  fish_j = 0;
  for (int i = 0; i < ssize(wide_warehouse) && fish_i == 0; ++i)
    for (int j = 0; j < ssize(wide_warehouse[0]) && fish_i == 0; ++j)
      if (wide_warehouse[i][j] == '@')
      {
        fish_i = i;
        fish_j = j;
      }
  for (char c : instructions)
  {
    int di = c == '^' ? -1 : (c == 'v' ? 1 : 0);
    int dj = c == '<' ? -1 : (c == '>' ? 1 : 0);
    try_move_box(wide_warehouse, fish_i, fish_j, di, dj);
  }
  ans = 0;
  for (int i = 0; i < ssize(wide_warehouse); ++i)
    for (int j = 0; j < ssize(wide_warehouse[0]); ++j)
      if (wide_warehouse[i][j] == '[')
        ans += i * 100 + j;
  cout << ans << endl;

  return 0;
}
