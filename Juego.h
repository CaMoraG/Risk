#ifndef _Juego_H_
#define _Juego_H_

#include <string>
#include <list>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
#include "Jugador.h"
#include "Territorio.h"

using namespace std;

class Juego{
private:
    vector<Jugador> jugadores;
    vector<Territorio> territorios = {Territorio("Alaska", "America del norte", {1, 5, 31}, 0),
Territorio("Alberta", "America del norte", {0, 3, 5, 6, 8}, 1),
Territorio("America Central", "America del norte", {3, 8, 12}, 2),
Territorio("Estados Unidos Orientales", "America del norte", {2, 6, 7, 8}, 3),
Territorio("Groenlandia", "America del norte", {5, 6, 7, 14}, 4),
Territorio("Territorio Noroccidental", "America del norte", {0, 1, 4, 6, 7}, 5),
Territorio("Ontario", "America del norte", {1, 3, 4, 5, 7}, 6),
Territorio("Quebec", "America del norte", {3, 4, 5, 6}, 7),
Territorio("Estados Unidos Occidentales", "America del norte", {1, 2, 3, 6}, 8),
Territorio("Argentina", "America del sur", {10, 11}, 9),
Territorio("Brasil", "America del sur", {9, 11, 12, 24}, 10),
Territorio("Peru", "America del sur", {9, 10, 12}, 11),
Territorio("Venezuela", "America del sur", {2, 10, 11}, 12),
Territorio("Gran Bretana", "Europa", {14, 15, 16, 19}, 13),
Territorio("Islandia", "Europa", {4, 13, 16}, 14),
Territorio("Europa del norte", "Europa", {13, 16, 17, 18, 19}, 15),
Territorio("Escandinavia", "Europa", {13, 14, 15, 18}, 16),
Territorio("Europa del Sur", "Europa", {15, 18, 19, 22, 32}, 17),
Territorio("Ucrania", "Europa", {15, 16, 17, 26, 32, 36}, 18),
Territorio("Europa Occidental", "Europa", {13, 15, 18, 24}, 19),
Territorio("Congo", "Africa", {21, 24, 25}, 20),
Territorio("Africa Oriental", "Africa", {20, 22, 23, 25, 32}, 21),
Territorio("Egipto", "Africa", {17, 21, 24, 32}, 22),
Territorio("Madagascar", "Africa", {21, 25}, 23),
Territorio("Africa del Norte", "Africa", {10, 17, 19, 20, 21, 22}, 24),
Territorio("Africa del Sur", "Africa", {20, 21, 23}, 25),
Territorio("Afganistan", "Asia", {18, 27, 28, 32, 36}, 26),
Territorio("China", "Asia", {26, 28, 33, 34, 35, 36}, 27),
Territorio("India", "Asia", {26, 27, 32, 34}, 28),
Territorio("Irkutsk", "Asia", {31, 33, 35, 37}, 29),
Territorio("Japon", "Asia", {31, 33}, 30),
Territorio("Kamchatka", "Asia", {0, 29, 30, 33, 37}, 31),
Territorio("Medio Oriente", "Asia", {17, 18, 21, 22, 26, 28}, 32),
Territorio("Mongolia", "Asia", {31, 33, 35, 37} ,33),
Territorio("Siam", "Asia", {27, 28, 39}, 34),
Territorio("Siberia", "Asia", {27, 29, 33, 36, 37}, 35),
Territorio("Ural", "Asia", {18, 26, 27, 35}, 36),
Territorio("Yakutsk", "Asia", {29, 31, 36}, 37),
Territorio("Australia Oriental", "Australia", {40, 41}, 38),
Territorio("Indonesia", "Australia", {34, 40, 41}, 39),
Territorio("Nueva Guinea", "Australia", {38, 39}, 40),
Territorio("Australia Occidental", "Australia", {38, 39}, 41)
};
    //queue<Carta> mazo;
    bool inicializado = false;
    int turno;
    bool terminado = false;
    int numjugadores = 0;
    vector<int> lanzarDados(int n);
public:
    Juego(){}
    void setJugadores(vector<Jugador> &njugadores);
    vector<Jugador*> getJugadores();
    vector<Territorio*> getTerritorios();
    vector<Territorio> getCTerritorios();
    Jugador getJugador(int id);
    void setInicializado(bool tf);
    bool getInicializado();
    void setTerminado(bool tf);
    bool getTerminado();
    void setTurno(int nturno);
    int getTurno();
    int getNumjugadores();
    void setNumJugadores(int num);
    int getJugTropas(int id);
    int getTerritorioId(string nombre);
    int getJugadorId(string nombre);
    bool combate(int &atacante, int &defensor);
    //vector<Territorio&> asignarTerritorios();
};

#include "Juego.hxx"

#endif