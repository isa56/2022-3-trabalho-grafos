#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include "Graph.h"
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

// Gera um número aleatório de 0 ate a 'porcentagem' de alpha em node
int RandomNumberGeneration(float alpha, int sizeNode)
{
    int maxRange = ((float)alpha * sizeNode);
    int generatedNumber = rand() % maxRange;

    cout << "Max range: " << maxRange << endl;
    cout << "Generated number: " << generatedNumber << endl;

    return generatedNumber;
}

// int findTotalWeight(vector<Node *> nodes)
// {
//     int total = 0;
//     for (int i = 0; i < nodes.size(); i++)
//     {
//         total = total + nodes[i]->getNodeWeight();
//     }
//     return total;
// }

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

void updateProbabilityList(vector<float> *probabilities, vector<float> averages, vector<Node *> sol)
{
    vector<float> qualities;
    float quality, totalQuality = 0;

    for (int i = 0; i < sol.size(); i++)
    {

        totalQuality += quality;
    }

    for (int i = 0; i < sol.size(); i++)
    {
        (*probabilities)[i] = (qualities[i] / (float)totalQuality);
    }
}

float selectAlpha(vector<float> probabilities, vector<float> alphas)
{
    float alpha;

    return alpha;
}

void updateAverageList(vector<float> averageList, vector<Node *> solutionAux, float alpha)
{
}

vector<Node *> beginGreedyAlgorithm(Graph *graph, ofstream &output_file)
{
    // auto nodePosition = -1;
    bool solutionComplete = false;
    vector<Node *> solution;
    // DONE?: preenche o vector de possíveis nós com todos os nós do grafo
    vector<Node *> possibleNodes = fetchAllNodes(graph);

    // DONE: inclui todos os nós que não podem ser "evitados" na solution e remove do possibleNodes
    clearVisitedAndRatio(graph);

    do
    {
        Node *node = heuristic(possibleNodes);

        auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));

        solution.push_back(node);

        markNeighborsAsVisited(graph, node);

        possibleNodes.erase(nodePosition);

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
    return solution;
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
    } while (solutionComplete == false);

    clearVisitedAndRatio(graph);

    return solution;
}

// vector<Node *> beginRandomizedReactiveAlgorithm(Graph *graph)
// {
//     vector<Node *> bestSolution, solutionAux;

//     vector<float> alphas{0.05, 0.10, 0.15, 0.30, 0.50};
//     vector<float> alphaProbability{0, 0, 0, 0, 0};
//     vector<float> averageSolutionQualityPerAlpha{0, 0, 0, 0, 0};

//     int blockSize = 250;
//     int iterationCount = 2500;
//     int bestSolutionWeight = 0;
//     bool solutionComplete = false;
//     float alpha = 0;

//     vector<Node *> possibleNodes;

//     // TODO: loop de testes deve ser colocado aqui?

//     for (size_t i = 0; i < iterationCount; i++)
//     {

//         possibleNodes.clear();
//         solutionAux.clear();
//         possibleNodes = fetchAllNodes(graph);

//         if (i % blockSize == 0)
//         {
//             updateProbabilityList(&alphaProbability, averageSolutionQualityPerAlpha, bestSolution);
//         }

//         alpha = selectAlpha(alphaProbability, alphas);

//         do
//         {
//             Node *node = randomizedAdaptativeHeuristic(possibleNodes, alphas[i]);

//             auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));

//             solutionAux.push_back(node);

//             markNeighborsAsVisited(graph, node);

//             possibleNodes.erase(nodePosition);

//             solutionComplete = (isSolutionComplete(possibleNodes)) || (possibleNodes.empty());

//         } while (solutionComplete == false); // definir condicao de parada para solução completa

//         updateAverageList(averageSolutionQualityPerAlpha, solutionAux, alpha);

//         if (i == 0)
//         {
//             bestSolution = solutionAux;
//             bestSolutionWeight = findTotalWeight(bestSolution);
//         }

//         if (bestSolutionWeight < findTotalWeight(solutionAux))
//         {
//             bestSolution = solutionAux;
//             bestSolutionWeight = findTotalWeight(bestSolution);
//         }

//         clearVisitedAndRatio(graph);
//     }

//     return bestSolution;
// }