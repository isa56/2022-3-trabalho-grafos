#include <iostream>
#include <fstream>  // lib de file stream
#include <sstream>  // lib de string stream
#include <unistd.h> // lib de timeout
#include <vector>
#include <algorithm>
#include <string>
#include "Graph.h"
#include "Metrics.h"

using namespace std;

string getFileName(string txt)
{
     size_t pos = txt.find_last_of("/");
     string str2 = txt.substr(pos + 1, txt.size());
     return str2;
}

Graph *readFile(ifstream &input_file, int directed, int isEdgeWeighted, int isNodeWeighted)
{

     // Variáveis para auxiliar na criação dos nós no Grafo
     int idNodeSource;
     int idNodeTarget;
     int order;

     // Pegando a ordem do grafo
     input_file >> order;

     // Criando objeto grafo
     Graph *graph = new Graph(order, directed, isEdgeWeighted, isNodeWeighted);

     // Leitura de arquivo

     // Ler um arquivo sem peso nas Aresta e nos Vertices
     if (!isEdgeWeighted && !isNodeWeighted)
     {
          while (input_file >> idNodeSource >> idNodeTarget)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, 0);
          }
     }
     // Ler um arquivo com peso nas Aresta e sem peso nos Vertices
     else if (isEdgeWeighted && !isNodeWeighted)
     {
          float edgeWeight;
          while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
          }
     }
     // Ler um arquivo com peso nos Vertices e sem peso nas Aresta
     else if (!isEdgeWeighted && isNodeWeighted)
     {
          float nodeSourceWeight, nodeTargetWeight;
          while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, 0);
               graph->getNode(idNodeSource)->setNodeWeight(nodeSourceWeight);
               graph->getNode(idNodeTarget)->setNodeWeight(nodeTargetWeight);
          }
     }
     // Ler um arquivo com peso nas Aresta e nos Vertices
     else if (isEdgeWeighted && isNodeWeighted)
     {
          float nodeSourceWeight, nodeTargetWeight, edgeWeight;
          while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight >> edgeWeight)
          {
               graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
               graph->getNode(idNodeSource)->setNodeWeight(nodeSourceWeight);
               graph->getNode(idNodeTarget)->setNodeWeight(nodeTargetWeight);
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

void selecionar(char selection, Graph *graphG1, ofstream &output_file, string input_file_name)
{
     int order = graphG1->getOrder();
     bool directed, weightedEdge, weightedNode;
     directed = graphG1->isDirected();
     weightedEdge = graphG1->isEdgeWeighted();
     weightedNode = graphG1->isNodeWeighted();
     GraphDOT GDot;
     GDot.G1 = getFileName(input_file_name);
     switch (selection)
     {
     case 'A': // Grafo Interseção
     {

          cout << "(A) - Grafo Interseção" << endl;
          ifstream input_file;
          Graph *graphG2;
          // Para passar o G2 via cin
          string Intersection;
          cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
          cin >> Intersection;
          GDot.G2 = Intersection;

          input_file.open("./input/" + Intersection, ios::in);
          while (!input_file.is_open()) // Espera uma entrada valida
          {
               cout << "Erro no arquivo de leitura!" << endl;
               cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
               cin >> Intersection;
               GDot.G2 = Intersection;
               input_file.open("./input/" + Intersection, ios::in);
          }

          // Cria um grafo com as mesmas especificações do G1
          graphG2 = readFile(input_file, directed, weightedEdge, weightedNode);

          Graph *graphIntersection_ = new Graph(order, directed, weightedEdge, weightedNode);

          graphIntersection_->graphIntersection(graphG1, graphG2);
          graphIntersection_->printList();

          GDot.description = "Grafo Interseção: dados dois grafos G1 = (V1, E1) e G2 = (V2,E2),\n o grafo interseção de G1 com G2 é dado por: G* = (V1 ∩ V2, E1 ∩ E2);";
          GDot.type = "Intersection";
          graphIntersection_->FileDot(output_file, GDot);

          delete graphIntersection_;
          delete graphG2;
          break;
     }
     case 'B': // Grafo União
     {
          cout << "(B) - Grafo União" << endl;
          ifstream input_file;
          Graph *graphG2;
          // Para passar o G2 via cin
          string Union;
          cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
          cin >> Union;
          GDot.G2 = Union;

          input_file.open("./input/" + Union, ios::in);
          while (!input_file.is_open()) // Espera uma entrada valida
          {
               cout << "Erro no arquivo de leitura!" << endl;
               cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
               cin >> Union;
               GDot.G2 = Union;
               input_file.open("./input/" + Union, ios::in);
          }

          // Cria um grafo com as mesmas especificações do G1
          graphG2 = readFile(input_file, directed, weightedEdge, weightedNode);

          Graph *graphUnion_ = new Graph(order, directed, weightedEdge, weightedNode);

          graphUnion_->graphUnion(graphG1, graphG2);
          graphUnion_->printList();

          GDot.description = "Grafo União: dados dois grafos G1 = (V1, E1) e G2 = (V2,E2),\n o grafo interseção de G1 com G2 é dado por: G+ = (V1 U V2, E1 U E2);";
          GDot.type = "Union";

          graphUnion_->FileDot(output_file, GDot);

          delete graphUnion_;
          delete graphG2;
          break;
     }
     case 'C': // Grafo Diferença
     {
          cout << "(C) - Grafo Diferença" << endl;
          ifstream input_file;
          Graph *graphG2;
          // Para passar o G2 via cin
          string Difference;
          cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
          cin >> Difference;
          GDot.G2 = Difference;

          input_file.open("./input/" + Difference, ios::in);
          while (!input_file.is_open()) // Espera uma entrada valida
          {
               cout << "Erro no arquivo de leitura!" << endl;
               cout << "Qual o diretorio do Grafo G2 <input_file>\n> ";
               cin >> Difference;
               GDot.G2 = Difference;
               input_file.open("./input/" + Difference, ios::in);
          }

          // Cria um grafo com as mesmas especificações do G1
          graphG2 = readFile(input_file, directed, weightedEdge, weightedNode);

          Graph *graphDifference_ = new Graph(order, directed, weightedEdge, weightedNode);

          graphDifference_->graphUnion(graphG1, graphG2);
          graphDifference_->printList();

          GDot.description = "Grafo Diferença: dados dois grafos G1 = (V, E1) e G2 = (V,E2),\no grafo diferença de G1 com G2 é dado por: G_ = (V, E1/E2).Note que operador exige que E1 ⊇ E2;";
          GDot.type = "Difference";

          graphDifference_->FileDot(output_file, GDot);

          delete graphDifference_;
          delete graphG2;
          break;
     }
     case 'D': // Rede Pert
     {
          // TODO: implementar Rede PERT
          cout << "(D) - Rede Pert" << endl;
          Metrics p;
          Setup_metrics(&p);
          auto t0 = std::chrono::high_resolution_clock::now();
          GDot.description = "Grafo usado na Rede PERT";
          GDot.type = "Rede_PERT";
          graphG1->PERT();
          graphG1->FileDot(output_file, GDot);
          cout << endl;

          // Teste de tempo
          auto t1 = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> delta = t1 - t0;
          Set_CPUtime(&p, delta.count());
          cout << "Performace:" << endl;
          Print_metrics(&p);
          cout << endl;
          break;
     }
     case 'P': // Imprimir o Grafo
     {
          cout << "(P) - Imprimir a Lista" << endl;
          graphG1->printList();
          GDot.description = getFileName(input_file_name);
          GDot.type = "G";
          graphG1->FileDot(output_file, GDot);
          break;
     }
     case 'X': // Sair;
     {
          cout << "Saindo da aplicação" << endl;
          sleep(1);
          system("clear");
          graphG1->~Graph();
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

int mainMenu(ofstream &output_file, Graph *graph, string input_file_name)
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
               selecionar(selection, graph, output_file, input_file_name);
          else
               cout << "Erro no arquivo de salvamento!" << endl;
          output_file << endl;
     } while (it == selectionCheck.end()); // looping ate ter uma opção aceitavel
     return 0;
}
