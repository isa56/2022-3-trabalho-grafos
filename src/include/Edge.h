#ifndef __EDGE_H__
#define __EDGE_H__

class Edge
{

private:
     // Artributos
     int id;
     float edgeWeight;
     Edge *nextEdge;
     int originId;
     int destinyId;

public:
     Edge(int id);               // Construtor
     Edge(int id, float weight); // Aresta com peso

     int getId();
     float getEdgeWeight();
     Edge *getNextEdge();

     int getOriginId();
     int getDestinyId();

     void setNextEdge(Edge *nexEdge);
     void setEdgeWeight(int edgeWeight);

     void setOrigin(int origin);
     void setDestiny(int destiny);
};

#endif // __EDGE_H__