//#include <bits/stdc++.h> 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

# define INF 999

class Graph
{
  int numVertices, numEdges;
  vector < vector<int> > adj_matrix;
  int * distBellmanFord; //keep the distance of all vertices from a source vertex
  vector < vector<int> > distFloydWarshall;    
  bool directed;

  public:
  Graph(int vertices, int dir);
  //~Graph();
  void addEdge(int src, int dest, int weight); 
  void removeEdge(int src, int dest);
  void printGraph();
  void getFloydWarshall();
  void printFloydWarshall();
  void printBellmanFord();
  void getBellmanFord(int src);
    
};
 

// member variable assignment
Graph::Graph(int vertices, int dir)
{
  numVertices = vertices;
  numEdges = 0;
  if (dir == 1){
    directed = true;
  }
  else{
    directed = false;
  }
  
  distBellmanFord = new int[numVertices];
  
  adj_matrix = vector<vector<int>>(vertices, vector<int>(vertices, INF));
  for(int i = 0; i <  numVertices; i++){
        adj_matrix[i][i] = 0;
  }
  distFloydWarshall = vector<vector<int> >(vertices, vector<int>(vertices, INF));
}

/*
// Constructor initializer list
// https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
Graph::Graph(int vertices, int dir): 
    adj_matrix(vertices, vector<int>(vertices, INF)),
    distFloydWarshall(vertices, vector<int>(vertices, INF))
{
  numVertices = vertices;
  numEdges = 0;
  if (dir == 0){
    directed = true;
  }
  else{
    directed = false;
  }
  
  distBellmanFord = new int[numVertices];
  
  for(int i = 0; i <  numVertices; i++){
        adj_matrix[i][i] = 0;
  }
}
*/

void Graph::addEdge(int src, int dest, int weight)
{
    
  return;
}

void Graph::removeEdge(int src, int dest)
{
  
  return;
}


void Graph::getBellmanFord(int src) 
{ 
  int i, j, k;
  // initialize the distBellmanFord array with INF

  // initialize distBellmanFord[src] with 0

  // Adding vertices individually
  // There should be 3 nested loops. 
  // first one for running V-1 times 
  // the other two loops will run V times to cover all edges (every cell in adjacency matrix)
  // then relax if dist[i] + weight(i,j) < dist[j] // weight = adj_matrix[i][j]
        
  
  // check if there is a neg cycle
  // If we get a shorter path, then there is a negative edge cycle.
  // basically copy - paste the previous code except the outer loop
  
  
  printBellmanFord();
 
  return;    
} 

// Recurive Function to print path of given vertex v from source vertex
void Graph::printBellmanFord()
{  
  for (int i = 0; i < numVertices; i++) {
      printf("%4d", distBellmanFord[i]);
    }
  return; 
}

void Graph::getFloydWarshall() 
{ 
  int i, j, k;
  // initialize the distFloydWarshall array with adj_matrix

  // Adding vertices individually
  // There should be 3 nested loops that will run V times 
  // then relax (see slide for the relaxation)

  
  // check if there is a neg value in the diagonal.
  // If yes, just print a message that negative cycle exists

  
  printFloydWarshall();  
  return;    
} 

// Recurive Function to print path of given vertex v from source vertex
void Graph::printFloydWarshall()
{
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      if (distFloydWarshall[i][j] == INF)
        printf("%4s", "INF");
      else
        printf("%4d", distFloydWarshall[i][j]);
    }
    printf("\n");
  }
  return; 
}

void Graph::printGraph() {
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      if (adj_matrix[i][j] == INF)
        printf("%4s", "INF");
      else
        printf("%4d", adj_matrix[i][j]);
    }
    printf("\n");
  }
}

/*
Graph::~Graph()
{
    //write your destructor here
}
*/

int main()
{
    int nVertex, nEdge, direction, choice, i, u, v, w;
    ifstream file; 
 
    file.open("inputbellman.txt",ios::in); 
 
    if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    } 
    cout<<"File opened successfully: "; 
    
    cout<<"Enter number of vertices: "<<endl;
    file>>nVertex;
    cout<<"Enter directed/undirected: "<<endl;
    file>>direction;
    Graph g(nVertex, direction);
    file>>nEdge; 
    for(i = 0; i < nEdge; i++)
    {
        file>>u;
        file>>v;
        file>>w;
        g.addEdge(u, v, w);
    }
    cout<<"Done inserting "<<endl;
    g.printGraph();
    
    while (1)
    {
        cout<<"\n----------------------"<<endl;
        cout<<"Operations on Graph"<<endl;
        cout<<"\n----------------------"<<endl;
        cout<<"1.Add Edge"<<endl;
        cout<<"2.Remove Edge"<<endl;
        cout<<"3.Find Distance: FloydWarshall"<<endl;
        cout<<"4.Find Distance: Bellman Ford"<<endl;
        cout<<"5.Print Graph"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                //add edge
                cout<<"Please enter the source,destination and weight for the edge"<<endl;
                cin>>u >>v >>w;
                g.addEdge(u, v, w);
                break;
            
            case 2:
                //remove edge
                cout<<"Please enter the source and destination of the edge"<<endl;
                cin>>u >>v;
                g.removeEdge(u, v);
                break;
            
            case 3:
                //Get Distance of other nodes uisng Floyd-Warshall
                g.getFloydWarshall();
                break;
            
            case 4:
                //Get Distance of other nodes uisng Bellman Ford
                cout<<"Please enter the source vertex"<<endl;
                cin>>u;
                g.getBellmanFord(u);
                break;
            
            case 5:
                //Print Graph
                g.printGraph();
                break;

            case 6:
                //Print Graph
                exit(1);
                break;
          
            default:
               cout<<"\nEnter correct option\n";
        }
    }
    
    return 0;
}