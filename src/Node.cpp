#include <iostream>
#include "./include/Node.h"

using namespace std;
// Construtor
Node::Node(int _id)
{
     this->lastEdge = nullptr;
     this->firstEdge = nullptr;
     this->nextNode = nullptr;
     this->nodeWeight = 0;
     this->inDegree = 0;
     this->outDegree = 0;
     this->id = _id;
     this->ratio = 0;
     this->visited = false;
}

// Gets

int Node::getId()
{
     return this->id;
}

Edge *Node::getLastEdge()
{
     return this->lastEdge;
}

Edge *Node::getFirstEdge()
{
     return this->firstEdge;
}
int Node::getDegree()
{
     return this->degree;
}
int Node::getInDegree()
{
     return this->inDegree;
}

int Node::getOutDegree()
{
     return this->outDegree;
}

Node *Node::getNextNode()
{
     return this->nextNode;
}
float Node::getNodeWeight()
{
     return this->nodeWeight;
}

// sets

void Node::setNodeWeight(float _nodeWeight)
{
     this->nodeWeight = _nodeWeight;
}

void Node::setNextNode(Node *_nextNode)
{
     this->nextNode = _nextNode;
}

// Incrementa o Grau
void Node::incrementDegree()
{
     this->degree++;
}
// Incrementa o Grau de entrada
void Node::incrementInDegree()
{
     this->inDegree++;
}
// Incrementa o Grau de saida
void Node::incrementOutDegree()
{
     this->outDegree++;
}
// Decrementa o Grau
void Node::decrementDegree()
{
     this->degree--;
}
// Decrementa o Grau de entrada
void Node::decrementInDegree()
{
     this->inDegree--;
}
// Decrementa o Grau de saida
void Node::decrementOutDegree()
{
     this->outDegree--;
}
// Adiciona uma nova aresta com peso
void Node::addEdge(int _id, float _weightEdge)
{
     // Verifico se tem ao menos uma aresta no no
     if (this->firstEdge != nullptr)
     {
          // Add uma nova aresta(sem perder a referencia)
          Edge *NewEdge = new Edge(_id);
          NewEdge->setEdgeWeight(_weightEdge);
          this->lastEdge->setNextEdge(NewEdge);
          this->lastEdge = NewEdge;
     }
     else
     {
          // Add uma nova aresta caso ainda nao tenha
          // nenhuma aresta no No(sem perder a referencia)
          this->firstEdge = new Edge(_id);
          this->firstEdge->setEdgeWeight(_weightEdge);
          this->lastEdge = this->firstEdge;
     }
}

void Node::removeAllEdges()
{
     // Verifica se tem aresta no nó
     if (this->firstEdge != nullptr)
     {
          Edge *next = nullptr;
          Edge *aux = this->firstEdge;
          // Removo todas as arestas do No
          while (aux != nullptr)
          {
               next = aux->getNextEdge();
               delete aux;
               aux = next;
          }
     }
     this->firstEdge = this->lastEdge = nullptr;
}

void Node::removeEdge(int _id, bool _directed, Node *_node)
{
     // Verifica se tem aresta no nó
     if (this->searchEdge(_id))
     {
          Edge *aux = this->firstEdge;
          Edge *prev = nullptr;
          // Loop até achar a aresta
          while (aux->getId() != id)
          {
               prev = aux;
               aux = aux->getNextEdge();
          }
          // Ajusto para não perder a referencia quando deletar
          if (prev != nullptr)
               prev->setNextEdge(aux->getNextEdge());
          else
               this->firstEdge = aux->getNextEdge();
          if (aux == this->lastEdge)
               this->lastEdge = prev;
          if (aux->getNextEdge() == this->lastEdge)
               this->lastEdge = aux->getNextEdge();
          delete aux;
          // Verifica se o gráfico é direcionado
          if (_directed)
               this->decrementOutDegree();
          else
          {
               this->decrementInDegree();
               _node->decrementInDegree();
          }
     }
}

Edge *Node::searchEdge(int _id)
{
     // Verifica se tem aresta no nó
     if (this->firstEdge != nullptr)
     {
          // Pego a primeira aresta
          Edge *aux = this->firstEdge;

          do
          {
               if (aux->getId() == _id)  // vefico se a aresta tem o mesmo
                    return aux;          // id passado por parametro e retorno true
               aux = aux->getNextEdge(); // Pego a proxima aresta

          } while (aux != nullptr); // Verifico se ela existe
     }
     return nullptr;
}

bool Node::isVisited()
{
     return this->visited;
}

double Node::getRatio()
{
     return this->ratio;
}

void Node::setRatio(double _ratio)
{
     this->ratio = _ratio;
}

void Node::setVisited(bool _visited)
{
     this->visited = _visited;
}

// Destrutor
Node::~Node()
{
     Edge *edge = this->firstEdge;

     while (edge != nullptr)
     {
          Edge *aux = edge->getNextEdge();
          delete edge;
          edge = aux;
     }
}