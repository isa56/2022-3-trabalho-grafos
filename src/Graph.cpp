#include "./include/Graph.h"
#include "./include/Metrics.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

// Construtor
Graph::Graph(int _order, bool _directed, bool _weightedEdge, bool _weightedNode)
{
     this->order = _order;
     this->directed = _directed;
     this->edgeHasWeight = _weightedEdge;
     this->nodeHasWeight = _weightedNode;

     this->firstNode = nullptr;
     this->lastNode = nullptr;
     this->edgesNumber = 0;
}
void Graph::setOrder(int _order)
{
     this->order = _order;
}
// Os gets
int Graph::getOrder()
{
     return this->order;
}
int Graph::getEdgesNumber()
{
     return this->edgesNumber;
}

bool Graph::isDirected()
{
     return this->directed;
}

bool Graph::isEdgeWeighted()
{
     return this->edgeHasWeight;
}

bool Graph::isNodeWeighted()
{
     return this->nodeHasWeight;
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
               Node *next;
               Node *aux = nullptr;

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

     Node *node = this->getNode(_id);
     Node *targetNode = this->getNode(_targetId);
     if (this->isDirected())
     {
          node->addEdge(_targetId, _weightEdge);
          node->incrementOutDegree();
          targetNode->incrementInDegree();
          node->incrementDegree();
          targetNode->incrementDegree();
     }
     else
     {
          node->addEdge(_targetId, _weightEdge);
          targetNode->addEdge(_id, _weightEdge);
          node->incrementDegree();
          targetNode->incrementDegree();
     }

     this->edgesNumber++;
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
     cout << "numero de Arestas: " << this->getEdgesNumber() << endl;
     cout << "Direcionado: " << this->isDirected() << endl;
     // cout << this->getNodePosition() << endl;

     // TODO: criar funcao para retornar o peso no nó e na aresta (antes estava retornando apenas se o grafo era ponderado por no ou aresta)
     //  cout << "Peso na aresta: " << this->isEdgeWeighted() << endl;
     //  cout << "Peso no vertice: " << this->isNodeWeighted() << endl;

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
     Node *nextNode = this->getFirstNode();

     while (nextNode != nullptr)
     {
          nextNode->removeAllEdges();
          this->firstNode = nextNode->getNextNode();
          delete nextNode;
          nextNode = this->getFirstNode();
     }
     this->firstNode = this->lastNode = nullptr;
     delete nextNode;
}

