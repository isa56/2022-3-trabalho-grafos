#include <iostream>
#include <fstream>  // lib de file stream
#include <sstream>  // lib de string stream
#include <unistd.h> // lib de timeout
#include <vector>
#include <algorithm>
#include <string>
#include "Graph.h"
using namespace std;

Graph *readFile(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

     // Variáveis para auxiliar na criação dos nós no Grafo
     int idNodeSource;
     int idNodeTarget;
     int order;

     // Pegando a ordem do grafo
     input_file >> order;

     // Criando objeto grafo
     Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

     // Leitura de arquivo

     // Ler um arquivo sem peso nas Aresta e nos Vertices
     if (!graph->getWeightedEdge() && !graph->getWeightedNode())
     {
          while (input_file >> idNodeSource >> idNodeTarget)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, 0);
          }
     }
     // Ler um arquivo com peso nas Aresta e sem peso nos Vertices
     else if (graph->getWeightedEdge() && !graph->getWeightedNode())
     {
          float edgeWeight;
          while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
          }
     }
     // Ler um arquivo com peso nos Vertices e sem peso nas Aresta
     else if (graph->getWeightedNode() && !graph->getWeightedEdge())
     {
          float nodeSourceWeight, nodeTargetWeight;
          while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, 0);
               graph->getNode(idNodeSource)->setWeightNode(nodeSourceWeight);
               graph->getNode(idNodeTarget)->setWeightNode(nodeTargetWeight);
          }
     }
     // Ler um arquivo com peso nas Aresta e nos Vertices
     else if (graph->getWeightedNode() && graph->getWeightedEdge())
     {
          float nodeSourceWeight, nodeTargetWeight, edgeWeight;
          while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
               graph->getNode(idNodeSource)->setWeightNode(nodeSourceWeight);
               graph->getNode(idNodeTarget)->setWeightNode(nodeTargetWeight);
          }
     }

     return graph;
}

char menu()
{
     char selection;

     cout << "----- MENU -----" << endl;

     cout << "(A) - Grafo Interseção" << endl;
     cout << "(B) - Grafo União" << endl;
     cout << "(C) - Grafo Diferença" << endl;
     cout << "(D) - Rede Pert" << endl;

     cout << "(P) - Imprimir a Lista" << endl;
     cout << "(x) - Sair" << endl;

     cout << "\nSua escolha: ";
     cin >> selection;
     // Return sempre maiusculo
     return toupper(selection);
}

void selecionar(char selection, Graph *graphG1, ofstream &output_file)
{

     switch (selection)
     {
     case 'A': // Grafo Interseção
     {

          cout << "(A) - Grafo Interseção" << endl;
          Graph *graphG2;
          ifstream input_file;

          // // Para passar o G2 via cin
          // string Intersection;
          // cout << "Qual o diretorio do Grafo G2 <input_file>\n";
          // cin >> Intersection;

          int order = graphG1->getOrder();
          bool directed, weightedEdge, weightedNode;
          directed = graphG1->getDirected();
          weightedEdge = graphG1->getWeightedEdge();
          weightedNode = graphG1->getWeightedNode();

          input_file.open("Entrada_Intersecao.txt", ios::in);
          // Cria um grafo com as mesmas especificações do G1
          graphG2 = readFile(input_file, directed, weightedEdge, weightedNode);

          Graph *graphIntersection_ = new Graph(order, directed, weightedEdge, weightedNode);

          graphIntersection_->graphIntersection(graphG1, graphG2);
          graphIntersection_->printList();
          break;
     }
     case 'B': // Grafo União
     {
          cout << "(B) - Grafo União" << endl;
          Graph *graphG2;
          ifstream input_file;
          int order = graphG1->getOrder();
          bool directed, weightedEdge, weightedNode;
          directed = graphG1->getDirected();
          weightedEdge = graphG1->getWeightedEdge();
          weightedNode = graphG1->getWeightedNode();

          // Desconderar o nome Entrada_Intersecao.txt
          input_file.open("Entrada_Intersecao.txt", ios::in);
          // Cria um grafo com as mesmas especificações do G1
          graphG2 = readFile(input_file, directed, weightedEdge, weightedNode);

          Graph *graphUnion = new Graph(order, directed, weightedEdge, weightedNode);

          graphUnion->graphUnion(graphG1, graphG2);
          graphUnion->printList();
          break;
     }
     case 'C': // Grafo Diferença
     {
          cout << "(C) - Grafo Diferença" << endl;
          break;
     }
     case 'D': // Rede Pert
     {
          cout << "(D) - Rede Pert" << endl;
          break;
     }
     case 'P':
     {
          cout << "(P) - Imprimir a Lista" << endl;
          graphG1->printList();
          break;
     }
     case 'X': // Sair;
     {
          cout << "Saindo da aplicação" << endl;
          sleep(1);
          system("clear");
          exit(0);

          break;
     }
     default:
     {
          cout << "Error!!! Opção invalida!" << endl;
          sleep(1);
          break;
     }
     }
}

int mainMenu(ofstream &output_file, Graph *graph)
{
     // Verifica se as a pessoa digitou uma opção valida
     char selection = '1';
     vector<char> selectionCheck = {'A', 'B', 'C', 'D', 'E', 'P', 'X'};
     auto it = find(selectionCheck.begin(), selectionCheck.end(), selection);
     do
     {
          system("clear");
          selection = menu();
          it = find(selectionCheck.begin(), selectionCheck.end(), selection);
          if (output_file.is_open())
               selecionar(selection, graph, output_file);
          else
               cout << "Erro no arquivo de salvamento!" << endl;
          output_file << endl;
     } while (it == selectionCheck.end()); // looping ate ter uma opção aceitavel
     return 0;
}
