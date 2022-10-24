#include <iostream>
#include "./include/Edge.h"

using namespace std;
// Construtor
Edge::Edge(int _id)
{
     this->id = _id;
     this->weightEdge = 0;
     this->nexEdge = nullptr;
}
// Pega o Id da aresta
int Edge::getId()
{
     return this->id;
}
// Pega o peso da aresta
float Edge::getWeightEdge()
{
     return this->weightEdge;
}
// Pega a proxima aresta
Edge *Edge::getNextEdge()
{
     return this->nexEdge;
}
// Seta o peso na aresta
void Edge::setWeightEdge(int _weightEdge)
{
     this->weightEdge = _weightEdge;
}
// Seta  a proxima aresta
void Edge::setNextEdge(Edge *_nexEdge)
{
     this->nexEdge = _nexEdge;
}
// Destrutor
Edge::~Edge()
{
     // Verifica se não é a ultima aresta
     if (this->nexEdge != nullptr)
     {
          delete this->nexEdge;
          this->nexEdge = nullptr;
     }
}
