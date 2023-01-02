#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include "Graph.h"
#include "random.h"
#include "SortingMethods.h"
#include <limits.h>

using namespace std;

void calculateRatio(vector<Node *> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getDegree() == 0)
        {
            nodes[i]->setRatio(0);
            continue;
        }
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
// Gera um número aleatório de 0 ate a 'porcentagem' de alpha em node
int RandomNumberGeneration(float alpha, int sizeNode)
{
    int range = ((float)alpha * sizeNode);
    if (range < 1) // Para nunca tentar difidir por 0
        range = 1;
    int rand = xrandomRange(0, (short)INT_MAX);
    int random = (rand % range);
    return random;
}

/*Node *randomizedReactiveHeuristic(vector<Node *> nodes, float alpha)
{}*/

// WIP: implementar o algoritmo guloso randomizado
Node *randomizedAdaptativeHeuristic(vector<Node *> nodes, float alpha)
{
    calculateRatio(nodes);
    mergeSort(&nodes, 0, (nodes.size() - 1));
    int index = RandomNumberGeneration(alpha, nodes.size());
    return nodes[index];
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
    Node *newNode;
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

void beginGreedyAlgorithm(Graph *graph, ofstream &output_file)
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
    output_file << "Solucao: ";
    for (int i = 0; i < solution.size(); i++)
    {
        cout << solution[i]->getId() << " ";
        output_file << solution[i]->getId() << " ";
        if (i % 20 == 0 && i >= 20)
            output_file << endl;
    }
    output_file << "\nA solução tem " << solution.size() << " vertices";
    cout << endl;
}

vector<Node *> beginRandomizedAdaptativeAlgorithm(Graph *graph, float alpha)
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
    // cout << "Solucao:" << endl;
    // for (int i = 0; i < solution.size(); i++)
    // {
    //     cout << solution[i]->getId() << " ";
    // }
    // cout << endl;

    return solution;
}

void beginRandomReactiveAlgorithm(Graph *graph)
{
    vector<Node *> solution, solutionAux;
    vector<float> alphas{0.05, 0.10, 0.15, 0.30, 0.50};
    vector<float> solutionbest;
    int blockSize = 250;
    bool solutionComplete = false;

    vector<Node *> possibleNodes = fetchAllNodes(graph);
    // TODO: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes
    clearVisitedAndRatio(graph);
    for (size_t i = 0; i < alphas.size(); i++)
    {
        do
        {
            Node *node = randomizedAdaptativeHeuristic(possibleNodes, alphas[i]);
            auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));
            solution.push_back(node);
            possibleNodes.erase(nodePosition);
            markNeighborsAsVisited(graph, node);
            solutionComplete = (isSolutionComplete(possibleNodes)) || (possibleNodes.empty());
        } while (solutionComplete == false); // definir condicao de parada para solução completa
        if (i == 0)
            solutionAux = solution;
        if (solution.size() < solutionAux.size())
            solutionAux = solution;
    }

    clearVisitedAndRatio(graph);

    // DONE: imprimir a solução
    // cout << "Solucao:" << endl;
    // for (int i = 0; i < solution.size(); i++)
    // {
    //     cout << solution[i]->getId() << " ";
    // }
    // cout << endl;
}