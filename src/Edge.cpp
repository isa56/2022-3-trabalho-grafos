#include <iostream>
#include "include/Edge.h"


using namespace std;
// Construtor
Edge::Edge(int _id)
{
     this->id = _id;
     this->edgeWeight = 0;
     this->nextEdge = nullptr;
}
Edge::Edge(int id, float weight)
{
     this->id = id;
     this->edgeWeight = weight;
     this->nextEdge = nullptr;
}
// Pega o Id da aresta
int Edge::getId()
{
     return this->id;
}
// Pega o peso da aresta
float Edge::getEdgeWeight()
{
     return this->edgeWeight;
}
// Pega a proxima aresta
Edge *Edge::getNextEdge()
{
     return this->nextEdge;
}
int Edge::getOriginId()
{
     return this->originId;
}
int Edge::getDestinyId()
{
     return this->destinyId;
}
// Seta o peso na aresta
void Edge::setEdgeWeight(int _edgeWeight)
{
     this->edgeWeight = _edgeWeight;
}
void Edge::setOrigin(int origin)
{
     this->originId = origin;
}
void Edge::setDestiny(int destiny)
{
     this->destinyId = destiny;
}
// Seta  a proxima aresta
void Edge::setNextEdge(Edge *_nextEdge)
{
     this->nextEdge = _nextEdge;
}
