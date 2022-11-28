#include <iostream>
#include "./include/Edge.h"

using namespace std;
// Construtor
Edge::Edge(int _id)
{
     this->id = _id;
     this->edgeWeight = 0;
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
// Seta o peso na aresta
void Edge::setEdgeWeight(int _edgeWeight)
{
     this->edgeWeight = _edgeWeight;
}
// Seta  a proxima aresta
void Edge::setNextEdge(Edge *_nextEdge)
{
     this->nextEdge = _nextEdge;
}
