#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>

using namespace std;

struct point
{
  int x, y;
};

point const dp[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool operator<(point const &a, point const &b)
{
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(point const &a, point const &b)
{
  return a.x == b.x && a.y == b.y;
}

point operator+(point const &a, point const &b)
{
  return {a.x + b.x, a.y + b.y};
}

point operator*(point const &a, int const &n)
{
  return {a.x * n, a.y * n};
}

point find_point(vector<string> const &maze, char c)
{
  for (int y = 0; y < ssize(maze); ++y)
    for (int x = 0; x < ssize(maze[0]); ++x)
      if (maze[y][x] == c)
        return {x, y};
  cerr << "didn't find " << c << endl;
  return {-1, -1};
}

int main()
{
  vector<string> maze;
  for (string str; getline(cin, str); )
    maze.push_back(str);

  map<point, int> distance;
  point start = find_point(maze, 'S');
  point finish = find_point(maze, 'E');;
  auto is_in_bounds = [&maze](point const &p)
  {
    return p.x >= 0 && p.y >= 0 && p.x < ssize(maze[0]) && p.y < ssize(maze);
  };

  distance.clear();
  distance[start] = 0;
  queue<point> q;
  q.push(start);
  while (!q.empty() && !distance.contains(finish))
  {
    point current = q.front();
    int current_distance = distance[current];
    q.pop();
    for (int i = 0; i < 4; ++i)
    {
      point next_point = current + dp[i];
      if (!is_in_bounds(next_point) ||
          maze[next_point.y][next_point.x] == '#' ||
          distance.contains(next_point))
        continue;
      distance[next_point] = current_distance + 1;
      q.push(next_point);
    }
  }

  map<int, int> cheats;
  for (int y = 0; y < ssize(maze); ++y)
    for (int x = 0; x < ssize(maze[0]); ++x)
      if (maze[y][x] != '#')
        for (int dy = -2; dy <= 2; ++dy)
          for (int dx = -2; dx <= 2; ++dx)
            if ((dx != 0 || dy != 0) && abs(dx) + abs(dy) <= 2)
            {
              point cheat_end_point = point{x, y} + point{dx, dy};
              if (is_in_bounds(cheat_end_point) &&
                  maze[cheat_end_point.y][cheat_end_point.x] != '#')
              {
                int cheat_saving = distance[cheat_end_point]
                  - distance[point{x, y}] - abs(dx) - abs(dy);
                if (cheat_saving > 0)
                  ++cheats[cheat_saving];
              }
            }

  //for (auto const &p : cheats)
  //  cout << p.first << " " << p.second << endl;

  int ans = 0;
  for (auto const &p : cheats)
    if (p.first >= 100)
      ans += p.second;
  cout << ans << endl;

  cheats.clear();
  for (int y = 0; y < ssize(maze); ++y)
    for (int x = 0; x < ssize(maze[0]); ++x)
      if (maze[y][x] != '#')
        for (int dy = -20; dy <= 20; ++dy)
          for (int dx = -20; dx <= 20; ++dx)
            if ((dx != 0 || dy != 0) && abs(dx) + abs(dy) <= 20)
            {
              point cheat_end_point = point{x, y} + point{dx, dy};
              if (is_in_bounds(cheat_end_point) &&
                  maze[cheat_end_point.y][cheat_end_point.x] != '#')
              {
                int cheat_saving = distance[cheat_end_point]
                  - distance[point{x, y}] - abs(dx) - abs(dy);
                if (cheat_saving > 0)
                  ++cheats[cheat_saving];
              }
            }
  ans = 0;
  for (auto const &p : cheats)
    if (p.first >= 100)
      ans += p.second;
  cout << ans << endl;

  return 0;
}
