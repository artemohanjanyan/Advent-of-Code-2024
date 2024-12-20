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

  auto bfs = [&]()
  {
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
  };

  bfs();
  int fair_distance = distance[finish];

  map<int, int> cheats;
  for (int y = 0; y < ssize(maze); ++y)
    for (int x = 0; x < ssize(maze[0]); ++x)
      if (maze[y][x] == '#')
      {
        maze[y][x] = '.';
        bfs();
        if (distance[finish] < fair_distance)
          ++cheats[fair_distance - distance[finish]];
        maze[y][x] = '#';
      }

  //for (auto const &p : cheats)
  //  cout << p.first << " " << p.second << endl;

  int ans = 0;
  for (auto const &p : cheats)
    if (p.first >= 100)
      ans += p.second;
  cout << ans << endl;

  return 0;
}
