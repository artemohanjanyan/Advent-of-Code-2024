Command to generate graph.png using Graphviz:
```
./a.out dot < input | dot -Tpng -Kneato -Nshape=point -Epenwidth=0.2 -o graph.png
```

Or pass `dot_part_2` instead of `dot` to highlight part 2 answer on the graph.
