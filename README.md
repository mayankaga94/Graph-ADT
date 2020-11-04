# Graph-ADT 
# Data Structures And Algorithms
Implemented Graph ADT and Traversal using Dijkstra's algorithm, priority queue ( Binomial Heap )

• Graph CreateEmptyGraph(). This function creates an empty graph and returns it.

• int InsertEdge(Graph g, Edge *e). This function does the following task. Check if the
edge e is in the graph g. If e is not in g, insert e into g and return 1. Otherwise, return
0.

• void DeleteEdge(Graph g, Edge *e). This function deletes the edge e from the graph g.
If e is not in g, it does nothing. After deleting the edge e, this function also deletes any
isolated end vertex of e. An isolated vertex is a vertex without any edge between this
vertex and any other vertex.

• void ReachableVertices(Graph g, Vertex *v). This function finds all the vertices
reachable from the vertex v in g and prints them in any order on the screen. A vertex
u is reachable from a vertex v if there is a path from v to u. In the output, each vertex
is displayed as a pair (x’, y’), where x’ and y’ are its x-coordinate and y-coordinate, and
two adjacent vertices are separated by a comma (,). If no vertex is reachable from v,
nothing will be printed. If v is not a vertex of g, this function does nothing.

• void ShortestPath(Graph g, Vertex *u, Vertex *v). This function finds the shortest path
between the vertex u and the vertex v, and print all the vertices of the shortest path
in their order on the shortest path from the vertex u to the vertex v in the form of (x1,
y1), …, (x2, y2), where the first and second element of each pair are the x-coordinate
and y-coordinate of the corresponding vertex. If either u or v is not a vertex of g, this
function does nothing.

• void FreeGraph(Graph g). This function frees the heap space occupied by the graph g.

• void ShowGraph(Graph g). This function prints each edge of g once in breadth-first
order. Your breadth-first search algorithm can pick any vertex as the first vertex to be
visited in the breadth-first search. In the output, each vertex is displayed as a pair (x’,
y’), where x’ and y’ are its x-coordinate and y-coordinate, and each edge (x1,y1)-(x2,y2)
is displayed as (x1,y1),(x2,y2), and two adjacent edges are separated by a white space. 
