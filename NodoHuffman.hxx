#include "NodoHuffman.h"
#include <iostream>

NodoHuffman::NodoHuffman(){
  this->izq=NULL;
  this->der=NULL;
}
NodoHuffman::NodoHuffman(int nfreq){
  this->freq=nfreq;
  this->izq=NULL;
  this->der=NULL;
}
NodoHuffman::NodoHuffman(char ncar, int nfreq){
  this->car=ncar;
  this->freq=nfreq;
  this->izq=NULL;
  this->der=NULL;
}
NodoHuffman::~NodoHuffman(){
  if(this->izq!=NULL){
    delete this->izq;
    this->izq=NULL;
  }
  if(this->der!=NULL){
    delete this->der;
    this->der=NULL;
  }
}
bool NodoHuffman::esHoja(){
  return this->izq==NULL && this->der==NULL;
}
int NodoHuffman::obtenerFreq(){
  return this->freq;
}
void NodoHuffman::fijarFreq(int nfreq){
  this->freq=nfreq;
}
char NodoHuffman::obtenerCar(){
  return this->car;
}
void NodoHuffman::fijarCar(char ncar){
  this->car=ncar;
}
NodoHuffman* NodoHuffman::obtenerHijoIzq(){
  return this->izq;
}
NodoHuffman* NodoHuffman::obtenerHijoDer(){
  return this->der;
}
void NodoHuffman::fijarHijoIzq(NodoHuffman* nizq){
  this->izq=nizq;
}
void NodoHuffman::fijarHijoDer(NodoHuffman* nder){
  this->der=nder;
}
void NodoHuffman::preOrden(){
  std::cout<<this->car<<": "<<this->freq<<" | ";
  if(this->izq!=NULL){
    this->izq->preOrden();
  }
  if(this->der!=NULL){
    this->der->preOrden();
  }
}

void NodoHuffman::posOrden(){
  if(this->izq!=NULL){
    this->izq->posOrden();
  }
  if(this->der!=NULL){
    this->der->posOrden();
  }
  std::cout<<this->car<<": "<<this->freq<<" | ";
}

void NodoHuffman::inOrden(){
  if(this->izq!=NULL){
    this->izq->inOrden();
  }
  std::cout<<this->car<<": "<<this->freq<<" | ";
  if(this->der!=NULL){
    this->der->inOrden();
  }
}