#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cassert>

using namespace std;

struct point
{
  int x, y;
};

struct position
{
  point tile, direction;
};

bool operator<(point const &a, point const &b)
{
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(point const &a, point const &b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator<(position const &a, position const &b)
{
  return a.tile < b.tile || (a.tile == b.tile && a.direction < b.direction);
}

point operator+(point const &a, point const &b)
{
  return {a.x + b.x, a.y + b.y};
}

point operator*(point const &a, int const &n)
{
  return {a.x * n, a.y * n};
}

point rotate_clockwise(point const &a)
{
  return {a.y, -a.x};
}

point rotate_anticlockwise(point const &a)
{
  return {-a.y, a.x};
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

  position start_position = {find_point(maze, 'S'), {1, 0}};
  point end_tile = find_point(maze, 'E');

  set<position> visited;
  set<pair<int, position>> next;
  map<position, int> distance;
  map<position, set<point>> paths;

  auto refresh_distance = [&next, &distance](position p, int new_distance)
  {
    next.erase({distance[p], p});
    distance[p] = new_distance;
    next.insert({distance[p], p});
  };
  refresh_distance(start_position, 0);
  paths[start_position] = {start_position.tile};

  int ans = 0;
  int ans_2 = 0;
  while (!next.empty())
  {
    auto [current_distance, current_position] = *next.begin();
    next.erase(next.begin());
    visited.insert(current_position);

    if (current_position.tile == end_tile)
    {
      ans = current_distance;
      ans_2 = ssize(paths[current_position]);
      break;
    }

    vector<pair<int, position>> candidates
    {
      {current_distance + 1,
        {current_position.tile + current_position.direction,
          current_position.direction}},
      {current_distance + 1000,
        {current_position.tile,
          rotate_clockwise(current_position.direction)}},
      {current_distance + 1000,
        {current_position.tile,
          rotate_anticlockwise(current_position.direction)}},
    };
    
    for (auto const &[candidate_distance, candidate_position] : candidates)
      if (maze[candidate_position.tile.y][candidate_position.tile.x] != '#' &&
          !visited.contains(candidate_position))
      {
        if (!distance.contains(candidate_position) ||
            distance[candidate_position] > candidate_distance)
        {
          refresh_distance(candidate_position, candidate_distance);
          paths[candidate_position] = paths[current_position];
          paths[candidate_position].insert(candidate_position.tile);
        }
        else if (distance.contains(candidate_position) &&
            distance[candidate_position] == candidate_distance)
          for (auto tile : paths[current_position])
            paths[candidate_position].insert(tile);
      }
  }

  cout << ans << endl;
  cout << ans_2 << endl;

  return 0;
}
