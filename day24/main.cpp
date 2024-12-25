#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <ranges>
#include <format>
#include <random>
#include <bitset>

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

struct device
{
  vector<operation> operations;
  set<string> z_wires;

  pair<uint64_t, map<string, bool>> evaluate(map<string, bool> values, uint64_t x, uint64_t y) const
  {
    for (int i = 0; i < 64; ++i)
    {
      string operand = format("x{:02d}", i);
      if (!values.contains(operand))
        values[operand] = x & 1;
      x >>= 1;
    }
    for (int i = 0; i < 64; ++i)
    {
      string operand = format("y{:02d}", i);
      if (!values.contains(operand))
        values[operand] = y & 1;
      y >>= 1;
    }

    map<string, vector<int>> inputs;
    for (size_t i = 0; i < operations.size(); ++i)
    {
      inputs[operations[i].op1].push_back(i);
      inputs[operations[i].op2].push_back(i);
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
    return {ans, values};
  }

  void dot()
  {
    cout << "digraph G {\n";
    //for (auto const &z_wire : z_wires)
    //{
    //  cout << "  x" << z_wire.substr(1) << " [pos=\"0," << stoi(z_wire.substr(1)) * 2 << "!\"];\n";
    //  cout << "  y" << z_wire.substr(1) << " [pos=\"5," << stoi(z_wire.substr(1)) * 2 << "!\"];\n";
    //  cout << "  " << z_wire << " [pos=\"10," << stoi(z_wire.substr(1)) * 2 << "!\"];\n";
    //}
    for (auto const &op : operations)
    {
      string op_node = op.op1 + op.op[0] + op.op2 + "_" + op.res;
      cout << "  " << op.op1 << " -> " << op_node << ";\n";
      cout << "  " << op.op2 << " -> " << op_node << ";\n";
      cout << "  " << op_node << " -> " << op.res << ";\n";
    }
    cout << "}" << endl;
  }
};

int main(int argc, char **argv)
{
  map<string, bool> values;
  for (string str; getline(cin, str), !str.empty(); )
    values[str.substr(0, 3)] = str[5] == '1';

  device d;
  for (string op1, op, op2, res, tmp; cin >> op1 >> op >> op2 >> tmp >> res; )
  {
    d.operations.push_back(operation{op1, op, op2, res});
    if (op1[0] == 'z') d.z_wires.insert(op1);
    if (op2[0] == 'z') d.z_wires.insert(op2);
    if (res[0] == 'z') d.z_wires.insert(res);
  }

  bool should_print_dot = argc == 2 && string(argv[1]) == "dot";

  if (should_print_dot)
  {
    d.dot();
    return 0;
  }

  cout << d.evaluate(values, 0, 0).first << endl;

  mt19937_64 rng(0);
  set<int> bad_bits;
  for (int i = 0; i < 100; ++i)
  {
    uint64_t x = rng() & 35184372088831;
    uint64_t y = rng() & 35184372088831;
    auto ans_bits = bitset<45>(d.evaluate({}, x, y).first);
    auto correct_bits = bitset<45>(x + y);
    for (int j = 0; j < 45; ++j)
      if (ans_bits[j] != correct_bits[j])
        bad_bits.insert(j);
  }
  cout << "bad bits: ";
  for (auto bit : bad_bits)
    cout << bit << " ";
  cout << endl;

  return 0;
}
