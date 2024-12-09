#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

uint64_t checksum(vector<int> const &memory)
{
  uint64_t ans = 0;
  for (int i = 0; i < ssize(memory); ++i)
    if (memory[i] != -1)
      ans += static_cast<uint64_t>(i) * memory[i];
  return ans;
}

uint64_t defragment_1(vector<int> memory)
{
  int next_empty = 0;
  while (memory[next_empty] != -1)
    ++next_empty;

  for (int i = ssize(memory) - 1; next_empty < i; --i)
    if (memory[i] != -1)
    {
      swap(memory[i], memory[next_empty]);
      while (memory[next_empty] != -1)
        ++next_empty;
    }

  return checksum(memory);
}

uint64_t defragment_2(vector<int> memory)
{
  for (int i = ssize(memory) - 1; i >= 0; --i)
    if (memory[i] != -1)
    {
      int length = 1;
      while (i > 0 && memory[i] == memory[i - 1])
      {
        --i;
        ++length;
      }

      for (int j = 0; j < i; ++j)
        if (memory[j] == -1)
        {
          int empty_length = 1;
          while (j < i && memory[j + 1] == -1)
          {
            ++j;
            ++empty_length;
          }
          if (empty_length >= length)
          {
            swap_ranges(&memory[i], &memory[i + length], &memory[j - empty_length + 1]);
            break;
          }
        }
    }

  return checksum(memory);
}

int main()
{
  string str;
  getline(cin, str);

  vector<int> memory;
  for (int i = 0; i < ssize(str); ++i)
    if (i % 2 == 0)
      for (int j = 0; j < str[i] - '0'; ++j)
        memory.push_back(i / 2);
    else
      for (int j = 0; j < str[i] - '0'; ++j)
        memory.push_back(-1);

  cout << defragment_1(memory) << endl;
  cout << defragment_2(memory) << endl;
  return 0;
}
