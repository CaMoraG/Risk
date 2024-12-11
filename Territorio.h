#ifndef _Territorio_H_
#define _Territorio_H_

#include <string>
#include <list>

using namespace std;

class Territorio {
private:
    string nombre;
    string continente;
    list<int> vecinos;
    int guarnicion = 0;
    int idjugador = 0;
    int id;
public:
    Territorio(){}
    Territorio(string nombre, string continente, list<int> vecinos, int id);
    void setJugador(int id);
    string getNombre();
    string getContinente();
    list<int> getVecinos();
    int getGuarnicion();
    void setGuarnicion(int nguarnicion);
    int getJugador();
    int getId();
    void agregarTropas(int tropas);
    void quitarTropas(int tropas);
};

#include "Territorio.hxx"

#endif 