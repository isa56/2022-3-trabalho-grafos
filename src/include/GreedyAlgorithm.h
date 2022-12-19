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
        if (nodes[i].isVisited())
        {
            
        }
        nodes[i].setRatio(ratio);
    }
}

Node heuristic(vector<Node> nodes)
{
    calculateRatio(nodes);
    // ordena de forma decrescente:
}

void markNeighborsAsVisited(Node *node)
{
    node->setVisited(true);
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

vector<Node> fetchAllNodes(Graph *graph)
{
    // iterar sobre os nós do grafo
    vector<Node> possibleNodes;
    Node *node = graph->getFirstNode();
    Node &newNode = *node;
    while (node != nullptr)
    {
        // criar um HeuristicNode e adicionar ao vector
        possibleNodes.push_back(newNode);
        node = node->getNextNode();
        newNode = *node;
    }
    return possibleNodes;
}

void beginGreedyAlgorithm(Graph *graph)
{
    clearVisitedAndRatio(graph);
    bool solutionComplete = false;
    vector<Node> solution;
    // DONE?: preenche o vector de possíveis nós com todos os nós do grafo
    vector<Node> possibleNodes = fetchAllNodes(graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes

    do
    {
        Node node = heuristic(possibleNodes);
        solution.push_back(node);
        markNeighborsAsVisited(&node);
        // possibleNodes.erase(possibleNodes.begin());
    } while (!possibleNodes.empty() || !checkIfSolutionComplete(possibleNodes)); // definir condicao de parada para solução completa
    clearVisitedAndRatio(graph);
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
