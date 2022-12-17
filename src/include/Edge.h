#ifndef __EDGE_H__
#define __EDGE_H__

#include "Node.h"

class Edge
{

private:
     // Artributos
     int id;
     float edgeWeight;
     Edge *nextEdge;
     Node *origin;
     Node *destiny;

public:
     Edge(int id);               // Construtor
     Edge(int id, float weight); // Aresta com peso

     int getId();
     float getEdgeWeight();
     Edge *getNextEdge();

     Node *getOrigin();
     Node *getDestiny();

     void setNextEdge(Edge *nexEdge);
     void setEdgeWeight(int edgeWeight);

     void setOrigin(int origin);
     void setDestiny(int destiny);
};

#endif // __EDGE_H__