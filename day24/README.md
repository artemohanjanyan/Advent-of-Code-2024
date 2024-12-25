Command to generate graph.png using Graphviz:
```
./a.out dot < input | dot -Tpng -Kneato -Nshape=plain -o graph.png
```

For part 2, check out program output to see what bits are incorrect in the
output. Take a look at graph.png in the vicinity of the first incorrect bit and
try to understand what outputs need to be swapped to improve it. Copy input file,
swap wires in the file, test the assumption, repeat if you are incorrect,
proceed if the number of incorrect bits decreased. Repeat 4 times :)

Use this command to get wire names for the answer:
```
diff input input4 | awk '{ print $6 }' | sort | uniq
```
