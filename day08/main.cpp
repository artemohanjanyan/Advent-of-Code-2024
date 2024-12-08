#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

pair<int, int> operator+(pair<int, int> const &a, pair<int, int> const &b)
{
  return {a.first + b.first, a.second + b.second};
}

pair<int, int> operator-(pair<int, int> const &a, pair<int, int> const &b)
{
  return {a.first - b.first, a.second - b.second};
}

pair<int, int> normalize(pair<int, int> a)
{
  int x = abs(a.first), y = abs(a.second);
  while (x > 0 && y > 0)
    if (x > y)
      x %= y;
    else
      y %= x;
  int gcd = x + y;
  return {a.first / gcd, a.second / gcd};
}

int main()
{
  vector<string> antennas;
  for (string str; getline(cin, str);)
    antennas.push_back(str);

  map<char, vector<pair<int, int>>> frequencies;
  set<pair<int, int>> antinodes;

  for (int i = 0; i < ssize(antennas); ++i)
    for (int j = 0; j < ssize(antennas); ++j)
      if (antennas[i][j] != '.')
        frequencies[antennas[i][j]].push_back(make_pair(j, i));

  for (auto const &[frequency, locations]: frequencies)
    for (int i = 0; i < ssize(locations); ++i)
      for (int j = 0; j < ssize(locations); ++j)
        if (i != j)
        {
          auto antinode = locations[i] + locations[i] - locations[j];
          if (antinode.first >= 0 && antinode.second >= 0 &&
              antinode.first < ssize(antennas[0]) &&
              antinode.second < ssize(antennas))
            antinodes.insert(antinode);
        }
  cout << antinodes.size() << endl;

  antinodes.clear();
  for (auto const &[frequency, locations]: frequencies)
    for (int i = 0; i < ssize(locations); ++i)
      for (int j = i + 1; j < ssize(locations); ++j)
      {
        auto vec = normalize(locations[i] - locations[j]);
        for (auto antinode = locations[i] - vec;
            antinode.first >= 0 && antinode.second >= 0 &&
            antinode.first < ssize(antennas[0]) &&
            antinode.second < ssize(antennas);
            antinode = antinode - vec)
          antinodes.insert(antinode);
        for (auto antinode = locations[i];
            antinode.first >= 0 && antinode.second >= 0 &&
            antinode.first < ssize(antennas[0]) &&
            antinode.second < ssize(antennas);
            antinode = antinode + vec)
          antinodes.insert(antinode);
      }
  cout << antinodes.size() << endl;

  return 0;
}
