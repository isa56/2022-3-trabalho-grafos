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
     int numberEdges;
     int position; // posição de inserção do node
     bool directed;
     bool weightedEdge;
     bool weightedNode;

     Node *firstNode;
     Node *lastNode;

public:
     // Constructor & Destructor
     Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
     ~Graph();

     // Getters
     int getOrder();
     int getNumberEdges();
     bool getDirected();
     bool getWeightedEdge();
     bool getWeightedNode();
     Node *getFirstNode();
     Node *getLastNode();
     Node *getNode(int id);
     Node *getNodePosition(int position); // Pega um node apartir de sua posição de inserção
     Graph *getVertInduz();

     // Other methods
     void insertNode(int id);
     void insertEdge(int id, int target_id, float weight);
     void removeNode(int id);
     bool searchNode(int id);

     void printList();
};

#endif // __GRAPH_H__