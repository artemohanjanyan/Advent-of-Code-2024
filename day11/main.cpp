#include <iostream>
#include <vector>

using namespace std;

int get_number_of_digits(uint64_t n)
{
  int ans = 0;
  while (n > 0)
  {
    ++ans;
    n /= 10;
  }
  return ans;
}

pair<uint64_t, uint64_t> split_digit(uint64_t n, int number_of_digits)
{
  uint64_t a = 0;
  for (int i = 0; i < number_of_digits / 2; ++i)
  {
    uint64_t b = n % 10;
    for (int j = 0; j < i; ++j)
      b *= 10;
    a += b;
    n /= 10;
  }
  return {n, a};
}

int main()
{
  vector<uint64_t> numbers;
  uint64_t x;
  while (cin >> x)
    numbers.push_back(x);

  for (int i = 0; i < 25; ++i)
  {
    vector<uint64_t> new_numbers;
    for (uint64_t n : numbers)
      if (n == 0)
        new_numbers.push_back(1);
      else
      {
        int number_of_digits = get_number_of_digits(n);
        if (number_of_digits % 2 == 0)
        {
          pair<uint64_t, uint64_t> after_split = split_digit(n, number_of_digits);
          new_numbers.push_back(after_split.first);
          new_numbers.push_back(after_split.second);
        }
        else
          new_numbers.push_back(n * 2024);
      }
    numbers.swap(new_numbers);
  }
  cout << numbers.size() << endl;

  return 0;
}
