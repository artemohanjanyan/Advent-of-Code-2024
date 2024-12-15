#include <iostream>
#include <vector>
#include <cstdlib>
#include <set>

using namespace std;

struct point
{
  int64_t x, y;
};

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

point operator*(point const &a, int64_t const &n)
{
  return {a.x * n, a.y * n};
}

int64_t modmod(int64_t a, int64_t b)
{
  return ((a % b) + b) % b;
}

struct robot_t
{
  point position;
  point velocity;
};

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "please pass max_x and max_y" << "\n";
    return 0;
  }

  vector<robot_t> robots;
  for (char c; cin >> c; )
  {
    robots.push_back({});
    auto &robot = robots.back();
    cin >> c >> robot.position.x >> c >> robot.position.y
        >> c >> c >> robot.velocity.x >> c >> robot.velocity.y;
  }

  int64_t max_x = atoi(argv[1]);
  int64_t max_y = atoi(argv[2]);

  int64_t q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  for (auto const &robot : robots)
  {
    point new_position = robot.position + robot.velocity * 100;
    int64_t x = modmod(new_position.x, max_x);
    int64_t y = modmod(new_position.y, max_y);
    if (x < max_x / 2 && y < max_y / 2)
      ++q1;
    else if (x < max_x / 2 && y > max_y / 2)
      ++q2;
    else if (x > max_x / 2 && y < max_y / 2)
      ++q3;
    else if (x > max_x / 2 && y > max_y / 2)
      ++q4;
  }
  cout << q1 * q2 * q3 * q4 << "\n";

  for (int i = 1; i <= 11000; ++i)
  {
    cout << "step " << i << "\n";
    if (i % 100 == 0)
      cerr << "step " << i << endl;
    for (auto &robot : robots)
      robot.position = robot.position + robot.velocity;
    set<point> positions;
    for (auto &robot : robots)
    {
      int64_t x = modmod(robot.position.x, max_x);
      int64_t y = modmod(robot.position.y, max_y);
      positions.insert({x, y});
    }
    for (int y = 0; y < max_y; ++y)
    {
      for (int x = 0; x < max_x; ++x)
        if (positions.contains({x, y}))
          cout << '*';
        else
          cout << '.';
      cout << "\n";
    }
    cout << "\n";
  }

  return 0;
}
