#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> list1;
  vector<int> list2;
  int a, b;
  while (cin >> a >> b)
  {
    list1.push_back(a);
    list2.push_back(b);
  }
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());

  int ans = 0;
  for (size_t i = 0; i < list1.size(); ++i)
    ans += abs(list1[i] - list2[i]);
  cout << ans << endl;

  ans = 0;
  for (int x: list1)
    ans += count(list2.begin(), list2.end(), x) * x;

  cout << ans << endl;

  return 0;
}
