#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;

typedef struct HeuristicNode
{
    Node *node;
    double ratio;
    bool visited;
} HeuristicNode;

HeuristicNode heuristic(vector<HeuristicNode> nodes)
{
}

void markNeighborsAsVisited(HeuristicNode heuristicNode)
{
    // iterar sobre os vizinhos do nó
    Node *node = heuristicNode.node;
    while (node->getLastEdge() != NULL)
    {
    }
    // if (heuristicNode.visited == false) {
    // heuristicNode.visited = true;
    // }
}

bool checkIfSolutionComplete(vector<HeuristicNode> nodes)
{
    // iterar sobre o vector
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].visited == false)
        {
            return false;
        }
    }
    return true;
}

void beginGreedyAlgorithm()
{
    bool solutionComplete = false;
    vector<HeuristicNode> solution;
    vector<HeuristicNode> possibleNodes;
    // inclui todos os nós que não podem ser "evitados" na solution
    do
    {
        HeuristicNode node = heuristic(possibleNodes);
        solution.push_back(node);
        markNeighborsAsVisited(node);
        // possibleNodes.erase(possibleNodes.begin());
    } while (!possibleNodes.empty() || !checkIfSolutionComplete(possibleNodes)); // definir condicao de parada para solução completa
}
