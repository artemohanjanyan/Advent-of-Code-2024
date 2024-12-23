#include <iostream>
#include <string>
#include <map>
#include <set>
#include <bitset>
#include <algorithm>

using namespace std;

int popcount(int n)
{
  return bitset<32>(n).count();
}

int main(int argc, char **argv)
{
  map<string, set<string>> graph;
  char q1, q2, q3, q4, q5;
  while (cin >> q1 >> q2 >> q3 >> q4 >> q5)
  {
    string n1 = string("") + q1 + q2;
    string n2 = string("") + q4 + q5;
    graph[n1].insert(n2);
    graph[n2].insert(n1);
  }

  bool should_print_raw_graph = argc == 2 && string(argv[1]) == "dot";
  bool should_print_part_2_graph = argc == 2 && string(argv[1]) == "dot_part_2";

  if (should_print_raw_graph)
  {
    cout << "graph G {\n";
    for (auto const &[n1, e1] : graph)
      for (auto const &n2 : e1)
        if (n1 < n2)
          cout << "  " << n1 << " -- " << n2 << ";\n";
    cout << "}\n";
    return 0;
  }

  int ans = 0;
  for (auto const &[n1, e1] : graph)
    for (auto const &n2 : e1)
      for (auto const &n3 : graph[n2])
        if (n1 < n2 && n2 < n3 && graph[n3].contains(n1) &&
            (n1[0] == 't' || n2[0] == 't' || n3[0] == 't'))
          ++ans;
  if (!should_print_part_2_graph)
    cout << ans << endl;

  vector<string> ans2;
  int ans_size = 0;
  for (auto const &[n1, e1] : graph)
  {
    int max_bitmask = 1 << e1.size();
    for (int mask = 0; mask < max_bitmask; ++mask)
    {
      bool fl = true;
      if (popcount(mask) + 1 <= ans_size)
        continue;
      vector<string> edge_vector(e1.begin(), e1.end());
      for (uint32_t i = 0; i < e1.size() && fl; ++i)
        for (uint32_t j = i + 1; j < e1.size() && fl; ++j)
          if (((mask >> i) & 1) && ((mask >> j) & 1))
            fl &= graph[edge_vector[i]].contains(edge_vector[j]);
      if (fl)
      {
        ans_size = popcount(mask) + 1;
        ans2.clear();
        ans2.push_back(n1);
        for (uint32_t i = 0; i < e1.size(); ++i)
          if ((mask >> i) & 1)
            ans2.push_back(edge_vector[i]);
      }
    }
  }
  sort(ans2.begin(), ans2.end());
  if (!should_print_part_2_graph)
  {
    cout << ans2[0];
    for (size_t i = 1; i < ans2.size(); ++i)
      cout << "," << ans2[i];
    cout << endl;
  }
  else
  {
    cout << "graph G {\n";
    for (string const &n : ans2)
      cout << "  " << n << " [color=\"red\"];\n";
    for (auto const &[n1, e1] : graph)
      for (auto const &n2 : e1)
        if (n1 < n2)
          cout << "  " << n1 << " -- " << n2 << ";\n";
    cout << "}\n";
  }

  return 0;
}
