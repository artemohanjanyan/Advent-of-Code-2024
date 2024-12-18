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

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    cerr << "provide max_x, max_y and first_byte_n" << endl;
    return 0;
  }

  int const max_x = atoi(argv[1]);
  int const max_y = atoi(argv[2]);
  int const first_byte_n = atoi(argv[3]);

  int a, b;
  char c;
  vector<point> positions;
  while (cin >> a >> c >> b)
    positions.push_back({a, b});

  set<point> corrupted(positions.begin(), positions.begin() + first_byte_n);
  map<point, int> distance;
  point start{0, 0}, finish{max_x - 1, max_y - 1};
  auto is_in_bounds = [&max_x, &max_y](point const &p)
  {
    return p.x >= 0 && p.y >= 0 && p.x < max_x && p.y < max_y;
  };
  queue<point> q;
  q.push(start);
  distance[start] = 0;
  while (!q.empty() && !distance.contains(finish))
  {
    point current = q.front();
    int current_distance = distance[current];
    q.pop();
    for (int i = 0; i < 4; ++i)
    {
      point next_point = current + dp[i];
      if (!is_in_bounds(next_point) ||
          distance.contains(next_point) ||
          corrupted.contains(next_point))
        continue;
      distance[next_point] = current_distance + 1;
      q.push(next_point);
    }
  }

  if (distance.contains(finish))
    cout << distance[finish] << endl;
  else
    cout << "didn't finsh path to finish" << endl;

  corrupted.clear();
  for (point const &corrupted_point : positions)
  {
    corrupted.insert(corrupted_point);
    distance.clear();
    while (!q.empty())
      q.pop();
    q.push(start);
    distance[start] = 0;
    while (!q.empty() && !distance.contains(finish))
    {
      point current = q.front();
      int current_distance = distance[current];
      q.pop();
      for (int i = 0; i < 4; ++i)
      {
        point next_point = current + dp[i];
        if (!is_in_bounds(next_point) ||
            distance.contains(next_point) ||
            corrupted.contains(next_point))
          continue;
        distance[next_point] = current_distance + 1;
        q.push(next_point);
      }
    }
    if (!distance.contains(finish))
    {
      cout << corrupted_point.x << "," << corrupted_point.y << endl;
      return 0;
    }
  }

  return 0;
}
