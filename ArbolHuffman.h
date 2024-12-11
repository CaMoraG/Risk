#ifndef _ArbolHuffman_H_
#define _ArbolHuffman_H_

#include "NodoHuffman.h"
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <fstream>
#include <bitset>

class ArbolHuffman {
protected:
  NodoHuffman *raiz;

  std::string codigo(NodoHuffman* nodo, char car, std::string cod);
public:
  ArbolHuffman();
  ArbolHuffman(NodoHuffman* nraiz);
  ~ArbolHuffman();
  int freqRaiz();
  NodoHuffman *obtenerRaiz();
  void fijarRaiz(NodoHuffman *n_raiz);
  bool esVacio();
  void preOrden();
  void inOrden();
  void posOrden();
  void nivelOrden();
  void crearArbol(std::vector<NodoHuffman*> nodos);
  std::string codificar (std::string texto, std::string nomarch);
  std::string decodificar (std::string codificacion, int caracs);
  void generarArchivo(std::unordered_map<char, int> frecs, std::string codificacion, int caracs, std::string nomarch);
  std::string leerArchivo(std::string nomarch);
};

#include "ArbolHuffman.hxx"

#endif