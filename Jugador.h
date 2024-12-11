#ifndef _Jugador_H_
#define _Jugador_H_

#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Jugador {
private:
    int id;
    string nombre = "Sin jugador";
    list<int> posesiones;
    int tropas;
public:
    Jugador(){}
    void setId(int nid);
    int getId();
    void setnombre(string nombre);
    string getnombre();
    void agregarPosesion(int id);
    void eliminarPosesion(int id);
    list<int> getPosesiones();
    int getTropas();
    void quitarTropas(int ntropas);
    void setTropas(int ntropas);
    int nuevasTropasT();
};

#include "Jugador.hxx"

#endif 