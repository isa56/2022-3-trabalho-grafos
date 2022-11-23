#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "Node.h"
#include <fstream>
#include <vector>
#include <stack>
#include <list>
#include <chrono>
#include <time.h>
#include <ctime>

using namespace std;

class Graph
{
     // Atributes
private:
     int order;
     int edgesNumber;
     int position; // posição de inserção do node
     bool directed;
     bool edgeHasWeight;
     bool nodeHasWeight;

     Node *firstNode;
     Node *lastNode;

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
     Node *getNodePosition(int position); // Pega um node apartir de sua posição de inserção

     // Other methods
     void insertNode(int id);
     void insertEdge(int id, int target_id, float weight);
     void removeNode(int id);
     bool searchNode(int id);

     void printList();

     void graphIntersection(Graph *G1, Graph *G2);
     void graphUnion(Graph *G1, Graph *G2);
};

#endif // __GRAPH_H__