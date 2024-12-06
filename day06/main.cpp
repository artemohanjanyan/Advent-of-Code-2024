#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  vector<string> situation;
  string str;
  while (getline(cin, str))
    situation.push_back(str);

  int direction[2] = {0, -1};
  int position[2] = {-1, -1};
  for (int y = 0; y < ssize(situation) && position[0] == -1; ++y)
    for (int x = 0; x < ssize(situation[0]); ++x)
      if (situation[y][x] == '^')
      {
        position[0] = x;
        position[1] = y;
        break;
      }
  int start_position[2] = { position[0], position[1] };
  situation[position[1]][position[0]] = 'X';

  while (position[0] >= 0 && position[1] >= 0 &&
      position[1] < ssize(situation) && position[0] < ssize(situation[0]))
  {
    position[0] += direction[0];
    position[1] += direction[1];
    situation[position[1]][position[0]] = 'X';
    int next_position[2] =
      { position[0] + direction[0], position[1] + direction[1] };
    if (next_position[0] >= 0 && next_position[1] >= 0 &&
        next_position[1] < ssize(situation) &&
        next_position[0] < ssize(situation[0]) &&
        situation[next_position[1]][next_position[0]] == '#')
    {
      int tmp = direction[0];
      direction[0] = -direction[1];
      direction[1] = tmp;
    }
  }

  int ans = 0;
  for (int y = 0; y < ssize(situation); ++y)
    for (int x = 0; x < ssize(situation[0]); ++x)
      ans += situation[y][x] == 'X';

  cout << ans << endl;

  ans = 0;
  for (int y = 0; y < ssize(situation); ++y)
    for (int x = 0; x < ssize(situation[0]); ++x)
      if (situation[y][x] == 'X')
        situation[y][x] = '.';
  situation[start_position[1]][start_position[0]] = 'X';
  for (int y = 0; y < ssize(situation); ++y)
    for (int x = 0; x < ssize(situation[0]); ++x)
      if (situation[y][x] == '.')
      {
        situation[y][x] = '#';
        position[0] = start_position[0];
        position[1] = start_position[1];
        direction[0] = 0;
        direction[1] = -1;

        int next_position[2] =
          { position[0] + direction[0], position[1] + direction[1] };
        if (situation[next_position[1]][next_position[0]] == '#')
        {
          int tmp = direction[0];
          direction[0] = -direction[1];
          direction[1] = tmp;
        }

        int step_count;
        for (step_count = 0;
            position[0] >= 0 && position[1] >= 0 &&
            position[1] < ssize(situation) &&
            position[0] < ssize(situation[0]) &&
            step_count < ssize(situation) * ssize(situation[0]) * 5;
            ++step_count
            )
        {
          position[0] += direction[0];
          position[1] += direction[1];
          int next_position[2] =
            { position[0] + direction[0], position[1] + direction[1] };
          while (next_position[0] >= 0 && next_position[1] >= 0 &&
              next_position[1] < ssize(situation) &&
              next_position[0] < ssize(situation[0]) &&
              situation[next_position[1]][next_position[0]] == '#')
          {
            int tmp = direction[0];
            direction[0] = -direction[1];
            direction[1] = tmp;
            next_position[0] = position[0] + direction[0];
            next_position[1] = position[1] + direction[1];
          }
        }
        if (step_count == ssize(situation) * ssize(situation[0]) * 5)
          ++ans;

        situation[y][x] = '.';
      }

  cout << ans << endl;

  return 0;
}
