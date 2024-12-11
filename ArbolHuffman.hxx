#include "ArbolHuffman.h"

ArbolHuffman::ArbolHuffman(){
  this->raiz=NULL;
}
ArbolHuffman::ArbolHuffman(NodoHuffman* nraiz){
  this->raiz=nraiz;
}
ArbolHuffman::~ArbolHuffman(){
  delete this->raiz;
  this->raiz=NULL;
}
int ArbolHuffman::freqRaiz(){
  return this->raiz->obtenerFreq();
}
NodoHuffman *ArbolHuffman::obtenerRaiz(){
  return this->raiz;
}
void ArbolHuffman::fijarRaiz(NodoHuffman *n_raiz){
  this->raiz=n_raiz;
}
bool ArbolHuffman::esVacio(){
  return this->raiz==NULL;
}
void ArbolHuffman::preOrden(){
  if(!this->esVacio()){
    this->raiz->preOrden();
  }
}
void ArbolHuffman::inOrden(){
  if(!this->esVacio()){
    this->raiz->inOrden();
  }
}
void ArbolHuffman::posOrden(){
  if(!this->esVacio()){
    this->raiz->posOrden();
  }
}
void ArbolHuffman::nivelOrden(){
  
}

struct cmpNodos{
  bool operator()(NodoHuffman * a, NodoHuffman * b){
    return a->obtenerFreq()>b->obtenerFreq();
  }
};

void ArbolHuffman::crearArbol(std::vector<NodoHuffman*> nodos){
  std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, cmpNodos> heap;
  for(int i = 0; i<nodos.size(); i++){
    heap.push(nodos[i]);
  }

  while (heap.size()>1){
    NodoHuffman* nodoz = new NodoHuffman;
    nodoz->fijarHijoIzq(heap.top());
    heap.pop();
    nodoz->fijarHijoDer(heap.top());
    heap.pop();
    nodoz->fijarFreq(nodoz->obtenerHijoIzq()->obtenerFreq() + nodoz->obtenerHijoDer()->obtenerFreq());
    nodoz->fijarCar('@');
    heap.push(nodoz);
  }

  this->raiz=heap.top();
}

std::string ArbolHuffman::codigo(NodoHuffman* nodo, char car, std::string cod){
  if(this->esVacio()){
    return "";
  }

  if(nodo!=NULL){
    if(nodo->esHoja() && nodo->obtenerCar()==car){
      return cod;
    }
    std::string codizq = codigo(nodo->obtenerHijoIzq(), car, cod+"0");
    std::string codder =  codigo(nodo->obtenerHijoDer(), car, cod+"1");

    if(codizq.empty()){
      return codder;
    }else{
      return codizq;
    }
  }
  return "";
}

std::string ArbolHuffman::decodificar (std::string codificacion, int caracs){
  if(this->esVacio()){
    return "";
  }

  std::string decodificado = "";
  std::string cod = "";
  NodoHuffman* nodo = this->raiz;

  for(int i = 0; caracs!=0;i++){
    if(nodo!=NULL){
      if(nodo->esHoja()){
        decodificado+= nodo->obtenerCar();
        caracs--;
        nodo = this->raiz;
        i--;
      }else{
        if(codificacion[i]=='0'){
          nodo = nodo->obtenerHijoIzq();
        }else{
          nodo = nodo->obtenerHijoDer();
        }
      }
    }
  }

  return decodificado;
}


void ArbolHuffman::generarArchivo(std::unordered_map<char, int> frecs, std::string codificacion, int caracs, std::string nomarch){
  std::ofstream archivo(nomarch, std::ios::binary);
  if (!archivo.is_open()) {
    std::cerr << "No se pudo abrir el archivo" <<std::endl; 
    return;
  }

  int16_t numnodos = frecs.size();
  archivo.write(reinterpret_cast<char *>(&numnodos), sizeof(numnodos));

  std::unordered_map<char, int>::iterator mapit;
  int8_t car;
  int64_t freq;
  for(mapit = frecs.begin(); mapit != frecs.end(); mapit++){
    car = ((*mapit).first);
    freq = ((*mapit).second);
    archivo.write(reinterpret_cast<char *>(&car), sizeof(car));
    archivo.write(reinterpret_cast<char *>(&freq), sizeof(freq));
  }

  int64_t numcaracs = caracs;
  archivo.write(reinterpret_cast<char *>(&numcaracs), sizeof(numcaracs));

  while((codificacion.size()%8)!=0){
    codificacion+="0";
  }

  for(int i = 0; i < codificacion.size()/8; i++){
    std::string byteStr = codificacion.substr(i * 8, 8);
    unsigned char byte = std::bitset<8>(byteStr).to_ulong();
    archivo.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
  }

  archivo.close();
}

std::string ArbolHuffman::leerArchivo(std::string nomarch){
  std::ifstream archivo(nomarch, std::ios::binary);
  if (!archivo.is_open()) {
    std::cerr << "No se pudo abrir el archivo" <<std::endl; 
    return "";
  }

  int16_t numnodos;
  archivo.read(reinterpret_cast<char *>(&numnodos), sizeof(numnodos));

  std::vector<NodoHuffman*> nodos;
  int8_t car;
  int64_t freq;
  for(int i = 0; i<numnodos; i++){
    NodoHuffman* mapnodo = new NodoHuffman;
    archivo.read(reinterpret_cast<char *>(&car), sizeof(car));
    archivo.read(reinterpret_cast<char *>(&freq), sizeof(freq));
    mapnodo->fijarCar(car);
    mapnodo->fijarFreq(freq);
    nodos.push_back(mapnodo);
  }

  int64_t numcaracs;
  archivo.read(reinterpret_cast<char *>(&numcaracs), sizeof(numcaracs));

  std::string codificacion = "";
  char byteChar;
  while (archivo.read(&byteChar, sizeof(byteChar)) ) {
      std::bitset<8> byteBits(byteChar);
      codificacion+=byteBits.to_string();
  }

  archivo.close();
  crearArbol(nodos);
  return decodificar(codificacion, numcaracs);
}

std::string ArbolHuffman::codificar (std::string texto, std::string nomarch){
  std::unordered_map<char, int> frecs;
  for (int i = 0; i<texto.size();i++) {
		frecs[texto[i]]++;
	}

  std::vector<NodoHuffman*> nodos;
  std::unordered_map<char, int>::iterator mapit;
  for(mapit = frecs.begin(); mapit != frecs.end(); mapit++){
    NodoHuffman* mapnodo = new NodoHuffman;
    mapnodo->fijarCar((*mapit).first);
    mapnodo->fijarFreq((*mapit).second);
    nodos.push_back(mapnodo);
  }

  crearArbol(nodos);
  std::string codificacion = "";
  for(int i = 0; i<texto.size();i++){
    std::string cod = codigo(this->raiz, texto[i], "");
    codificacion+=cod;
  }
  generarArchivo(frecs, codificacion, texto.size(), nomarch);
  return codificacion;
}
