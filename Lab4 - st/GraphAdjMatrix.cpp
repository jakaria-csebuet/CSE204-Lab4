#include<stdio.h>#include<stdlib.h>#define NULL_VALUE -999999#define INFINITY 999999#define WHITE 0#define GRAY 1#define BLACK 2class Queue {    int queueInitSize ;    int queueMaxSize;    int * data;    int length;    int front;    int rear;public:    Queue();    ~Queue();    void enqueue(int item); //insert item in the queue    int dequeue(); //returns the item according to FIFO    bool empty(); //return true if Queue is empty};Queue::Queue() {    queueInitSize = 2 ;    queueMaxSize = queueInitSize;    data = new int[queueMaxSize] ; //allocate initial memory    length = 0 ;    front = 0;    rear = 0;}void Queue::enqueue(int item) {    if (length == queueMaxSize) {        int * tempData ;        //allocate new memory space for tempList        queueMaxSize = 2 * queueMaxSize ;        tempData = new int[queueMaxSize] ;        int i, j;        j = 0;        for( i = rear; i < length ; i++ ) {            tempData[j++] = data[i] ; //copy items from rear        }        for( i = 0; i < rear ; i++ ) {            tempData[j++] = data[i] ; //copy items before rear        }        rear = 0 ;        front = length ;        delete[] data ; //free the memory allocated before        data = tempData ; //make list to point to new memory    }    data[front] = item ; //store new item    front = (front + 1) % queueMaxSize ;    length++ ;}bool Queue::empty() {    if(length == 0) return true ;    else return false ;}int Queue::dequeue() {    if(length == 0) return NULL_VALUE ;    int item = data[rear] ;    rear = (rear + 1) % queueMaxSize ;    length-- ;    return item ;}Queue::~Queue() {    if(data) delete[] data; //deallocate memory    data = 0; //set to NULL}//****************Queue class ends here************************//******************Graph class starts here**************************class Graph {    int nVertices, nEdges ;    bool directed ;    int ** matrix ; //adjacency matrix to store the graph    int *color ;    int *parent ;    int *dist ;    //define other variables required for bfs such as color, parent, and dist    //you must use pointers and dynamic allocationpublic:    Graph(bool dir = false);    ~Graph();    void setnVertices(int n);    void addEdge(int u, int v);    void removeEdge(int u, int v);    bool isEdge(int u, int v);    int getDegree(int u);    void printAdjVertices(int u);    bool hasCommonAdjacent(int u, int v);    int getDist(int u, int v);    void printGraph();    void bfs(int source); //will run bfs in the graph};Graph::Graph(bool dir) {    nVertices = 0 ;    nEdges = 0 ;    matrix = 0 ;    directed = dir ; //set direction of the graph    color = new int[nVertices];    parent = new int[nVertices];    dist = new int[nVertices] ;  //define other variables to be initialized}void Graph::setnVertices(int n) {    this->nVertices = n ;    //allocate space for the matrix    matrix = new int*[nVertices];    for(int i=0; i<nVertices; i++) {        matrix[i] = new int[nVertices];        for(int j=0; j<nVertices; j++)            matrix[i][j] = 0; //initialize the matrix cells to 0    }}void Graph::addEdge(int u, int v) {    //write your code here    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;    matrix[u][v] = 1;    if(!directed) matrix[v][u] = 1;}void Graph::removeEdge(int u, int v) {    //write this function    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;    matrix[u][v] = 0;    if(!directed) matrix[v][u] = 0;}bool Graph::isEdge(int u, int v) {    //returns true if (u,v) is an edge, otherwise should return false    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;    if(matrix[u][v]) return true ;    return false ;}int Graph::getDegree(int u) {    //returns the degree of vertex u    if(u<0 || u>=nVertices ) return NULL_VALUE;    int degree = 0 ;    for(int j = 0 ; j < nVertices ; ++j)        if(isEdge(u,j)) degree++ ;    return degree ;}void Graph::printAdjVertices(int u) {    //prints all adjacent vertices of a vertex u    if(u<0 || u>=nVertices ) return;    for(int j = 0 ; j < nVertices ; ++j)        if(matrix[u][j]) printf("%d ",j) ;    printf("\n") ;}bool Graph::hasCommonAdjacent(int u, int v) {    //returns true if vertices u and v have common adjacent vertices    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;    for(int j = 0 ; j < nVertices ; ++j) {        //if(j == u || j == v) continue ;        if(isEdge(j,u) && isEdge(j,v))return true ;    }    return false ;}void Graph::bfs(int source) {    //write this function    for(int j = 0; j < nVertices ; ++j){        color[j] = WHITE ;        parent[j] = -1 ;        dist[j] = INFINITY ;    }    color[source] = GRAY;    parent[source] = -1 ;    dist[source] = 0 ;    Queue q ;    q.enqueue(source) ;    while (!q.empty()) {        int i = q.dequeue() ;        color[i] = GRAY ;        int j = 0 ;        //ArrayStack<int> edges;        //g.outEdges(i, edges);        for (int k = 0; k < nVertices; k++) {            if(matrix[i][k]) {                if (color[k]==WHITE) {                    color[k] = GRAY ;                    parent[k] = i ;                    dist[k] = dist[i]+1 ;                    q.enqueue(k);                }            }        }        color[i] = BLACK ;    }}int Graph::getDist(int u, int v) {    //returns the shortest path distance from u to v    //must call bfs using u as the source vertex, then use distance array to find the distance     if(u<0 || u>=nVertices || v<0 || v>=nVertices)return INFINITY ;    bfs(u) ;    return dist[v] ;}void Graph::printGraph() {    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);    for(int i=0; i<nVertices; i++) {        printf("%d:", i);        for(int j=0; j<nVertices; j++) {            if(matrix[i][j]==1)                printf(" %d", j);        }        printf("\n");    }}Graph::~Graph() {    //write your destructor here    if(matrix){        for(int i = 0 ; i < nVertices ; ++i)            if(matrix[i]) delete[] matrix[i] ;        delete[] matrix ;//adjacency matrix to store the graph    }    if(color) delete[] color ;    if(parent) delete[] parent ;    if(dist) delete[] dist ;}//**********************Graph class ends here******************************//******main function to test your code*************************int main(void) {    int n;    //Graph g;    Graph g(true);    printf("Enter number of vertices: ");    scanf("%d", &n);    g.setnVertices(n);    while(1) {        printf("1. Add edge. 2. Remove edge 3. Is Edge 4. Get degree.\n");        printf("5. Print Graph  6. Exit. 7. print Adjacent Vertices\n");        printf("8. Has Common Adjacent 9.Get Distance\n") ;        int ch;        scanf("%d",&ch);        if(ch==1) {            int u, v;            scanf("%d%d", &u, &v);            g.addEdge(u, v);        } else if(ch==2) {            int u, v;            scanf("%d%d", &u, &v);            g.removeEdge(u, v);        } else if(ch==3) {            int u, v;            scanf("%d%d", &u, &v);            if(g.isEdge(u,v)) printf("Yes.\n");            else printf("No.\n") ;        } else if(ch==4) {            int u;            scanf("%d", &u);            printf("Degree of %d: %d\n",u,g.getDegree(u)) ;        } else if(ch==5) {            g.printGraph();        } else if(ch==6) {            break;        } else if(ch==7) {            int u;            scanf("%d", &u);            g.printAdjVertices(u) ;        } else if(ch==8) {            int u, v;            scanf("%d%d", &u, &v);            if(g.hasCommonAdjacent(u,v)) printf("Yes.\n");            else printf("No.\n") ;        }        else if(ch==9) {            int u, v;            scanf("%d%d", &u, &v);            printf("Distance: %d\n",g.getDist(u,v));        }    }}