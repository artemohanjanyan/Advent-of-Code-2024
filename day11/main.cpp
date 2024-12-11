#include <iostream>
#include <map>

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

void step(map<uint64_t, uint64_t> &numbers)
{
  map<uint64_t, uint64_t> new_numbers;
  for (auto const &[n, n_count] : numbers)
    if (n == 0)
      new_numbers[1] += n_count;
    else
    {
      int number_of_digits = get_number_of_digits(n);
      if (number_of_digits % 2 == 0)
      {
        pair<uint64_t, uint64_t> after_split = split_digit(n, number_of_digits);
        new_numbers[after_split.first] += n_count;
        new_numbers[after_split.second] += n_count;
      }
      else
        new_numbers[n * 2024] += n_count;
    }
  numbers.swap(new_numbers);
}

uint64_t get_ans(map<uint64_t, uint64_t> &numbers)
{
  uint64_t ans = 0;
  for (auto const &[n, n_count] : numbers)
    ans += n_count;
  return ans;
}

int main()
{
  map<uint64_t, uint64_t> numbers;
  uint64_t x;
  while (cin >> x)
    ++numbers[x];

  for (int i = 0; i < 25; ++i)
    step(numbers);
  cout << get_ans(numbers) << endl;

  for (int i = 0; i < 50; ++i)
    step(numbers);
  cout << get_ans(numbers) << endl;

  return 0;
}
