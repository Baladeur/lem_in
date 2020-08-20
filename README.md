# Lem_in

Lem_in is an approach at pathfinding algorithms by simulating an ant farm. Here, our farm is represented by a graph, where the nodes and the edges are defined in a file.

Our goal is to find the shortest way to move a set amount of ants from a starting node to a destination node. There are various constraints we have to deal with.

To determine wether a solution is optimal or not, we count the number of turns it took until every ant made it to the end. 
- Each ant can move once per turn. This means you can move 3 different ants during a single turn, but you need 3 turns to move a single ant 3 times. 
- There can only be one ant per node at a time, besides the starting and ending room which have an unlimited capacity. 
- The ant farm is an undirected and unweighted graph.

Thus, the job of our algorithm is to find the best combination of paths from start to end that are node-disjoint. Once this is done, ants are split accordingly on the different paths, allowing them to move forward at the same time, reducing the total amount of turns required.

Following this combination of paths, ants will travel more than if they had followed the single shortest path, however they will also reach the end of the farm sooner.

We chose a modified version of Suurballe`s node disjoint algorithm to solve this problem.

## Breakdown of our algorithm

### Initial Layout

![Initial layout](https://i.imgur.com/qjepeI3.jpg)

This pretty basic graph should suffice to demonstrate how the algorithm operates. As expected of a lem_in ant farm, it is undirected and unweighted.

A is the starting node while H is the destination.

### Preparatory step

![Preparatory step](https://i.imgur.com/Xi6h6SF.jpg)

Before running the algorithm loop, we must turn the graph into a directed one.

To do so, we start by splitting every node into an input node (i) and an output node (o).

Every connection **towards** a node will be redirected to its input node, and every connection **from** a node will be redirected from its output node.
The following undirected edge B<->C would turn into the following directed edges : Bo->Ci, Co->Bi

In addition to the split of each node, we also add an edge between the input and the output of a same node : Bi->Bo and Ci->Co. These will be the only edges directed **towards** an output node during the splitting process.

Finally, the start node and the end node follow a different set of rules when split. The start node is turned into an output node only, and the end node is turned into an input room only.
This means the following edges A<->X and X<->H will turn into A->X and X->H.

One everything is done, the new graph is prepared for the loop.

### Algorithm loop

The loop itself is quite short, it mostly concist of two steps.

![Step 1](https://i.imgur.com/I5RcS5w.jpg)

At first, we use a basic breadth-first search algorithm to find the current shortest path. Here, it is hihlighted in orange : A->Ei->Eo->Di->Do->H.
We store this path in our memory and proceed to the second step.

![Step 2](https://i.imgur.com/TAMrJnY.jpg)

We now modify the graph by reversing every edge from the previous path. This will allow the following iterations of the loop to find different shortest paths.

![Loop 2](https://i.imgur.com/3DgQIzk.jpg)

The first iteration of the loop is done, this is the current state of the graph. We can now proceed with the second iteration.

![Step 1](https://i.imgur.com/jPxJ4ds.jpg)

Once again, we search for the shortest path from A to H. Here, it is A->Bi->Bo->Ci->Co->Di->Eo->Fi->Fo->Gi->Go->H.
We also store this path, and reverse its edges.

![Step 2](https://i.imgur.com/jxpYjru.jpg)

![Dead end](https://i.imgur.com/wCl83ZH.jpg)

This is now the state of the graph after 2 iterations of the loop. There is no more path between A and H, thus the loop stops.

## Merging

With the loop over and the paths stored, we can now revert the graph to its initial state, merging the input and output nodes into a single node once again.
In the process, we also transform the paths we found to match the original layout of the graph.
Thus, the following paths:

A->Ei->Eo->Di->Do->H.
A->Bi->Bo->Ci->Co->Di->Eo->Fi->Fo->Gi->Go->H.

become :
A->E->D->H
A->B->C->D->E->F->G->H

Then, all there is left to do is overlapping the paths.

![Overlap](https://i.imgur.com/l1bM6py.jpg)

Edges that cross each other are cancelled out, and it leaves a new usable set of paths :

![Result](https://i.imgur.com/8Zwfxsk.jpg)

The ants will follow these paths to reach the end of the ant-farm.
