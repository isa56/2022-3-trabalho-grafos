#include "./include/Graph.h"
#include "./include/Metrics.h"
#include <iostream>
#include <vector>

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
     Node *next;
     Node *aux = nullptr;

     // Verifica se já existe algum nó
     if (this->getFirstNode() == nullptr)
     {
          this->firstNode = new Node(_id);
          this->lastNode = this->getFirstNode();
     }
     else
     {
          if (!this->searchNode(_id))
          {
               next = this->firstNode;
               // Procura o último nó inserido
               while (next != nullptr)
               {
                    aux = next;
                    next = next->getNextNode();
               }
               // Inseri o nó na última posição
               aux->setNextNode(new Node(_id));
               this->lastNode = this->getNode(_id);
          }
     }
     // // Crio o vertice
     // Node *NewNode = new Node(_id);
     // if (firstNode != nullptr) // Se tem vertice no grafo
     // {
     //      // Seta o ultimo vertice pro novo vertice e o novo se torna o ultimo vertice
     //      lastNode->setNextNode(NewNode);
     //      lastNode = NewNode;
     // }
     // else // Se não tem vertice no grafo
     // {
     //      // Seta o vertice como o ultimo e o primeiro vertice
     //      firstNode = NewNode;
     //      lastNode = NewNode;
     // }
}
void Graph::insertEdge(int _id, int _targetId, float _weightEdge)
{
     // Se o Mó existe eu so adiciono a aresta
     if (!this->searchNode(_id))
     {
          this->insertNode(_id);
     }
     if (!this->searchNode(_targetId))
     {
          this->insertNode(_targetId);
     }

     // Insiro aresta do nó id-targetId
     Node *nodeId = this->getNode(_id);
     Node *nodeTargetId = this->getNode(_targetId);
     if (this->getDirected())
     {
          nodeId->addEdge(_targetId, _weightEdge);
          nodeId->incrementOutDegree();
          nodeTargetId->incrementInDegree();
     }
     else
     {
          nodeId->addEdge(_targetId, _weightEdge);
          nodeTargetId->addEdge(_id, _weightEdge);
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
     Edge *edge;
     if (aux != nullptr)
     {
          // Teste de tempo
          Metrics p;
          Setup_metrics(&p);
          auto t0 = std::chrono::high_resolution_clock::now();

          while (aux != nullptr)
          {
               edge = aux->getFirstEdge();
               cout << aux->getId() << " => ";
               while (edge != nullptr)
               {
                    cout << edge->getId() << " - ";
                    edge = edge->getNextEdge();
               }
               cout << "null" << endl;
               aux = aux->getNextNode();
          }

          cout << endl;

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

void Graph::graphIntersection(Graph *G1, Graph *G2)
{
     vector<int> NodeIntersection;
     Node *NodeG1 = G1->getFirstNode();
     while (NodeG1 != nullptr)
     {
          Node *NodeG2 = G2->getFirstNode();
          while (NodeG2 != nullptr)
          {
               if (NodeG1->getId() == NodeG2->getId())
               {
                    NodeIntersection.push_back(NodeG1->getId());
                    cout << "iguais " << NodeG1->getId() << " ";
               }
               NodeG2 = NodeG2->getNextNode();
          }

          NodeG1 = NodeG1->getNextNode();
     }

     if (G1->getNode(2)->searchEdge(3))
     {
          cout << "Aresta é " << G1->getNode(2)->getFirstEdge()->getWeightEdge() << endl;
     }
     cout << endl;
}