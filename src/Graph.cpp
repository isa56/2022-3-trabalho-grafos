#include "./include/Graph.h"
#include "./include/Metrics.h"
#include <iostream>

// Construtor
Graph::Graph(int _order, bool _directed, bool _weightedEdge, bool _weightedNode)
{
     this->order = _order;
     this->directed = _directed;
     this->weightedEdge = _weightedEdge;
     this->weightedNode = _weightedNode;

     this->firstNode = nullptr;
     this->lastNode = nullptr;
     this->numberEdges = 0;
}
// Os gets
int Graph::getOrder()
{
     return this->order;
}
int Graph::getNumberEdges()
{
     return this->numberEdges;
}

bool Graph::getDirected()
{
     return this->directed;
}

bool Graph::getWeightedEdge()
{
     return this->weightedEdge;
}

bool Graph::getWeightedNode()
{
     return this->weightedNode;
}

Node *Graph::getFirstNode()
{
     return this->firstNode;
}

Node *Graph::getLastNode()
{
     return this->lastNode;
}

// Insere um Novo vertice
void Graph::insertNode(int _id)
{
     // Crio o vertice
     Node *NewNode = new Node(_id);
     if (firstNode != nullptr) // Se tem vertice no grafo
     {
          // Seta o ultimo vertice pro novo vertice e o novo se torna o ultimo vertice
          lastNode->setNextNode(NewNode);
          lastNode = NewNode;
     }
     else // Se não tem vertice no grafo
     {
          // Seta o vertice como o ultimo e o primeiro vertice
          firstNode = NewNode;
          lastNode = NewNode;
     }
     order++;
}
void Graph::insertEdge(int _id, int _targetId, float _weightEdge)
{
     insertNode(_id);
     insertNode(_targetId);

     // Insiro aresta do nó id-targetId
     getNode(_id)->addEdge(_targetId, +weightedEdge);

     if (!this->directed)
     {
          getNode(_targetId)->addEdge(_id, _weightEdge);
     }

     this->numberEdges++;
}
void Graph::removeNode(int _id)
{
     Node *aux = this->firstNode;
     if (aux->getId() == _id) // Verifica se o No a ser removido
     {                        // é o primeiro No
          firstNode = aux->getNextNode();
          delete aux;
     }
     else if (this->searchNode(_id))       // Se não é o primeiro No na lista
     {                                     // e existe no grafo
          Node *prev = aux;                // aponta para o No anterior a ser removido
          aux = aux->getNextNode();        // o que vai ser removido
          Node *next = aux->getNextNode(); // aponta para o proximo No do que vai ser removido
          while (aux != nullptr)
          {
               if (aux->getId() == _id) // Encontro o no a ser removido
               {
                    prev->setNextNode(next);
                    delete aux;
                    return;
               }
               prev = aux;
               aux = aux->getNextNode();
               next = aux->getNextNode();
          }
     }
}
// Pesquisa se o Vertice existe
bool Graph::searchNode(int _id)
{
     Node *node = firstNode; // Vertice auxiliar

     while (node != nullptr)
     {
          if (node->getId() == _id)
          {
               return true;
          }
          node = node->getNextNode();
     }

     return false;
}
Node *Graph::getNode(int _id)
{
     Node *node = this->getFirstNode();

     while (node != nullptr)
     {
          if (node->getId() == _id)
               return node;
          node = node->getNextNode();
     }
     return nullptr;
}
void Graph::printList()
{
     cout << "Ordem: " << this->getOrder() << endl;
     cout << "numero de Arestas: " << this->getNumberEdges() << endl;
     cout << "Direcionado: " << this->getDirected() << endl;
     // cout << this->getNodePosition() << endl;
     cout << "Peso na aresta: " << this->getWeightedEdge() << endl;
     cout << "Peso no vertice: " << this->getWeightedNode() << endl;

     Node *aux = this->getFirstNode();
     if (aux != nullptr)
     {
          // Teste de tempo
          Metrics p;
          Setup_metrics(&p);
          auto t0 = std::chrono::high_resolution_clock::now();

          // for (size_t i = 0; i < this->getNumberEdges(); i++)
          // {
          cout << aux->getId() << " Aponta para os seguintes vertices -> ";
          // while (aux->getNextNode() != nullptr)
          // {
          int i = 0;
          while (i <= 16)
          {
               cout << aux->getId() << " - ";
               aux = aux->getNextNode();
               i++;
          }

          // aux->setNextNode(aux->getNextNode());
          // }
          cout << endl;
          // }
          // Teste de tempo
          auto t1 = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> delta = t1 - t0;
          Set_CPUtime(&p, delta.count());
          cout << "Performace:" << endl;
          Print_metrics(&p);
          cout << endl;
     }
}
// Destrutor
Graph::~Graph()
{
     Node *nextNode = this->firstNode;

     while (nextNode != nullptr)
     {

          nextNode->removeAllEdges();
          Node *auxNode = nextNode->getNextNode();
          delete nextNode;
          nextNode = auxNode;
     }
}