void Graph::graphIntersection(Graph *G1, Graph *G2)
{ // Grafos G1 = (V1, E1) e G2 = (V2,E2),
     // Vetor com todos os vertices da interseção (V1 ∩ V2)
     vector<int> NodeIntersection;

     Node *NodeG1 = G1->getFirstNode(); // Pegando o primeiro Nó de G1

     while (NodeG1 != nullptr) // Percorrendo os Nos de G1
     {
          Node *NodeG2 = G2->getFirstNode(); // Pegando o primeiro Nó de G2
          while (NodeG2 != nullptr)          // Percorrendo os Nos de G2
          {
               // Verifico a interseção dos vertices (V1 ∩ V2)
               if (NodeG1->getId() == NodeG2->getId())
               {
                    NodeIntersection.push_back(NodeG1->getId()); // Colocando no vetor
               }
               NodeG2 = NodeG2->getNextNode(); // Proximo vertice de G2
          }
          NodeG1 = NodeG1->getNextNode(); // Proximo vertice de G1
     }
     // Setando a ordem correta do grafo interseção
     int order = NodeIntersection.size();
     this->setOrder(order);

     int x = 0;             // Variavel auxiliar para percorrer o vetor
     int _id, _targetId;    // Variavel auxiliar para salvar os vertices (padrao insertNode())
     float _weightEdge;     // Variavel auxiliar para salvar o peso da aresta entre dois vertices (padrao insertNode())
     Edge *EdgeG1, *EdgeG2; // Fica com a aresta entre os dois vertices (_id e _targetId)
     bool isolatedVertex;   // Variavel auxiliar para inserir vertices islodados

     // Se undirected é 1 signiica que ele é não direcionado
     int undirected = this->isDirected() == true ? 0 : 1;
     if (order == 0) // Sem interseção
     {
          cout << "Não tem intercesão entre os Grafos G1 e G2";
     }
     else if (order == 1) // Um vertice, ele não tem aresta
     {
          this->insertNode(NodeIntersection[0]);
     }
     else // 2 ou mais vertices, eles podem ter arestas entre eles
     {
          // Percorro todo o vetor comparando todos os valores possiveis (todas as combinaçoes)
          // Se é direcionado o undirected é 0 e eu percorro todas as combinaçoes

          /*
          . Se não é direcionado o undirected é 1 e eu percorro order -1
            o ultimo valor ja foi testado com todas as outras combinaçoes, por isso o -1
          */
          while (x < (order - undirected))
          {
               isolatedVertex = true;
               _id = NodeIntersection[x];
               /*
                    (x + 1) * undirected
                    undirected é 0 se o grafo é direcionado e 1 se o grafo não é direcionado
                    Quando é direcionado eu preciso ir de 0 ate order verificando todas as
                    possibilidades, ja que o sentido da aresta importa combinaçoes
                    x = 0-> order e y = x+1 -> order

                    Ja no não direcionado eu consigo ter um desempenho melhor, tento em vista
                    que não é preciso verificar o ultimo vertice e as combinaçoes e sempre
                    x = 0 -> order-1 e y = x+1 -> order
               */
               for (int y = ((x + 1) * undirected); y < order; y++)
               {

                    _targetId = NodeIntersection[y];
                    EdgeG1 = G1->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G1

                    if (EdgeG1 != nullptr) // Verifica sem tem aresta entre _id e _targetId
                    {
                         EdgeG2 = G2->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G2
                         if (EdgeG2 != nullptr)
                         {
                              _weightEdge = EdgeG1->getEdgeWeight(); // Peso da aresta
                              isolatedVertex = false;                // O vertice X não é isolado, tem aresta
                              this->insertEdge(_id, _targetId, _weightEdge);
                         }
                    }
               }
               if (isolatedVertex == true) // vertice isolado
               {
                    this->insertNode(_id); // Insere o vertice sem Aresta
               }

               x++;
          }
     }
}

