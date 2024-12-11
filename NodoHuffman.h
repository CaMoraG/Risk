#ifndef _NodoHuffman_H_
#define _NodoHuffman_H_

#include <iostream>
#include <string>

class NodoHuffman {
protected:
  int freq;
  char car;
  NodoHuffman *izq;
  NodoHuffman *der;

public:
  NodoHuffman();
  NodoHuffman(int nfreq);
  NodoHuffman(char ncar, int nfreq);
  ~NodoHuffman();
  int obtenerFreq();
  void fijarFreq(int nfreq);
  char obtenerCar();
  void fijarCar(char ncar);
  NodoHuffman *obtenerHijoIzq();
  NodoHuffman *obtenerHijoDer();
  void fijarHijoIzq(NodoHuffman *izq);
  void fijarHijoDer(NodoHuffman *der);
  bool esHoja();
  void preOrden();
  void inOrden();
  void posOrden();
  bool operator<(const NodoHuffman& e) const {
    return freq < e.freq;
  }
  bool operator>(const NodoHuffman& e) const {
    return freq > e.freq;
  }
};

#include "NodoHuffman.hxx"

#endif