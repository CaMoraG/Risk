#include "Juego.h"

using namespace std;


void Juego::setJugadores(vector<Jugador> &njugadores){
    jugadores = njugadores;
}
vector<Jugador*> Juego::getJugadores(){
    vector<Jugador*> vectorNuevo;
    for(Jugador &itjug : jugadores){
        vectorNuevo.push_back(&itjug);
    }
    return vectorNuevo;
}
vector<Territorio*> Juego::getTerritorios(){
    vector<Territorio*> vectorNuevo;
    for(Territorio &itter : territorios){
        vectorNuevo.push_back(&itter);
    }
    return vectorNuevo;
}
vector<Territorio> Juego::getCTerritorios(){
    return territorios;
}
Jugador Juego::getJugador(int id){
    return jugadores[id];
}
void Juego::setInicializado(bool tf){
    inicializado = tf;
}
bool Juego::getInicializado(){
    return inicializado;
}
void Juego::setTerminado(bool tf){
    terminado = tf;
}
bool Juego::getTerminado(){
    return terminado;
}
void Juego::setTurno(int nturno){
    turno = nturno;
}
int Juego::getTurno(){
    return turno;
}
void Juego::setNumJugadores(int num){
    numjugadores = num;
}
int Juego::getNumjugadores(){
    return numjugadores;
}
int Juego::getTerritorioId(string nombre){
    int i = 0;
    string nombreTerr;
    for(Territorio itter : territorios){
        nombreTerr = itter.getNombre();
        transform(nombreTerr.begin(), nombreTerr.end(), nombreTerr.begin(), ::tolower);
        if(nombreTerr==nombre){
            return i;
        }
        i++;
    }
    return -1;
}

int Juego::getJugadorId(string nombre){
    bool encontrado = false;
    int i = 0;
    string nombreJug;
    cout<<nombre<<endl;
    for(Jugador itter : jugadores){
        nombreJug = itter.getnombre();
        cout<<nombreJug<<endl;
        if(nombreJug==nombre){
            encontrado = true;
            return i;
        }
        i++;
    }
    if(!encontrado){
        i = -1;
    }
    return i;
}
bool Juego::combate(int &atacante, int &defensor){
    bool conquista = false;
    vector<int> rAtacante = lanzarDados(3);
    vector<int> rDefensor = lanzarDados(2);
    sort(rAtacante.rbegin(), rAtacante.rend());
    sort(rDefensor.rbegin(), rDefensor.rend());
    if (defensor==0){
        return true;
    }
    cout<<"Resultados atacante: "<<rAtacante[0]<<", "<<rAtacante[1]<<", "<<rAtacante[2]<<endl;
    cout<<"Resultados defensor: "<<rDefensor[0]<<", "<<rDefensor[1]<<endl;
    if(rAtacante[0]>rDefensor[0]){
        defensor-=1;
        cout<<"El defensor pierde 1 tropa"<<endl;
        if (defensor == 0){
            return true;
        }
    }else{
        atacante-=1;
        cout<<"El atacante pierde 1 tropa"<<endl;
        if(atacante==1){
            return false;
        }
    }
    if(rAtacante[1]>rDefensor[1]){
        defensor-=1;
        cout<<"El defensor pierde 1 tropa"<<endl;
        if (defensor == 0){
            return true;
        }
    }else{
        atacante-=1;
        cout<<"El atacante pierde 1 tropa"<<endl;
        if(atacante==1){
            return false;
        }
    }
    return conquista;
}
vector<int> Juego::lanzarDados(int n) {
    vector<int> resultados;
    
    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<int> dado(1, 6);
    for (int i = 0; i < n; ++i) {
        int resultado = dado(generador);
        resultados.push_back(resultado);
    }
    
    return resultados;
}
int Juego::getJugTropas(int id){
    int tropas = 0, numNort = 0, numSur = 0, numE = 0, numAf = 0, numAs = 0, numAu = 0;
    Jugador jugador = jugadores[id];
    tropas += jugador.nuevasTropasT();
    list<int> indices = jugador.getPosesiones();
    for (int it : indices){
        string continente = territorios[it].getContinente();
        if (continente == "America del norte"){
            numNort++;
        }else if (continente == "America del sur"){
            numSur++;
        }else if (continente == "Europa"){
            numE++;
        }else if (continente == "Africa"){
            numAf++;
        }else if (continente == "Asia"){
            numAs++;
        }else if (continente == "Australia"){
            numAu++;
        }
    }
    if (numNort == 9){
        tropas+=5;
    }if (numSur==4){
        tropas+=2;
    }if (numE == 7){
        tropas+=5;
    }if (numAf == 6){
        tropas+=3;
    }if (numAs == 12){
        tropas+=7;
    }if (numAu == 4){
        tropas+=2;
    }
    return tropas;
}
/*
vector<Territorio&> Juego::asignarTerritorios(){

}*/