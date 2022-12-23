#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "Node.h"
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <chrono>
#include <time.h>
#include <ctime>

using namespace std;
typedef struct
{
     string description; // Descrição do Grafo (Grafo interseção de G1 com G2)
     string type;        // Tipo do Grafo (interseção, união ou diferença)
     string G1;
     string G2;

} GraphDOT;
class Graph
{
private:
     int order;
     int edgesNumber;
     int position; // posição de inserção do node
     bool directed;
     bool edgeHasWeight;
     bool nodeHasWeight;

     Node *firstNode;
     Node *lastNode;

     void TopologicalSorting();
     void MaximumPath(int id_start, int id_end);
     bool DFS(int V, vector<bool> &visited);
     int Dijkstra(int origin, int destiny);
     void TopologicalSortUtil(int v, bool visited[], queue<int> &Stack);
     void MaximumPathUtil(int id_start, int id_end, bool visited[], int path[], int &path_index);

public:
     // Constructor & Destructor
     Graph(int order, bool directed, bool edgeWeighted, bool nodeWeighted);
     ~Graph();
     void setOrder(int order);
     // Getters
     int getOrder();
     int getEdgesNumber();
     bool isDirected();
     bool isEdgeWeighted();
     bool isNodeWeighted();
     Node *getFirstNode();
     Node *getLastNode();
     Node *getNode(int id);
     Node *getNodeByPosition(int position); // Pega um node apartir de sua posição de inserção

     void insertNode(int id);
     void insertEdge(int id, int target_id, float weight);
     void removeNode(int id);
     bool searchNode(int id);

     void printList();
     // Criar um arquivo na linguagem “dot” para
     // geração de grafos para no software Graphviz

     void FileDot(ofstream &output_file, GraphDOT GDot);

     void graphIntersection(Graph *G1, Graph *G2);
     void graphUnion(Graph *G1, Graph *G2);
     void graphDifference(Graph *G1, Graph *G2);
     void PERT(); // Rede Pert
};

#endif // __GRAPH_H__