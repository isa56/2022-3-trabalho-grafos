#include <iostream>
#include <string>
#include <fstream>
#include "include/Graph.h"
#include "include/FileUtils.h"

using namespace std;

int main(int argc, char const *argv[])
{
  // Verificação se todos os parâmetros do programa foram entrados
  if (argc != 6)
  {
    cout << "ERRO: Esperado: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
    return 1;
  }
  // argv[0] -> Nome do Programa
  // argv[1] -> Diretório do arquivo de entrada
  // argv[2] -> Diretório do arquivo de saída
  // argv[3] -> Se o grafo é orientado (1) ou não (0)
  // argv[4] -> Se o grafo tem peso nas arestas"(1) ou não (0)
  // argv[5] -> Se o grafo tem peso nos vértices (1) ou não (0)

  string program_name(argv[0]);
  string input_file_name(argv[1]);
  string output_file_name(argv[2]);
  string isOriented(argv[3]);
  string isEdgeWeighted(argv[4]);
  string isNodeWeighted(argv[5]);

  input_file_name = "./input/" + input_file_name;
  output_file_name = "./output/" + output_file_name;

  ifstream input_file;
  ofstream output_file;
  input_file.open(input_file_name, ios::in);
  output_file.open(output_file_name, ios::app); //| ios::trun

  if (!input_file.is_open())
  {
    cout << "Erro no arquivo de leitura!" << endl;
    cout << input_file_name;
    return -1;
  }
  if (!output_file.is_open())
  {
    cout << "Erro no arquivo de salvamento!" << endl;
    cout << output_file_name;
    return -1;
  }

  Graph *graph;

  graph = readFile(input_file, atoi(isOriented.c_str()), atoi(isEdgeWeighted.c_str()), atoi(isNodeWeighted.c_str()));

  mainMenu(output_file, graph, input_file_name);

  // Fechando arquivo de entrada
  input_file.close();

  // Fechando arquivo de saída
  output_file.close();

  if (input_file.is_open() || output_file.is_open())
  {
    cout << "Erro ao fechar os arquivos!" << endl;
    return 1;
  }
  // Alguns testes para os argumentos da main
  // cout << "Nome do arquivo .exe! -> " << program_name << endl;
  // cout << "Nome do arquivo de entrada .txt! -> " << input_file_name << endl;
  // cout << "Nome do arquivo de saida .txt! -> " << output_file_name << endl;

  // cout << "O grafo sera" << ((isOriented == "0") ? " não orientado\n" : " orientado\n");
  // cout << "O grafo sera com peso nas arestas? R: -> " << ((isEdgeWeighted == "0") ? " não!\n" : "sim!\n");
  // cout << "O grafo sera com peso nos vertices? R: -> " << ((isNodeWeighted == "0") ? " não!\n" : "sim!\n");

  graph->~Graph();
  delete graph;
  return 0;
}