void Graph::graphUnion(Graph *G1, Graph *G2)
{
     vector<int> NodeUnion; // Todos as arestas de  G1 e G2

     Node *NodeG1 = G1->getFirstNode(); // Pegando o primeiro Nó de G1

     while (NodeG1 != nullptr) // Percorrendo os Nos de G1
     {
          NodeUnion.push_back(NodeG1->getId()); // Colocando todos os vertices de G1
          NodeG1 = NodeG1->getNextNode();       // Proximo vertice de G1
     }
     Node *NodeG2 = G2->getFirstNode(); // Pegando o primeiro Nó de G2

     while (NodeG2 != nullptr) // Percorrendo os Nos de G2
     {
          // Verifico se o vertice de V2 esta em NodeUnion (V1 u V2)
          if (find(NodeUnion.begin(), NodeUnion.end(), NodeG2->getId()) == NodeUnion.end())
          {
               // If é falso(Vertice de G2 não esta em NodeUnion)
               NodeUnion.push_back(NodeG2->getId()); // Colocando no vetor
          }
          NodeG2 = NodeG2->getNextNode(); // Proximo vertice de G2
     }
     // Setando a ordem correta do grafo interseção
     int order = NodeUnion.size();
     this->setOrder(order);

     int x = 0;             // Variavel auxiliar para percorrer o vetor
     int _id, _targetId;    // Variavel auxiliar para salvar os vertices (padrao insertNode())
     float _weightEdge;     // Variavel auxiliar para salvar o peso da aresta entre dois vertices (padrao insertNode())
     Edge *EdgeG1, *EdgeG2; // Fica com a aresta entre os dois vertices (_id e _targetId)

     // Se undirected é 1 signfica que ele é não direcionado
     int undirected = this->isDirected() == true ? 0 : 1;
     if (order == 0) // G1 e G2 é vazio
     {
          cout << "G1 e G2 é nulo ";
     }
     else if (order == 1) // Um vertice, ele não tem aresta
     {
          this->insertNode(NodeUnion[0]);
     }
     /*
     Adicionar outras condiçoes (Pode ser no inicio, para melhor desempenho)
     caso1: order == G1->getOrder // Significa que G2 é nulo e a uniao de G1 u G2 é G1
     caso2: order == G2->getOrder  // Significa que G1 é nulo e a uniao de G1 u G2 é G2
     */
     else // 2 ou mais vertices, eles podem ter arestas entre eles
     {
          // Percorro todo o vetor comparando todos os valores possiveis (todas as combinaçoes)
          // Se é direcionado o undirected é 0 e eu percorro todas as combinaçoes

          /*
          . Se não é direcionado o undirected é 1 e eu percorro order -1
            o ultimo valor ja foi testado com todas as outras combinaçoes, por isso o -1
          */
          while (x < (order - undirected))
          {
               _id = NodeUnion[x];
               /*
                    (x + 1) * undirected
                    undirected é 0 se o grafo é direcionado e 1 se o grafo não é direcionado
                    Quando é direcionado eu preciso ir de 0 ate order verificando todas as
                    possibilidades, ja que o sentido da aresta importa combinaçoes
                    x = 0-> order e y = x+1 -> order

                    Ja no não direcionado eu consigo ter um desempenho melhor, tento em vista
                    que não é preciso verificar o ultimo vertice e as combinaçoes e sempre
                    x = 0 -> order-1 e y = x+1 -> order
               */

               for (int y = ((x + 1) * undirected); y < order; y++)
               {
                    EdgeG1 = EdgeG2 = nullptr;
                    _targetId = NodeUnion[y];
                    /*
                    Esses dois if é para não ter erro de memoria
                    Eles garantem  que eu so vou pegar a aresta se e somente se, no meu grafo tiver os vertices
                    _id e _targetId
                    Na união eu posso tentar achar uma aresta entre dois vertices de grafos diferentes
                    E o searchEdge(_targetId) parte do principio que o _targetId esta no grafo
                    */
                    if (G1->getNode(_id) != nullptr && G1->getNode(_targetId) != nullptr)
                         EdgeG1 = G1->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G1
                    if (G2->getNode(_id) != nullptr && G2->getNode(_targetId) != nullptr)
                         EdgeG2 = G2->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G2

                    if (EdgeG1 != nullptr) // Caso em que os vertices estão presente somente em G1
                    {
                         _weightEdge = EdgeG1->getEdgeWeight(); // Peso da aresta
                         this->insertEdge(_id, _targetId, _weightEdge);
                    }
                    else if (EdgeG2 != nullptr) // Caso em que os vertices estão presente somente em G2
                    {
                         _weightEdge = EdgeG2->getEdgeWeight(); // Peso da aresta
                         this->insertEdge(_id, _targetId, _weightEdge);
                    }
                    else
                    {
                         this->insertNode(_id); // Insere o vertice sem Aresta
                    }
               }

               x++;
          }
     }
}

