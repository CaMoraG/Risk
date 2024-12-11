#ifndef _Grafo_H_
#define _Grafo_H_


#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <stack>
#include <queue>

template <class V>
class Grafo {
protected:
    std::vector<V> vertices;
    std::list<std::list<std::pair<V, int>>> aristas;
    bool dirigido;

    std::vector<std::vector<float>> matrizFW ();

public:
  Grafo();
  ~Grafo();

  int numVertices();
  int numAristas();
  void insertarVertice(V nvertice);
  void insertarArista(V orVertice, V destVertice, int costo);
  int buscarVertice(V vertice);
  int buscarArista(V orVertice, V destVertice);
  void eliminarVertice(V vertice);
  void eliminarArista(V orVertice, V destVertice);
  void recorridoPlano();
  void DFS(V vertice);
  void BFS(V vertice);
  std::vector<std::pair<int, int>> dijkstra(V vertice);
  void floydwarshall();
  void aristasde(V vertice);
  void printMatriz(std::vector<std::vector<float>> matriz, int n);
};

#include "Grafo.hxx"

#endif