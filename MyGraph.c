#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define SIZE 100
// Notes

// Vertex implemented as adjacency list
// Make an linked list which stores all vertices
// Each vertex is a part of linked list storing its adjacent vertices(edges)
// Each Vertex will also be part of a priority queue
	// We will then need to implement all operations like insert,
	// delete, change values(order changes then) etc for the queue.
// Djikistra's algorithm
	// Every vertex is visited or not visited

// A vertex is a 2D point
typedef struct Vertex { 
	int x; // x-coordinate
	int y; // y-coordinate
} Vertex;
// each edge is a pair of vertices (end-points)
typedef struct Edge {
	Vertex *p1; // first end point
	Vertex *p2; // second end point
} Edge;

typedef struct VertexNode {
	Vertex *v;
	int visited;
	struct AdjacentNode *edges; // Head of edges(AdjacentNode) linked list
	struct VertexNode *next; // Next Vertex in graph
	struct VertexNode *prev;
 	// we could add an array containing pointers of its presence in other vertices lists
	// above is not required as that will be its own adjacency list.
} VertexNode;

typedef struct AdjacentNode {
	VertexNode *origin; // Points to the Vertex
	struct AdjacentNode *next;
} AdjacentNode;

typedef struct GraphRep *Graph;
typedef struct GraphRep { // graph header
	VertexNode *vertices; // an array of vertices or a linked list of vertices  (going with LL)
	int nV; // #vertices
	int nE; // #edges
} GraphRep;

// Queue structure
typedef struct Queue {
	VertexNode *items[SIZE];
	int front;
	int rear;
} Queue;

Queue *CreateQueue(){
	Queue *q = malloc(sizeof(Queue));
	q->front = -1;
	q->rear = -1;
	return q;
}

int isEmpty(Queue *q){
	if(q->rear == -1) return 1;
	else return 0;
}

void Enqueue(Queue *q,VertexNode *v){
	if(q->rear == SIZE-1) printf("Queue Full");
	else {
		if(q->front == -1) q->front = 0; // Queue is empty
		q->rear++;
		q->items[q->rear] = v;
	}
}

VertexNode *Dequeue(Queue *q){
	VertexNode *v;
	if(isEmpty(q) == 1){
		printf("Empty queue");
		return NULL;
	} else {
		v = q->items[q->front];
		q->front++;
		if(q->front > q->rear) q->front = q->rear = -1; //Queue is Empty, reset
	}
	return v;
}

void BFS(Graph g,VertexNode *v){
	Queue *q = CreateQueue();
	v->visited = 1; // Set vertex as visited
	Enqueue(q,v); // Insert in queue
	while(!isEmpty(q)){
		VertexNode *currentV = Dequeue(q);
		printf("( %d , %d )",currentV->v->x,currentV->v->y);
		AdjacentNode *edgeV = currentV->edges;
		while(edgeV != NULL){
			if(edgeV->origin->visited == 0){ // If vertex is not visited
				edgeV->origin->visited = 1; // Mark as visited
				Enqueue(q,edgeV->origin);
			}
			edgeV = edgeV->next;
		}
	}
	free(q);
}
// A vertex node stores a vertex and other information, and you need to expand this type

//The above types serve as a starting point only. You need to expand them and add more types. 
// Watch the lecture video between 7:50pm-8:20 or so for my discussion about this assignment    

// Add the time complexity analysis of CreateEmptyGraph() here

void PrintVertex(VertexNode *V){ // Ignore this function
	printf("Vertex %d %d -> ",V->v->x,V->v->y);
}
void PrintVertexNode(Vertex *v){ // Ignore this function
	printf("V: %d %d\n",v->x,v->y);
}
int EquateVertices(Vertex *v1,Vertex *v2){ // Need to use this in other funtions
	if(v1->x == v2->x && v1->y == v2->y) {
		return 1;
	}
	else return 0;
}
Graph CreateEmptyGraph()
{
	Graph g = (GraphRep*)malloc(sizeof(GraphRep));
	assert(g!=NULL);
	g->nE = 0;
	g->nV = 0;
	g->vertices = NULL;
	return g;
}

void ResetGraph(Graph g){
	VertexNode *v;
	v = g->vertices;
	while(v != NULL){
		v->visited = 0;
		v = v->next;
	}
}