void Graph::graphDifference(Graph *G1, Graph *G2)
{
     cout << "Grafo diferença" << endl;

     vector<int> NodeDifference; // Todos as arestas de  G1 e G2

     Node *NodeG1 = G1->getFirstNode(); // Pegando o primeiro Nó de G1

     while (NodeG1 != nullptr) // Percorrendo os Nos de G1
     {
          NodeDifference.push_back(NodeG1->getId()); // Colocando todos os vertices de G1
          NodeG1 = NodeG1->getNextNode();            // Proximo vertice de G1
     }
     Node *NodeG2 = G2->getFirstNode(); // Pegando o primeiro Nó de G2

     while (NodeG2 != nullptr) // Percorrendo os Nos de G2
     {
          // Verifico se o vertice de V2 esta em NodeDifference (V1 u V2)
          if (find(NodeDifference.begin(), NodeDifference.end(), NodeG2->getId()) == NodeDifference.end())
          {
               // Significa que V de G1 é diferente de V de G2 (G2 não esta contido em G1)
               cout << "G2 não esta contido em G1: Esta operação nao pode ser concluida" << endl;
               return;
          }
          NodeG2 = NodeG2->getNextNode(); // Proximo vertice de G2
     }

     int order = NodeDifference.size();
     this->setOrder(order);

     int x = 0;             // Variavel auxiliar para percorrer o vetor
     int _id, _targetId;    // Variavel auxiliar para salvar os vertices (padrao insertNode())
     float _weightEdge;     // Variavel auxiliar para salvar o peso da aresta entre dois vertices (padrao insertNode())
     Edge *EdgeG1, *EdgeG2; // Fica com a aresta entre os dois vertices (_id e _targetId)

     // Se undirected é 1 signfica que ele é não direcionado
     int undirected = this->isDirected() == true ? 0 : 1;
     while (x < (order - undirected))
     {
          _id = NodeDifference[x];
          /*
               (x + 1) * undirected
               undirected é 0 se o grafo é direcionado e 1 se o grafo não é direcionado
               Quando é direcionado eu preciso ir de 0 ate order verificando todas as
               possibilidades, ja que o sentido da aresta importa combinaçoes
               x = 0-> order e y = x+1 -> order

               Ja no não direcionado eu consigo ter um desempenho melhor, tento em vista
               que não é preciso verificar o ultimo vertice e as combinaçoes e sempre
               x = 0 -> order-1 e y = x+1 -> order
          */

          for (int y = ((x + 1) * undirected); y < order; y++)
          {
               EdgeG1 = EdgeG2 = nullptr;
               _targetId = NodeDifference[y];
               /*
               Esses dois if é para não ter erro de memoria
               Eles garantem  que eu so vou pegar a aresta se e somente se, no meu grafo tiver os vertices
               _id e _targetId
               */
               if (G1->getNode(_id) != nullptr && G1->getNode(_targetId) != nullptr)
                    EdgeG1 = G1->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G1
               if (G2->getNode(_id) != nullptr && G2->getNode(_targetId) != nullptr)
                    EdgeG2 = G2->getNode(_id)->searchEdge(_targetId); // A aresta entre _id e _targetId No G2

               /*
               A verificação de que Há arestas é
               * A aresta não pode esta em G1 e G2 (Por isso verifico sempre se um é nullptr)
                 1° if() Verifica se a aresta que tem em G1 não existe em G2
                 2° else if() Verifica se a aresta que tem em G2 não existe em G1
                 3° else{} Se chegar aqui significa que ha uma aresta entr _id e _targetId
                    tanto em G1 quanto em G2, e é por isso que o vertice é isolado
               */

               if (EdgeG1 != nullptr && EdgeG2 == nullptr) // Caso em que os vertices estão presente somente em G1
               {
                    _weightEdge = EdgeG1->getEdgeWeight(); // Peso da aresta
                    this->insertEdge(_id, _targetId, _weightEdge);
               }
               else if (EdgeG2 != nullptr && EdgeG1 == nullptr) // Caso em que os vertices estão presente somente em G2
               {
                    _weightEdge = EdgeG2->getEdgeWeight(); // Peso da aresta
                    this->insertEdge(_id, _targetId, _weightEdge);
               }
               else
               {
                    this->insertNode(_id); // Insere o vertice sem Aresta
               }
          }

          x++;
     }
}
void Graph::PERT()
{
     // TODO: implementar a Rede PERT
     cout << "Rede PERT" << endl;
     // [] Verificar se é aciclico (Com busca em profundidade)
     // [] Implementar Rede PERT

     vector<int> nodeStart;

     Node *Nos = this->getFirstNode();
     Edge *Arestas;
     int i = 0;
     // Ja sabemos quais os vertice para começar na rede PERT
     while (Nos != nullptr)
     {

          if (Nos->getInDegree() == 0 && Nos->getOutDegree() > 0)
          {
               nodeStart.push_back(Nos->getId());
          }

          Nos = Nos->getNextNode();
     }
}
void Graph::fileDot(ofstream &output_file, GraphDOT GDot)
{
     Node *node = this->getFirstNode();
     Edge *edge;
     // Para a sintaxe do .dot
     string IsDirected = this->isDirected() == true ? "digraph" : "graph";
     string symbolAux = this->isDirected() == true ? "->" : "--";
     bool weightedEdge = this->isEdgeWeighted();

     // Espaço e aspas
     char space = 32, quotationMarks = 34;

     string label = '"' + GDot.description + '"';
     // Descrição comentada no arquivo .dot
     output_file << "/*\nGrupo 21 (Eduardo Araujo, Isadora Ferreira e Miguel Sales)\nDisciplina Teoria dos Grafos - UFJF - Prof. Stênio Sã\n*/ " << endl;
     // Mostra os aquivo(s) que gerou o grafo
     output_file << "/*\n"
                 << "G1 é o arquivo: " << GDot.G1;
     if (GDot.G2.size() > 0)
          output_file
              << " e G2 é o arquivo: " << GDot.G2;

     output_file << "\n*/";

     output_file << endl;
     output_file << IsDirected << "  "
                 << GDot.type
                 << " {" << endl;
     output_file << "label = " << label << endl;

     while (node != nullptr)
     {
          // Caso o Vertice seja isolado
          if (node->getFirstEdge() == nullptr && node->getDegree() == 0)
               output_file << "  " << node->getId() << endl;
          if (IsDirected == "digraph")
          {
               edge = node->getFirstEdge();
               while (edge != nullptr)
               {
                    // Percorro todas as arestas caso ele seja um grafo direcionado
                    // O sentido importa e é por isso que eu verifico todas as possibilidades
                    output_file << node->getId() << "  " << symbolAux;
                    output_file << "  " << edge->getId() << "  ";
                    if (weightedEdge)
                         output_file << "[weight=" << edge->getEdgeWeight()
                                     << "] [label=" << quotationMarks << space
                                     << edge->getEdgeWeight() << quotationMarks
                                     << "] " << endl;
                    else
                         output_file << endl;
                    edge = edge->getNextEdge();
               }
          }
          else
          {
               Node *auxNode = node->getNextNode();
               while (auxNode != nullptr)
               {
                    /*
                    Percorro todas os vertices verificando se há aresta entre eles
                    (A logica do Grafo direcionado não serve, pois ele repete as arestas)
                    O Graphviz identifica a Aresta 2 -- 3 Diferente da Aresta 3 --2
                    (E assim tendo um Multigrafo [múltiplas arestas])
                    */
                    edge = node->searchEdge(auxNode->getId());
                    if (edge != nullptr)
                    {
                         output_file << node->getId() << "  " << symbolAux;
                         output_file << "  " << auxNode->getId() << "  ";
                         if (weightedEdge)
                              output_file << "[weight=" << edge->getEdgeWeight()
                                          << "] [label=" << quotationMarks << space
                                          << edge->getEdgeWeight() << quotationMarks
                                          << "] " << endl;
                         else
                              output_file << endl;
                    }
                    auxNode = auxNode->getNextNode();
               }
          }
          node = node->getNextNode();
     }
     output_file << "}";
}
