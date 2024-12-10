#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

int const dc[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void calculate_score(int i, int j,
    int start_i, int start_j,
    vector<string> const &area,
    map<pair<int, int>, set<pair<int, int>>> &reachable_ends)
{
  if (area[i][j] == '9')
  {
    reachable_ends[{start_i, start_j}].insert({i, j});
    return;
  }
  for (int k = 0; k < 4; ++k)
  {
    int ii = i + dc[k][0];
    int jj = j + dc[k][1];
    if (ii >= 0 && jj >= 0 && ii < ssize(area) && jj < ssize(area[0]) &&
        area[ii][jj] == area[i][j] + 1)
      calculate_score(ii, jj, start_i, start_j, area, reachable_ends);
  }
  return;
}

int calculate_score_2(int i, int j, vector<string> const &area)
{
  if (area[i][j] == '9')
    return 1;
  int score = 0;
  for (int k = 0; k < 4; ++k)
  {
    int ii = i + dc[k][0];
    int jj = j + dc[k][1];
    if (ii >= 0 && jj >= 0 && ii < ssize(area) && jj < ssize(area[0]) &&
        area[ii][jj] == area[i][j] + 1)
      score += calculate_score_2(ii, jj, area);
  }
  return score;
}

int main()
{
  vector<string> area;
  for (string str; getline(cin, str);)
    area.push_back(str);

  int ans = 0;
  map<pair<int, int>, set<pair<int, int>>> reachable_ends;
  for (int i = 0; i < ssize(area); ++i)
    for (int j = 0; j < ssize(area[0]); ++j)
      if (area[i][j] == '0')
      {
        calculate_score(i, j, i, j, area, reachable_ends);
        ans += ssize(reachable_ends[{i, j}]);
      }
  cout << ans << endl;

  ans = 0;
  for (int i = 0; i < ssize(area); ++i)
    for (int j = 0; j < ssize(area[0]); ++j)
      if (area[i][j] == '0')
        ans += calculate_score_2(i, j, area);
  cout << ans << endl;

  return 0;
}