VertexNode *CreateVertexNode(Graph g, Vertex *p){ // Creates a new vertex node in the graph(Inserts in the graph too)
	VertexNode *V;
	V = (VertexNode*)malloc(sizeof(VertexNode));
	V->v = p;
	V->next = NULL;
	V->prev = NULL;
	V->edges = NULL;
	V->visited = 0;
	g->nV++;
	if(g->vertices == NULL){ // Graph is empty
		g->vertices = V;
	} else { // If graph not empty
		// Insert the vertex at start and point current head as next
		V->next = g->vertices;
		g->vertices->prev = V;
		g->vertices = V;
	}
	return V;
}

VertexNode *FindVertex(Graph g,Vertex *v){
	VertexNode *V;
	V = g->vertices;
	while(V!=NULL){
		if(EquateVertices(V->v,v) == 1) break;
		else V = V->next;
	}
	return V;
}

typedef struct HeapNode { 
	// each node stores the priority (key), name, execution time,
	// release time and deadline of one task
	int key; //key of this task
	int TaskName;  //task name 
	int Etime; //execution time of this task
	int Rtime; // release time of this task
	int Dline; // deadline of this task
	// add additional fields here
	int degree;
	struct HeapNode *child;
	struct HeapNode *sibling;
	struct HeapNode *parent;
	// degree
	// child
	// sibling
} HeapNode;

//data type for a priority queue (heap) 
typedef struct BinomialHeap{ //this is heap header
	int  size;      // count of items in the heap
	HeapNode *head;
	// add pointer to root of one of the binomial trees in the binomial heap
	//... // add additional fields here
} BinomialHeap;

typedef struct HeapRootList{
	HeapNode node;
} HeapRootList;


int Min(BinomialHeap *T)
{
  // put your code here
  int min = 999;
  //min = T->head->key;
  HeapNode *head = T->head;
  while(head){
	if(head->key<=min){
		min = head->key;
	}
	head = head->sibling;
  }
  return min;
}

// Inserts edge in a vertex's adjacency list
void InsertAdjacentNode(VertexNode *V,VertexNode *S){ 
	AdjacentNode *edge;
	edge = (AdjacentNode*)malloc(sizeof(AdjacentNode));
	edge->origin = S; // Edge is from V -- S
	if( V->edges == NULL){ // If vertex has no edges
		V->edges = edge;
		edge->next = NULL;
	} else {
		edge->next = V->edges; // Insert at start
		V->edges = edge;
	}
}
// Add the time complexity analysis of InsertEdge() here
// Check if edge exist.If yes return 0 else insert edge and update queue with 
// the two vertices.
// O(m)
int InsertEdge(Graph g, Edge *e)
{
	VertexNode *v = g->vertices,*v1 = NULL,*v2 = NULL;
	AdjacentNode *edge_incr;
	if (v == NULL){ // If graph is empty
		v1 = CreateVertexNode(g,e->p1);
		v2 = CreateVertexNode(g,e->p2);
		InsertAdjacentNode(v1,v2); //Insert v2 in v1 adjacent list
		InsertAdjacentNode(v2,v1); //Insert v1 in v2 adjacent list
	} else { // If graph is not empty
		// Loop through the graph 
		// Assign if vertex to v1,v2 if found else NULL
		while(v != NULL){
			// Check if both or either vertexnode is present in the graph
			if( v->v->x == e->p1->x && v->v->y == e->p1->y) {
				v1 = v;
			}
			if( v->v->x == e->p2->x && v->v->y == e->p2->y) {			
				v2 = v;
			}
			v = v->next;
		}
		// If v1 not found then insert it into the graph
		if(v1 == NULL){ // v1 is not present in the graph
			v1 = CreateVertexNode(g,e->p1);
		}
		// If v2 not found then insert it into the graph
		if(v2 == NULL){
			v2 = CreateVertexNode(g,e->p2);
		}
		// Now both v1 and v2 contain a vertexnode
		edge_incr = v1->edges;
		// If v1 contains the edge then return 0
		// No need to check in v2 as insert always happen on both
		while(edge_incr != NULL){
			if(edge_incr->origin->v == v2->v) {
				return 0;// The edge is already present(no insertion)
			}
			edge_incr = edge_incr->next;
		}
		// Edge is not present
		// Insert the edge
		InsertAdjacentNode(v1,v2);
		InsertAdjacentNode(v2,v1);
	}
	g->nE++;
	return 1;
}

