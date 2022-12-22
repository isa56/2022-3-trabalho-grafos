#include <iostream>
#include <vector>
#include "Graph.h"
#include "SortingMethods.h"
using namespace std;

void calculateRatio(vector<Node> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        // calcular o ratio
        double ratio = nodes[i].getDegree() / nodes[i].getNodeWeight();
        // problema: se o nó já foi visitado, o ratio deve ser reduzido pela metade, mas isso será feito todas as vezes que passarmos por aqui
        if (nodes[i].isVisited())
        {
            ratio *= 0.5;
        }
        nodes[i].setRatio(ratio);
    }
}

// WIP: implementar o algoritmo guloso randomizado
Node randomizedHeuristic(vector<Node> nodes, float alpha)
{
    calculateRatio(nodes);
    mergeSort(nodes, 0, (nodes.size() - 1));
    int index = (int)(alpha * nodes.size());
    return nodes[index];
}

Node heuristic(vector<Node> nodes)
{
    cout << "Calculando ratio..." << endl;
    calculateRatio(nodes);
    cout << "Ordenando..." << endl;
    mergeSort(nodes, 0, (nodes.size() - 1)); // ordenar o vector de nós por ratio
    return nodes[0];                         // retornar o nó com maior ratio
}

void markNeighborsAsVisited(Graph *graph, Node *node)
{
    cout << "Marcando vizinhos como visitados..." << endl;
    node->setVisited(true);
    // iterar sobre os vizinhos do nó
    Edge *neighborEdge = node->getFirstEdge();
    Node *neighbor = graph->getNode(neighborEdge->getDestinyId());
    while (neighbor != nullptr)
    {
        // marcar como visitado
        neighbor->setVisited(true);
        neighborEdge = neighborEdge->getNextEdge();
        neighbor = graph->getNode(neighborEdge->getDestinyId());
    }
}

bool isSolutionComplete(vector<Node> nodes)
{
    cout << "Verificando se a solução está completa..." << endl;
    // iterar sobre o vector
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].isVisited() == false)
        {
            return false;
        }
    }
    return true;
}

vector<Node> fetchAllNodes(Graph *graph)
{
    // iterar sobre os nós do grafo
    vector<Node> possibleNodes;
    Node *node = graph->getFirstNode();
    Node &newNode = *node;
    while (node != nullptr)
    {
        cout << "Adicionando no" << endl;
        possibleNodes.push_back(newNode);   // problema esta aqui
        cout << "Pega proximo no" << endl;
        node = node->getNextNode();
        newNode = *node;
        cout << "Criando novo no: " << newNode.getId() << endl;
    }
    return possibleNodes;
}

void clearVisitedAndRatio(Graph *graph)
{
    Node *node = graph->getFirstNode();
    while (node != nullptr)
    {
        node->setVisited(false);
        node->setRatio(0);
        node = node->getNextNode();
    }
}

void beginGreedyAlgorithm(Graph *graph)
{
    clearVisitedAndRatio(graph);
    bool solutionComplete = false;
    vector<Node> solution;
    // DONE?: preenche o vector de possíveis nós com todos os nós do grafo
    vector<Node> possibleNodes = fetchAllNodes(graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes

    cout << "Iniciando o loop..." << endl;
    do
    {
        Node node = heuristic(possibleNodes);
        solution.push_back(node);
        markNeighborsAsVisited(graph, &node);
    } while (!possibleNodes.empty() || !isSolutionComplete(possibleNodes)); // definir condicao de parada para solução completa
    clearVisitedAndRatio(graph);
}
