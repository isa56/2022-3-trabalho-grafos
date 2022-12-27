#include <iostream>
#include <vector>
#include "Graph.h"
#include "SortingMethods.h"
using namespace std;

void calculateRatio(vector<Node *> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        // calcular o ratio
        float ratio = (nodes[i]->getDegree() / (float)(nodes[i]->getNodeWeight()));
        // problema: se o nó já foi visitado, o ratio deve ser reduzido pela metade, mas isso será feito todas as vezes que passarmos por aqui
        if (nodes[i]->isVisited())
        {
            ratio = ratio * 0.25;
        }
        nodes[i]->setRatio(ratio);
    }
}

// WIP: implementar o algoritmo guloso randomizado
Node *randomizedAdaptativeHeuristic(vector<Node *> nodes, float alpha)
{
    calculateRatio(nodes);
    mergeSort(&nodes, 0, (nodes.size() - 1));

    int firstIndex = ((alpha)*276);

    int index = (rand() % (firstIndex - 0 + 1) + 0);

    cout << "firstIndex" << firstIndex;
    cout << "index" << index;
    // return nodes[index];
}

// DONE: implementar o algoritmo guloso
Node *heuristic(vector<Node *> nodes)
{
    calculateRatio(nodes);
    mergeSort(&nodes, 0, (nodes.size() - 1)); // ordenar o vector de nós por ratio // erro aqui
    return nodes[0];                          // retornar o nó com maior ratio
}

void markNeighborsAsVisited(Graph *graph, Node *node)
{
    int neighborId;
    Node *neighbor;
    node->setVisited(true);
    // iterar sobre os vizinhos do nó
    Edge *neighborEdge = node->getFirstEdge();
    do
    {
        neighborId = neighborEdge->getDestinyId();
        neighbor = graph->getNode(neighborId);
        // marcar como visitado
        neighbor->setVisited(true);
        neighborEdge = neighborEdge->getNextEdge();
    } while (neighborEdge != nullptr);
}

bool isSolutionComplete(vector<Node *> nodes)
{
    // iterar sobre o vector
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->isVisited() == false)
        {
            return false;
        }
    }
    return true;
}

vector<Node *> fetchAllNodes(Graph *graph)
{
    // iterar sobre os nós do grafo
    vector<Node *> possibleNodes;
    Node *node = graph->getFirstNode();
    Node *newNode = node;
    do
    {
        newNode = node;
        possibleNodes.push_back(newNode);
        node = node->getNextNode();
    } while (node != nullptr);
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
    // auto nodePosition = -1;
    bool solutionComplete = false;
    vector<Node *> solution;
    // DONE?: preenche o vector de possíveis nós com todos os nós do grafo
    vector<Node *> possibleNodes = fetchAllNodes(graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes
    clearVisitedAndRatio(graph);

    do
    {
        Node *node = heuristic(possibleNodes);
        auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));
        solution.push_back(node);
        possibleNodes.erase(nodePosition);
        markNeighborsAsVisited(graph, node);
        solutionComplete = (isSolutionComplete(possibleNodes)) || (possibleNodes.empty());
    } while (solutionComplete == false); // definir condicao de parada para solução completa

    clearVisitedAndRatio(graph);

    // DONE: imprimir a solução
    cout << "Solucao:" << endl;
    for (int i = 0; i < solution.size(); i++)
    {
        cout << solution[i]->getId() << " ";
    }
    cout << endl;
}

void beginRandomizedAdaptativeAlgorithm(Graph *graph, float alpha)
{
    // auto nodePosition = -1;
    bool solutionComplete = false;
    vector<Node *> solution;
    // DONE?: preenche o vector de possíveis nós com todos os nós do grafo
    vector<Node *> possibleNodes = fetchAllNodes(graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes
    clearVisitedAndRatio(graph);

    do
    {
        Node *node = randomizedAdaptativeHeuristic(possibleNodes, alpha);
        auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));
        solution.push_back(node);
        possibleNodes.erase(nodePosition);
        markNeighborsAsVisited(graph, node);
        solutionComplete = (isSolutionComplete(possibleNodes)) || (possibleNodes.empty());
    } while (solutionComplete == false); // definir condicao de parada para solução completa

    clearVisitedAndRatio(graph);

    // DONE: imprimir a solução
    cout << "Solucao:" << endl;
    for (int i = 0; i < solution.size(); i++)
    {
        cout << solution[i]->getId() << " ";
    }
    cout << endl;
}
