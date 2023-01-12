#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <cstdlib>
#include <climits>

#include "Graph.h"
#include "SortingMethods.h"

using namespace std;

float ALPHAS[] = {0.05, 0.10, 0.15, 0.30, 0.50};

typedef struct
{
    float alpha;
    float probability;
    int averageSolution;
    int totalWeight;
    int iterationsNumber;
} reactiveAlpha;

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

int random(int max)
{
    return (rand() % max);
}

// Gera um número aleatório de 0 ate a 'porcentagem' de alpha em node
int RandomNumberGeneration(float alpha, int sizeNode)
{
    int maxRange = ((float)alpha * sizeNode);
    int generatedNumber = random(maxRange);

    return generatedNumber;
}

int findTotalWeight(vector<Node *> nodes)
{
    int total = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        total = total + nodes[i]->getNodeWeight();
    }
    return total;
}

// DONE: implementar o algoritmo guloso randomizado
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

float updateProbabilityList(vector<reactiveAlpha> *alphaList, float bestQuality)
{
    // qualidade = peso
    // valor das i qualidades = ((melhor qualidade) / media das qualidades do alfai) elevado a 10
    float totalQuality = 0;
    vector<float> qualities = {0, 0, 0, 0, 0};

    for (int i = 0; i < (*alphaList).size(); i++)
    {
        qualities[i] = pow(((bestQuality) / ((float)(*alphaList)[i].averageSolution)), 10);
        totalQuality += qualities[i];
        if (qualities[i] < bestQuality)
        {
            bestQuality = qualities[i];
        }
    }

    for (int i = 0; i < (*alphaList).size(); i++)
    {
        (*alphaList)[i].probability = (qualities[i] / (float)totalQuality);
    }

    return bestQuality;
}

float selectAlpha(vector<reactiveAlpha> alphaList)
{
    int generatedNumber = random(alphaList.size());
    return alphaList[generatedNumber].alpha;
}

void updateAverageList(vector<reactiveAlpha> *alphas, int weight, float alpha)
{
    // DOING: Att a lista

    for (int i = 0; i < alphas->size(); i++)
    {
        if ((*alphas)[i].alpha == alpha)
        {
            (*alphas)[i].iterationsNumber++;
            (*alphas)[i].totalWeight += weight;
            (*alphas)[i].averageSolution = (((float)(*alphas)[i].totalWeight) / ((*alphas)[i].iterationsNumber));
        }
    }
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

vector<Node *> beginRandomizedReactiveAlgorithm(Graph *graph, int blockSize, int iterationCount, int &bestSolutionWeight, std::chrono::duration<double> &bestSolutionTime)
{

    bool solutionComplete = false;
    float alpha = 0, bestQuality = (float)INT_MAX;
    int bestWeightSolution = INT_MAX, weight = 0;
    float bestAlpha = 0.05;

    vector<Node *> solutionAux, bestSolution;
    vector<Node *> possibleNodes;

    vector<reactiveAlpha> alphaList;

    for (int i = 0; i < 5; i++)
    {
        reactiveAlpha a;
        a.alpha = ALPHAS[i];
        a.averageSolution = INT_MAX;
        a.probability = 0;
        a.iterationsNumber = 0;
        a.totalWeight = 0;
        alphaList.push_back(a);
    }

    Metrics p;
    Setup_metrics(&p);
    // TODO: loop de testes deve ser colocado aqui?

    for (size_t i = 0; i < iterationCount; i++)
    {
        auto t0 = std::chrono::high_resolution_clock::now();

        possibleNodes.clear();
        solutionAux.clear();
        possibleNodes = fetchAllNodes(graph);

        if (i % blockSize == 0)
        {
            bestQuality = updateProbabilityList(&alphaList, bestQuality);
        }
        alpha = selectAlpha(alphaList);

        do
        {
            Node *node = randomizedAdaptativeHeuristic(possibleNodes, alpha);

            auto nodePosition = (find(possibleNodes.begin(), possibleNodes.end(), node));

            solutionAux.push_back(node);
            markNeighborsAsVisited(graph, node);
            possibleNodes.erase(nodePosition);

            solutionComplete = (isSolutionComplete(possibleNodes)) || (possibleNodes.empty());

        } while (solutionComplete == false); // definir condicao de parada para solução completa

        weight = findTotalWeight(solutionAux);

        updateAverageList(&alphaList, weight, alpha);

        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = t1 - t0;

        if (i == 0)
        {
            bestSolution = solutionAux;
            bestSolutionWeight = weight;
            bestSolutionTime = delta;
        }

        if (weight < bestSolutionWeight)
        {
            bestSolution = solutionAux;
            bestSolutionWeight = weight;
            bestSolutionTime = delta;
            bestAlpha = alpha;
        }

        clearVisitedAndRatio(graph);
    }
    cout << "Melhor Alfa" << bestAlpha << endl;
    return bestSolution;
}