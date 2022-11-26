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
     int nodeWeight;
     int degree;
     Node *nextNode;

     unsigned int inDegree;
     unsigned int outDegree;

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
     void setNodeWeight(int nodeWeight);
     void setNextNode(Node *nextNode);

     void setFirstEdge(Edge *firstEdge);

     void incrementDegree();
     void decrementDegree();

     void incrementInDegree();
     void decrementInDegree();

     void incrementOutDegree();
     void decrementOutDegree();

     void addEdge(int id, float weightNode);
     Edge *searchEdge(int id);
     void removeEdge(int id, bool directed, Node *node);
     void removeAllEdges();
};

#endif // __NODE_H__