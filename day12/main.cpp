#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using point = pair<int, int>;
int const dc[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void dfs(point p, int current_region,
    vector<string> const &area, map<point, int> &region)
{
  region[p] = current_region;
  for (int ci = 0; ci < 4; ++ci)
  {
    point new_p = {p.first + dc[ci][0], p.second + dc[ci][1]};
    if (new_p.first >= 0 && new_p.second >= 0 &&
        new_p.second < ssize(area) && new_p.second < ssize(area[0]) &&
        area[p.first][p.second] == area[new_p.first][new_p.second] &&
        !region.contains(new_p))
      dfs(new_p, current_region, area, region);
  }
}

int main()
{
  vector<string> area;
  for (string str; getline(cin, str);)
    area.push_back(str);

  map<point, int> region;
  int current_region = -1;
  for (int i = 0; i < ssize(area); ++i)
    for (int j = 0; j < ssize(area[0]); ++j)
      if (!region.contains({i, j}))
        dfs({i, j}, ++current_region, area, region);

  map<int, pair<int, int>> perimeter_and_area;
  for (int i = 0; i < ssize(area); ++i)
    for (int j = 0; j < ssize(area[0]); ++j)
      ++perimeter_and_area[region[{i, j}]].second;

  for (int i = 1; i < ssize(area); ++i)
    for (int j = 0; j < ssize(area[0]); ++j)
      if (area[i - 1][j] != area[i][j])
      {
        ++perimeter_and_area[region[{i - 1, j}]].first;
        ++perimeter_and_area[region[{i, j}]].first;
      }
  for (int i = 0; i < ssize(area); ++i)
    for (int j = 1; j < ssize(area[0]); ++j)
      if (area[i][j - 1] != area[i][j])
      {
        ++perimeter_and_area[region[{i, j - 1}]].first;
        ++perimeter_and_area[region[{i, j}]].first;
      }
  for (int i = 0; i < ssize(area); ++i)
  {
    ++perimeter_and_area[region[{i, 0}]].first;
    ++perimeter_and_area[region[{i, ssize(area[0]) - 1}]].first;
  }
  for (int j = 0; j < ssize(area[0]); ++j)
  {
    ++perimeter_and_area[region[{0, j}]].first;
    ++perimeter_and_area[region[{ssize(area) - 1, j}]].first;
  }

  int ans = 0;
  for (auto const &[region_n, x] : perimeter_and_area)
    ans += x.first * x.second;
  cout << ans << endl;

  map<int, int> perimeter_2;
  for (int i = 1; i < ssize(area); ++i)
  {
    if (area[i - 1][0] != area[i][0])
    {
      ++perimeter_2[region[{i - 1, 0}]];
      ++perimeter_2[region[{i, 0}]];
    }
    for (int j = 1; j < ssize(area[0]); ++j)
      if (area[i - 1][j] != area[i][j])
      {
        ++perimeter_2[region[{i - 1, j}]];
        ++perimeter_2[region[{i, j}]];
        if (area[i - 1][j - 1] != area[i][j - 1])
        {
          if (area[i - 1][j - 1] == area[i - 1][j])
            --perimeter_2[region[{i - 1, j}]];
          if (area[i][j - 1] == area[i][j])
            --perimeter_2[region[{i, j}]];
        }
      }
  }
  for (int j = 1; j < ssize(area[0]); ++j)
  {
    if (area[0][j - 1] != area[0][j])
    {
      ++perimeter_2[region[{0, j - 1}]];
      ++perimeter_2[region[{0, j}]];
    }
    for (int i = 1; i < ssize(area); ++i)
      if (area[i][j - 1] != area[i][j])
      {
        ++perimeter_2[region[{i, j - 1}]];
        ++perimeter_2[region[{i, j}]];
        if (area[i - 1][j - 1] != area[i - 1][j])
        {
          if (area[i - 1][j - 1] == area[i][j - 1])
            --perimeter_2[region[{i, j - 1}]];
          if (area[i - 1][j] == area[i][j])
            --perimeter_2[region[{i, j}]];
        }
      }
  }
  ++perimeter_2[region[{0, 0}]];
  ++perimeter_2[region[{0, ssize(area[0]) - 1}]];
  ++perimeter_2[region[{0, 0}]];
  ++perimeter_2[region[{ssize(area) - 1, 0}]];
  for (int i = 1; i < ssize(area); ++i)
  {
    perimeter_2[region[{i, 0}]] += area[i - 1][0] != area[i][0];
    int jj = ssize(area[0]) - 1;
    perimeter_2[region[{i, jj}]] += area[i - 1][jj] != area[i][jj];
  }
  for (int j = 1; j < ssize(area[0]); ++j)
  {
    perimeter_2[region[{0, j}]] += area[0][j - 1] != area[0][j];
    int ii = ssize(area) - 1;
    perimeter_2[region[{ii, j}]] += area[ii][j - 1] != area[ii][j];
  }

  ans = 0;
  for (auto const &[region_n, x] : perimeter_and_area)
    ans += perimeter_2[region_n] * x.second;
  cout << ans << endl;

  return 0;
}
