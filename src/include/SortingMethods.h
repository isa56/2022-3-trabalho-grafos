#include <iostream>
#include <algorithm>
#include <vector>

#include "Node.h"

using namespace std;

template <typename T>
void swap(Node *a, Node *b)
{
  Node temp = *a;
  *a = *b;
  *b = temp;
}

void merge(vector<Node *> *v, int left, int right, int mid)
{
  // Pega as posições iniciais
  int firstSubVector = mid - left + 1;
  int secondSubVector = right - mid;

  // cria os novos vetores
  vector<Node *> leftVector, rightVector;

  // preenche os vetores
  for (int i = 0; i < firstSubVector; i++)
  {
    leftVector.push_back((*v)[left + i]);
  }

  for (int i = 0; i < secondSubVector; i++)
  {
    rightVector.push_back((*v)[mid + 1 + i]);
  }

  // inicia o merge
  int indexOfFirstSubVector = 0;
  int indexOfSecondSubVector = 0;
  int indexOfMergedVector = left;

  // compara os elementos dos vetores e os ordena de forma decrescente (maior ratio primeiro)
  while (indexOfFirstSubVector < firstSubVector && indexOfSecondSubVector < secondSubVector)
  {
    if (leftVector[indexOfFirstSubVector]->getRatio() >= rightVector[indexOfSecondSubVector]->getRatio())
    {
      (*v)[indexOfMergedVector] = leftVector[indexOfFirstSubVector];
      indexOfFirstSubVector++;
    }
    else
    {
      (*v)[indexOfMergedVector] = rightVector[indexOfSecondSubVector];
      indexOfSecondSubVector++;
    }
    indexOfMergedVector++;
  }

  // copia os elementos restantes de cada vetor
  while (indexOfFirstSubVector < firstSubVector)
  {
    (*v)[indexOfMergedVector] = leftVector[indexOfFirstSubVector];
    indexOfFirstSubVector++;
    indexOfMergedVector++;
  }

  while (indexOfSecondSubVector < secondSubVector)
  {
    (*v)[indexOfMergedVector] = rightVector[indexOfSecondSubVector];
    indexOfSecondSubVector++;
    indexOfMergedVector++;
  }

  // limpa os vetores:
  leftVector.clear();
  rightVector.clear();
}

void mergeSort(vector<Node *> *v, int begin, int end)
{
  if (begin >= end)
  {
    return;
  }

  int middle = begin + (end - begin) / 2;
  mergeSort(v, begin, middle);
  mergeSort(v, middle + 1, end);
  merge(v, begin, end, middle);
}