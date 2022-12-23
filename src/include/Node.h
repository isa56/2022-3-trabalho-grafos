#ifndef __NODE_H__
#define __NODE_H__

#include "Edge.h"

using namespace std;
class Node
{
private:
     int id;
     Edge *firstEdge;
     Edge *lastEdge;
     Node *nextNode;
     int nodeWeight;

     unsigned int degree;
     unsigned int inDegree;
     unsigned int outDegree;

     float ratio;
     bool visited;

public:
     Node(int id);
     ~Node();

     int getId();
     Edge *getFirstEdge();
     Edge *getLastEdge();
     Node *getNextNode();

     int getDegree();
     int getInDegree();
     int getOutDegree();
     bool isVisited();
     float getRatio();
     int getNodeWeight();

     void setNodeWeight(int nodeWeight);
     void setNextNode(Node *nextNode);

     void setFirstEdge(Edge *firstEdge);
     void setVisited(bool _visited);
     void setRatio(float _ratio);

     void incrementDegree();
     void decrementDegree();

     void incrementInDegree();
     void decrementInDegree();

     void incrementOutDegree();
     void decrementOutDegree();

     void addEdge(int _destinyId, float weightNode);
     Edge *searchEdge(int id);
     void removeEdge(int id, bool directed, Node *node);
     void removeAllEdges();

};

#endif // __NODE_H__