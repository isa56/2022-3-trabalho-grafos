#include <iostream>
#include <fstream>  // lib de file stream
#include <sstream>  // lib de string stream
#include <unistd.h> // lib de timeout
#include <vector>
#include <algorithm>
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

     if (!graph->getWeightedEdge() && !graph->getWeightedNode())
     {

          while (input_file >> idNodeSource >> idNodeTarget)
          {

               graph->insertEdge(idNodeSource, idNodeTarget, 0);
          }
     }
     else if (graph->getWeightedEdge() && !graph->getWeightedNode())
     {

          float edgeWeight;

          while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
          {

               graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
          }
     }
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

     return toupper(selection);
}

void selecionar(char selection, Graph *graphG1, ofstream &output_file)
{

     switch (selection)
     {
     case 'A': // Grafo Interseção
     {

          cout << "(A) - Grafo Interseção" << endl;
          Graph *graphIntersection, *graphG2;

          ifstream input_file;
          input_file.open("testeasa.txt", ios::in);
          graphG2 = readFile(input_file, graphG1->getDirected(), graphG1->getWeightedEdge(), graphG1->getWeightedNode());
          graphIntersection->graphIntersection(graphG1, graphG2);
          break;
     }
     case 'B': // Grafo União
     {
          cout << "(B) - Grafo União" << endl;
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
     } while (it == selectionCheck.end());

     // while (selection != 'X')
     // {
     //      // system("clear");
     //      selection = menu();
     //      cout << selection << endl;
     //      if (output_file.is_open())
     //           selecionar(selection, graph, output_file);
     //      else
     //           cout << "Erro no arquivo de salvamento!" << endl;

     //      output_file << endl;
     // }
     return 0;
}