// DeleteVertexNode() will only be called when a vertex has no edges(or 1 edge that has to be deleted)
// making it isolated.
void DeleteVertexNode(Graph g,VertexNode *v){
	if(g->nV == 1){ // Only 1 vertex in the graph(No need to check for an empty graph)
		g->vertices = NULL;
		free(v);
	} else if(EquateVertices(g->vertices->v,v->v) == 1){ // If vertex in head of graph of multiple vertices
		g->vertices = v->next;
		v->next->prev = NULL;
		free(v);
	} else { // If more than 1 vertex and vertex to delete not in head
		// delink the vertexnode from graph
		v->prev->next = v->next;
		if(v->next!=NULL) v->next->prev = v->prev; // Not the last vertex in graph list
		free(v);
	}
	g->nV--;
}
// Add the time complexity analysis of DeleteEdge() here
// After deletion if a vertex is left with no connections, then we need
// to remove it.
// O(m)

void DeleteEdge(Graph g, Edge *e)
{
	// Delete e->p1 from e->p2's vertexnode and vice versa 
	VertexNode *V,*v1,*v2;
	V = g->vertices;
	while(V != NULL){
		// Assign v1 and v2 to the vertices involved in e
		if(V->v->x == e->p1->x && V->v->y == e->p1->y){
			v1 = V;
		}
		if(V->v->x == e->p2->x && V->v->y == e->p2->y){
			v2 = V;
		}
		V = V->next;
	}

	AdjacentNode *edge_incr,*prev;
	// We assume that edge is present ie v1 and v2 are not NULL
	edge_incr = v1->edges;
	// If first element is the edge (ie only possible way a vertex will have 0 edges)
	if(edge_incr->origin->v->x == e->p2->x && edge_incr->origin->v->y == e->p2->y){ 
		if(edge_incr->next == NULL){ //Only one edge then delete the vertex itself
			DeleteVertexNode(g,v1);
			free(edge_incr);
		} else { // Edge to be deleted is the first of multiple edges
			v1->edges = edge_incr->next;
			free(edge_incr);
		}
	}
	else { // Vertex will have more than one edge despite deletion and edge is not in the front
		prev = edge_incr;
		edge_incr = edge_incr->next;
		while(edge_incr != NULL){ 
			// Using e in if statements instead of v1,v2 as there is a chance that have to be deleted
			if(edge_incr->origin->v->x == e->p2->x && edge_incr->origin->v->y == e->p2->y){
				prev->next = edge_incr->next; // Delete edge in v1
				free(edge_incr); // free the adjacentnode
				break;
			}
			prev = edge_incr;
			edge_incr = edge_incr->next;
		}
	}
	edge_incr = v2->edges;
	// Same as above(make it as a function?)
	if(edge_incr->origin->v->x == e->p1->x && edge_incr->origin->v->y == e->p1->y){ 
		if(edge_incr->next == NULL){
			DeleteVertexNode(g,v2);
			free(edge_incr);
		} else {
			v2->edges = edge_incr->next;
			free(edge_incr);
		}
	} else {
		prev = edge_incr;
		edge_incr = edge_incr->next;
		while(edge_incr != NULL){
			if(edge_incr->origin->v->x == e->p1->x && edge_incr->origin->v->y == e->p1->y){
				prev->next = edge_incr->next;
				free(edge_incr);
				break;
			}
			prev = edge_incr;
			edge_incr = edge_incr->next;
		}
	}
	
	g->nE--;
}

// Add the time complexity analysis of ReachableVertices() here
// O(m+n)
void ReachableVertices(Graph g, Vertex *v)
{	
	VertexNode *V;
	V = FindVertex(g,v);	
	BFS(g,V);
	printf("\n");
	ResetGraph(g);
}

// Add the time complexity analysis of ShortestPath() here
void ShortestPath(Graph g, Vertex *u, Vertex *v)
{
	
}

