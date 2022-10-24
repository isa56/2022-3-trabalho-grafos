#include <iostream>
#include <string>
#include <fstream>
#include "./include/Graph.h"
#include "./include/FileUtils.h"
// #define INPUT_POND_DIR "./input
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
  string orientado(argv[3]);
  string pesoAresta(argv[4]);
  string pesoVertices(argv[5]);

  ifstream input_file;
  ofstream output_file;
  input_file.open(input_file_name, ios::in);
  output_file.open(output_file_name, ios::out); //| ios::trun

  if (!input_file.is_open())
  {
    cout << "Erro no arquivo de leitura!" << endl;
    return -1;
  }
  if (!output_file.is_open())
  {
    cout << "Erro no arquivo de salvamento!" << endl;
    return -1;
  }

  Graph *graph;

  graph = readFile(input_file, atoi(orientado.c_str()), atoi(pesoAresta.c_str()), atoi(pesoVertices.c_str()));

  mainMenu(output_file, graph);
  graph->printList();

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
  cout << "Nome do arquivo .exe! -> " << program_name << endl;
  cout << "Nome do arquivo de entrada .txt! -> " << input_file_name << endl;
  cout << "Nome do arquivo de saida .txt! -> " << output_file_name << endl;

  cout << "O grafo sera" << ((orientado == "0") ? " não orientado\n" : " orientado\n");
  cout << "O grafo sera com peso nas arestas? R: -> " << ((pesoAresta == "0") ? " não!\n" : "sim!\n");
  cout << "O grafo sera com peso nos vertices? R: -> " << ((pesoVertices == "0") ? " não!\n" : "sim!\n");

  return 0;
}