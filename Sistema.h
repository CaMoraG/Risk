#ifndef _Sistema_H_
#define _Sistema_H_


#include <sstream>

#include "Juego.h"
#include "Jugador.h"
#include "Territorio.h"
#include "Grafo.h"
#include "ArbolHuffman.h"

class Sistema {
private:
    Juego partida;
    Grafo<int> grafo;

    void crearGrafo();
    void inicializar();
    void turno(int id);
    void guardar(string nombreArchivo);
    void guardar_comprimido(string nombreArchivo);
    void cargarBIN(string nombreArchivo);
    void cargarTXT(string nombreArchivo);
    void cargarLinea(string linea);
    string generarLinea();
    void costo_conquista(string nomterritorio);
    void conquista_barata();
    bool archivoValido(string nombre, string extension);
    bool extension(string nombre);
    void printPosesiones (list<int> &posesiones, vector<Territorio*> &territorios);
    void atacar(vector<Territorio*> &territorios, Jugador* jugador, vector<Jugador*> jugadores);
    vector<Territorio*> Vecinos (Territorio* &territorio, vector<Territorio*> &territorios, bool enemigos, int id);
    void combate(Territorio* atacante, Territorio* defensor, int id);
    void fortalecer(vector<Territorio*> &territorios, Jugador* jugador);
    void asignarTerritorios(vector<Jugador*> &jugadores);
    void repartirTropas(vector<Jugador*> &jugadores);
    bool nombreRepetido (vector<string> &nombres, string nombre);
public:
    void ejecutarComando (string comando, string parametro);
};

#include "Sistema.hxx"

#endif