// Add the time complexity analysis of FreeGraph() here
// O(n)
void FreeGraph(Graph g)
{
	VertexNode *v_free,*v;
	v = g->vertices;
	while(v != NULL){
		v_free = v;
		v = v->next;
		free(v_free);
	}
	free(g);
}

void PrintGraph(Graph g){ // Ignore this function
	VertexNode *v;
	v = g->vertices;
	AdjacentNode *edge;
	while(v != NULL){
		edge = v->edges;
		PrintVertex(v);
		printf(" %d ",v->visited);
		while(edge != NULL){
			PrintVertex(edge->origin);
			edge = edge->next;
		}
		v = v->next;
		printf("\n");
	}
}

// Add the time complexity analysis of ShowGraph() here
// O(m+n)
void ShowGraph(Graph g)
{	
	VertexNode *v;
	v = g->vertices;
	while(v != NULL){
		if(v->visited == 0){
			BFS(g,v);
		}
		v = v->next;
	}
	ResetGraph(g);
	printf("\n");
}

int main() //sample main for testing 
{ 
 Graph g1;
 Edge *e_ptr; 
 Vertex *v1, *v2;
  
 // Create an empty graph g1;
 g1=CreateEmptyGraph();
  
 // Create first connected component 
 // Insert edge (0,0)-(0,10)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=0;
 v2->y=10;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (0,0)-(5,6)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=5;
 v2->y=6;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (0, 10)-(10, 10)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=10;
 v2->x=10;
 v2->y=10;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (0,10)-(5,6)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=10;
 v2->x=5;
 v2->y=6;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (0,0)-(5,4)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=5;
 v2->y=4;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (5, 4)-(10, 4)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=5;
 v1->y=4;
 v2->x=10;
 v2->y=4;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (5,6)-(10,6)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=5;
 v1->y=6;
 v2->x=10;
 v2->y=6;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (10,10)-(10,6)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=10;
 v1->y=10;
 v2->x=10;
 v2->y=6;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (10, 6)-(10, 4)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=10;
 v1->y=6;
 v2->x=10;
 v2->y=4;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Create second connected component
 // Insert edge (20,4)-(20,10)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=20;
 v1->y=4;
 v2->x=20;
 v2->y=10;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (20,10)-(30,10)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=20;
 v1->y=10;
 v2->x=30;
 v2->y=10;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n");
 
 // Insert edge (25,5)-(30,10) 	
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=25;
 v1->y=5;
 v2->x=30;
 v2->y=10;
 e_ptr->p1=v1;
 e_ptr->p2=v2;
 if (InsertEdge(g1, e_ptr)==0) printf("edge exists\n"); 
 
 //Display graph g1
 ShowGraph(g1);
	
 // Find the shortest path between (0,0) and (10,6) 
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=10;
 v2->y=6;
 ShortestPath(g1, v1, v2);
 free(v1);
 free(v2);
	  
 // Delete edge (0,0)-(5, 6)
 e_ptr = (Edge*) malloc(sizeof(Edge));
 assert(e_ptr != NULL);
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=5;
 v2->y=6;
 e_ptr->p1=v1;
 e_ptr->p2=v2; 	 
 DeleteEdge(g1, e_ptr);
 free(e_ptr);
 free(v1);
 free(v2);
 	 
 // Display graph g1
 ShowGraph(g1);
	
 // Find the shortest path between (0,0) and (10,6) 
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=10;
 v2->y=6; 
 ShortestPath(g1, v1, v2);
 free(v1);
 free(v2);
 
 // Find the shortest path between (0,0) and (25,5)
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v2=(Vertex *) malloc(sizeof(Vertex));
 assert(v2 != NULL);
 v1->x=0;
 v1->y=0;
 v2->x=25;
 v2->y=5;
 ShortestPath(g1, v1, v2);
 free(v1);
 free(v2);	
 
 // Find reachable vertices of (0,0)
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v1->x=0;
 v1->y=0;
 ReachableVertices(g1, v1);
 free(v1);
 
 // Find reachable vertices of (20,4)
 v1=(Vertex*) malloc(sizeof(Vertex));
 assert(v1 != NULL);
 v1->x=20;
 v1->y=4;
 ReachableVertices(g1, v1);
 free(v1);
 
 // Free graph g1
 FreeGraph(g1);
 
 return 0; 
}