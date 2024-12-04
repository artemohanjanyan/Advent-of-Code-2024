#include <iostream>
#include <vector>
#include <string>

using namespace std;

char get_char(vector<string> const &words, int i, int j)
{
  if (i >= 0 && j >= 0 && i < ssize(words) && j < ssize(words[0]))
    return words[i][j];
  else
    return '-';
}

int main()
{
  vector<string> words;
  string str;
  while (getline(cin, str))
    words.push_back(str);

  string word = "XMAS";

  int ans = 0;
  for (int i = 0; i < ssize(words); ++i)
    for (int j = 0; j < ssize(words[0]); ++j)
      for (int di = -1; di <= 1; ++di)
        for (int dj = -1; dj <= 1; ++dj)
          if (di != 0 || dj != 0)
          {
            bool is_ok = true;
            for (int word_i = 0; word_i < ssize(word) && is_ok; ++word_i)
              if (word[word_i] != get_char(words, i + di * word_i, j + dj * word_i))
                is_ok = false;
            ans += is_ok;
          }

  ans = 0;
  for (int i = 1; i < ssize(words) - 1; ++i)
    for (int j = 1; j < ssize(words[0]) - 1; ++j)
        if (words[i][j] == 'A')
        {
          int m_count =
            (words[i - 1][j - 1] == 'M') +
            (words[i - 1][j + 1] == 'M') +
            (words[i + 1][j - 1] == 'M') +
            (words[i + 1][j + 1] == 'M');
          int s_count =
            (words[i - 1][j - 1] == 'S') +
            (words[i - 1][j + 1] == 'S') +
            (words[i + 1][j - 1] == 'S') +
            (words[i + 1][j + 1] == 'S');
          ans += m_count == 2 && s_count == 2 && words[i - 1][j - 1] != words[i + 1][j + 1];
        }

  cout << ans << endl;

  return 0;
}
