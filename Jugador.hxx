#include "Jugador.h"

using namespace std;

void Jugador::setId(int nid){
    id = nid;
}

int Jugador::getId(){
    return id;
}
string Jugador::getnombre(){
    return nombre;
}
void Jugador::setnombre(string nnombre){
    nombre = nnombre;
}
list<int> Jugador::getPosesiones(){
    return posesiones;
}
void Jugador::agregarPosesion(int id){
    posesiones.push_back(id);
    if(posesiones.size()>=2){
        posesiones.sort();
    }
}
void Jugador::eliminarPosesion(int id){
    list<int> nlista;
    if(!posesiones.empty()){
        for(int it : posesiones){
            if(it!=id){
                nlista.push_back(it);
            }
        }
        posesiones = nlista;
    }
}
int Jugador::getTropas(){
    return tropas;
}
void Jugador::setTropas(int ntropas){
    tropas = ntropas;
}
void Jugador::quitarTropas(int ntropas){
    tropas -= ntropas;
}
int Jugador::nuevasTropasT(){
    return posesiones.size()/3;
}

