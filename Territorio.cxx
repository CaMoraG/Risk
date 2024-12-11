#include "Territorio.h"

using namespace std;

Territorio::Territorio(int id, string nombre, string continente, list<int> vecinos)
: id (id), nombre(nombre), continente(continente), vecinos(vecinos){}

int Territorio::getID(){
    return id; 
}

void Territorio::setJugador(int id){
    idjugador = id;
}

string Territorio::getNombre(){
    return nombre;
}
string Territorio::getContinente(){
    return continente;
}
list<int> Territorio::getVecinos(){
    return vecinos;
}
int Territorio::getGuarnicion(){
    return guarnicion;
}
void Territorio::setGuarnicion(int nguarnicion){
    guarnicion = nguarnicion;
}
int Territorio::getJugador(){
    return idjugador;
}
void Territorio::agregarTropas(int tropas){
    guarnicion += tropas;
}
void Territorio::quitarTropas(int tropas){
    guarnicion -= tropas;
}
