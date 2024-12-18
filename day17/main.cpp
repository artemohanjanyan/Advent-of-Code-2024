#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct program
{
  uint64_t a = 0, b = 0, c = 0, ip = 0;
  vector<uint64_t> instructions;
  vector<uint64_t> output;

  uint64_t literal_operand()
  {
    return instructions[ip + 1];
  }

  uint64_t combo_operand()
  {
    switch (instructions[ip + 1])
    {
      case 0: case 1: case 2: case 3:
        return instructions[ip + 1];
      case 4:
        return a;
      case 5:
        return b;
      case 6:
        return c;
      default:
        cerr << "incorrect combo operand " << instructions[ip + 1] << endl;
        return 7;
    }
  }

  bool go()
  {
    switch (instructions[ip])
    {
      case 0:
        a = a >> combo_operand();
        ip += 2;
        break;
      case 1:
        b = b ^ literal_operand();
        ip += 2;
        break;
      case 2:
        b = combo_operand() & 7;
        ip += 2;
        break;
      case 3:
        if (a == 0)
          ip += 2;
        else
          ip = literal_operand();
        break;
      case 4:
        b = b ^ c;
        ip += 2;
        break;
      case 5:
        output.push_back(combo_operand() & 7);
        ip += 2;
        break;
      case 6:
        b = a >> combo_operand();
        ip += 2;
        break;
      case 7:
        c = a >> combo_operand();
        ip += 2;
        break;
      default:
        cerr << "incorrect instruction " << instructions[ip] << endl;
        return false;
    }
    return ip < instructions.size();
  }

  /*
   * Figured out by reading the input that A should be 3*number of instructions
   * bits long, and also on each iteration output depends on last 3 bits and
   * also some bits to the left, and that iteration removes 3 least significant
   * bits from A. It means that we need to find answer starting with 3 most
   * significant bits that determine what will be the last number printed by the
   * program.
   *
   * go_2 does that recursively, each iteration finds bits
   * i*3, i*3 + 1 and i*3 + 2 if we count from the most significant one.
   */
  uint64_t go_2(int i = 0, uint64_t ans = 0)
  {
    if (i == ssize(instructions))
      return ans;
    for (uint64_t j = 0; j < 8; ++j) // all posible 3-bit combinations at
                                     // position i
    {
      program p1 = *this; // make a copy of a program from the input
      p1.a = (ans << 3) | j; // replace a
      while (p1.go()); // run until it stops
      // if first output is same as i-th instruction, we can use it
      // we try all such options since the first one may not work further down
      // the road
      if (p1.output[0] == this->instructions[ssize(this->instructions) - i - 1])
      {
        // append 3 bits from j to ans and search further recursively
        uint64_t new_ans = go_2(i + 1, (ans << 3) | j);
        // assume that 0 is not our answer
        if (new_ans != 0)
          return new_ans;
      }
    }
    return 0;
  }
};

int main()
{
  program p;
  string str;
  cin >> str >> str >> p.a
      >> str >> str >> p.b
      >> str >> str >> p.c
      >> str;

  uint64_t tmp_i;
  char tmp_c;
  cin >> tmp_i;
  p.instructions.push_back(tmp_i);
  while (cin >> tmp_c >> tmp_i)
    p.instructions.push_back(tmp_i);

  program p1 = p;
  while (p1.go());
  cout << p1.output[0];
  for (int i = 1; i < ssize(p1.output); ++i)
    cout << "," << p1.output[i];
  cout << endl;

  cout << p.go_2() << endl;

  return 0;
}
