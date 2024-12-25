#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <ranges>
#include <format>

using namespace std;

struct operation
{
  string op1, op, op2, res;

  auto operator<=>(operation const&) const = default;

  bool evaluate(bool op1, bool op2) const
  {
    if (op == "AND")
      return op1 && op2;
    if (op == "OR")
      return op1 || op2;
    if (op == "XOR")
      return op1 ^ op2;
    cerr << "unknown operator " << op << endl;
    return false;
  }
};

int main()
{
  map<string, bool> values;
  for (string str; getline(cin, str), !str.empty(); )
    values[str.substr(0, 3)] = str[5] == '1';

  vector<operation> operations;
  map<string, vector<int>> inputs;
  set<string> z_wires;
  for (string op1, op, op2, res, tmp; cin >> op1 >> op >> op2 >> tmp >> res; )
  {
    operations.push_back(operation{op1, op, op2, res});
    if (op1[0] == 'z') z_wires.insert(op1);
    if (op2[0] == 'z') z_wires.insert(op2);
    if (res[0] == 'z') z_wires.insert(res);
    inputs[op1].push_back(operations.size() - 1);
    inputs[op2].push_back(operations.size() - 1);
  }

  set<string> unset_z_wires = z_wires;
  queue<string> wire_queue;
  for (auto const &[wire, value] : values)
    wire_queue.push(wire);
  while (!unset_z_wires.empty() && !wire_queue.empty())
  {
    string current_wire = wire_queue.front();
    wire_queue.pop();

    for (int op_i : inputs[current_wire])
    {
      operation const &op = operations[op_i];
      if (values.contains(op.op1) && values.contains(op.op2) && !values.contains(op.res))
      {
        values[op.res] = op.evaluate(values[op.op1], values[op.op2]);
        wire_queue.push(op.res);
        if (op.res[0] == 'z')
          unset_z_wires.erase(op.res);
      }
    }
  }

  uint64_t ans = 0;
  for (string const &z_wire : z_wires | views::reverse)
    ans = (ans << 1) | values[z_wire];
  cout << ans << endl;

  return 0;
}
