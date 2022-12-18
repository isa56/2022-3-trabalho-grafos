#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

typedef struct HeuristicNode
{
    Node *node;
    double ratio;
    bool visited;
} HeuristicNode;

void calculateRatio(vector<Node> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        // calcular o ratio
        double ratio = nodes[i].getDegree() / nodes[i].getNodeWeight();
        nodes[i].setRatio(ratio);
    }
}

Node heuristic(vector<Node> nodes)
{
    calculateRatio(nodes);
}

void markNeighborsAsVisited(Node *node)
{
    // iterar sobre os vizinhos do nó
    Edge *neighborEdge = node->getFirstEdge();
    Node *neighbor = neighborEdge->getDestiny();
    while (neighbor != nullptr)
    {
        // marcar como visitado
        neighbor->setVisited(true);
        neighborEdge = neighborEdge->getNextEdge();
        neighbor = neighborEdge->getDestiny();
    }
}

bool checkIfSolutionComplete(vector<Node> nodes)
{
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

void fetchAllNodes(vector<Node> *possibleNodes, Graph *graph)
{
    // iterar sobre os nós do grafo
    Node *node = graph->getFirstNode();
    while (node != nullptr)
    {
        // criar um HeuristicNode e adicionar ao vector
        node->setRatio(0);
        node->setVisited(false);
        possibleNodes->push_back(node);
        node = node->getNextNode();
    }
}

void beginGreedyAlgorithm(Graph *graph)
{
    clearVisitedAndRatio(graph);
    bool solutionComplete = false;
    vector<Node> solution;
    vector<Node> possibleNodes;
    // TODO: preenche o vector de possíveis nós com todos os nós do grafo
    fetchAllNodes(&possibleNodes, graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove da solution

    /*
        O que a gente precisa fazer?
        Precisamos ter a referencia de todos os nós que já foram visitados

        Possíveis soluções?
        1 - Criar um atributo visited no Node e trabalhar direto com ele ao inves do HeuristicNode
        Problemas: todas as vezes que for rodar o guloso precisa setar o visited de todos os nós como 0 e não temos propriedade ratio para fazer a lógica da razão.
    */

    do
    {
        Node node = heuristic(possibleNodes);
        solution.push_back(node);
        markNeighborsAsVisited(&node);
        // possibleNodes.erase(possibleNodes.begin());
    } while (!possibleNodes.empty() || !checkIfSolutionComplete(possibleNodes)); // definir condicao de parada para solução completa
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
