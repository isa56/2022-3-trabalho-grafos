#include <iostream>
#include <fstream>  // lib de file stream
#include <sstream>  // lib de string stream
#include <unistd.h> // lib de timeout
#include <vector>
#include <algorithm>
#include <string>
#include "Graph.h"
#include "Metrics.h"
#include "GreedyAlgorithm.h"

using namespace std;

string getFileName(string txt)
{
     size_t pos = txt.find_last_of("/");
     string str2 = txt.substr(pos + 1, txt.size());
     return str2;
}

Graph *readFilePartOne(ifstream &input_file, int directed, int isEdgeWeighted, int isNodeWeighted, string firstReading)
{

     // Variáveis para auxiliar na criação dos nós no Grafo
     int idNodeSource;
     int idNodeTarget;
     int order;

     // Pegando a ordem do grafo
     if (firstReading == "")
     {
          input_file >> order;
     }
     else
     {
          order = stoi(firstReading);
     }

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

Graph *readFilePartTwo(ifstream &input_file)
{
     // Variáveis para auxiliar na criação dos nós no Grafo
     string line;
     int order, hasEdge, nodeWeight;
     float position;

     // A primeira linha já está limpa pelo readFile

     // Pegando a ordem do grafo:
     input_file >> order;

     // Cria o grafo:
     Graph *graph = new Graph(order, false, false, true);

     // Pega a linha de texto com as posições:
     input_file >> line;
     // Pega as posições e faz algo com elas:
     for (int i = 0; i < order; i++)
     {
          input_file >> position;
          input_file >> position;
          graph->insertNode(i);
     }

     // Pega o texto dos pesos:
     input_file >> line;
     // Pega os pesos e adiciona aos nós:
     for (int i = 0; i < order; i++)
     {
          input_file >> nodeWeight;
          graph->getNode(i)->setNodeWeight(nodeWeight);
     }

     // Pega o texto das arestas:
     input_file >> line;
     // Pega as arestas e adiciona ao grafo:
     for (int i = 0; i < order; i++)
     {
          for (int j = 0; j < order; j++)
          {
               input_file >> hasEdge;

               // Não insere aresta de um nó para ele mesmo, nem multiarestas
               if (i >= j)
               {
                    continue;
               }

               if (hasEdge == 1)
               {
                    graph->insertEdge(i, j, hasEdge);
               }
          }
     }
     return graph;
}

Graph *readFile(ifstream &input_file, int directed, int isEdgeWeighted, int isNodeWeighted)
{
     string firstLine;
     Graph *g;
     // le a primeira linha do arquivo
     input_file >> firstLine;

     // Se a primeira linha do arquivo for um numero, é o formato da parte 1
     if (firstLine[0] >= '0' && firstLine[0] <= '9')
     {
          g = readFilePartOne(input_file, directed, isEdgeWeighted, isNodeWeighted, firstLine);
     }
     else
     {
          g = readFilePartTwo(input_file);
     }

     return g;
}

char menu()
{
     char selection;

     cout << "----- MENU -----" << endl;

     cout << "(A) - Grafo Interseção" << endl;
     cout << "(B) - Grafo União" << endl;
     cout << "(C) - Grafo Diferença" << endl;
     cout << "(D) - Rede Pert" << endl;
     cout << "(E) - Algoritmo Construtivo Guloso;" << endl;
     cout << "(F) - Algoritmo Construtivo Guloso Randomizado e Adaptativo;" << endl;
     cout << "(G) - Algoritmo Construtivo Guloso Randomizado Reativo." << endl;

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
          graphG2 = readFilePartOne(input_file, directed, weightedEdge, weightedNode, "");

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
          graphG2 = readFilePartOne(input_file, directed, weightedEdge, weightedNode, "");

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
          graphG2 = readFilePartOne(input_file, directed, weightedEdge, weightedNode, "");

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
     case 'E': // Algoritmo Guloso
     {
          cout << "(E) - Algoritmo Construtivo Guloso" << endl;
          Metrics p;
          Setup_metrics(&p);
          auto t0 = std::chrono::high_resolution_clock::now();

          // Algoritmo
          beginGreedyAlgorithm(graphG1);
          // Teste de tempo
          auto t1 = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> delta = t1 - t0;
          Set_CPUtime(&p, delta.count());
          cout << "Performace:" << endl;
          Print_metrics(&p);
          cout << endl;
          break;
     }
     case 'F':
     {
          cout << "(F) - Algoritmo construtivo guloso randomizado e adaptativo" << endl;
          Metrics p;
          Setup_metrics(&p);

          float alpha;
          int iterNumber;
          std::chrono::duration<double> bestSolution;

          // Escolha do valor do alpha
          cout << "Digite o valor do alfa a ser utilizado no algoritmo: ({0.05, 0.10, 0.15, 0.30, 0,50})" << endl;
          cin >> alpha;

          // // Escolha do valor da quantidade de iterações
          // cout << "Digite a quantidade de iterações: " << endl;
          // // cin >> iterNumber;
          // // Algoritmo

          vector<Node *> teste;

          iterNumber = 500;
          for (int i = 0; i < iterNumber; i++)
          {
               auto t0 = std::chrono::high_resolution_clock::now();
               teste = beginRandomizedAdaptativeAlgorithm(graphG1, alpha);
               // Teste de tempo
               auto t1 = std::chrono::high_resolution_clock::now();
               std::chrono::duration<double> delta = t1 - t0;

               // Caso seja a primeira vez que o loop está rodando, ele vai setar a melhor solução como a primeira
               if (i == 0)
                    bestSolution = delta;
               if (delta < bestSolution)
               {
                    bestSolution = delta;
               }
               Set_CPUtime(&p, delta.count());
               cout << i + 1 << "°) Performace de Delta:" << endl;
               Print_metrics(&p);
          }
          for (size_t i = 0; i < teste.size(); i++)
          {
               if (i % 20 == 0)
                    output_file << endl;
               output_file << teste[i]->getId() << " ";
          }
          Set_CPUtime(&p, bestSolution.count());
          output_file << "\nPerformace: " << p.time << endl;
          output_file << "Alfa: " << alpha << " e interaçoes: " << iterNumber << endl;
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
     vector<char> selectionCheck = {'A', 'B', 'C', 'D', 'E', 'F', 'P', 'X'};
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
