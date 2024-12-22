#include <iostream>
#include <vector>

using namespace std;

uint32_t next_secret_number(uint32_t n)
{
  n = ((n << 6) ^ n) & 16777215; 
  n = ((n >> 5) ^ n) & 16777215; 
  n = ((n << 11) ^ n) & 16777215; 
  return n;
}

int start_c(int prev_c)
{
  return -9 - min(prev_c, 0);
}

int end_c(int prev_c)
{
  return 9 - max(prev_c, 0);
}

int main()
{
  vector<uint32_t> initial_numbers;
  for (uint32_t n; cin >> n; )
    initial_numbers.push_back(n);

  uint64_t ans = 0;
  for (uint32_t n : initial_numbers)
  {
    for (int i = 0; i < 2000; ++i)
      n = next_secret_number(n);
    ans += n;
  }
  cout << ans << endl;

  ans = 0;
  for (int c1 = -9; c1 <= 9; ++c1)
  {
    cout << "processing c1 = " << c1 << "..." << endl;
    for (int c2 = start_c(c1); c2 <= end_c(c1); ++c2)
      for (int c3 = start_c(c2); c3 <= end_c(c2); ++c3)
        for (int c4 = start_c(c3); c4 <= end_c(c3); ++c4)
        {
          uint64_t current_ans = 0;
          for (uint32_t n1 : initial_numbers)
          {
            uint32_t n2 = next_secret_number(n1);
            uint32_t n3 = next_secret_number(n2);
            uint32_t n4 = next_secret_number(n3);
            for (int i = 3; i < 2000; ++i)
            {
              uint32_t n5 = next_secret_number(n4);
              if ((n2 % 10 - n1 % 10) == c1 &&
                  (n3 % 10 - n2 % 10) == c2 &&
                  (n4 % 10 - n3 % 10) == c3 &&
                  (n5 % 10 - n4 % 10) == c4)
              {
                current_ans += (n5 % 10);
                break;
              }
              n1 = n2;
              n2 = n3;
              n3 = n4;
              n4 = n5;
            }
          }
          ans = max(ans, current_ans);
        }
  }
  cout << ans << endl;

  return 0;
}
