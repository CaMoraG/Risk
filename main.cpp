#include <iostream>
#include <string>

#include "Sistema.h"

using namespace std;

struct Comando {
    string comando;
    string desc;
    string par;
};

void tratarComando(string entrada);
Comando obtenerComando(string comando);
void printRISK();
const list<Comando> comandos = {
        {"inicializar", "Parametros: \n"
        				"\n"
        				"Descripcion: \n"
						"Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones\n"
						},
        {"turno", "Parametros: \n"
        			"<id_jugador>\n"
        			"Descripcion: \n"
					"Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y fortificar)\n"
					},
        {"salir", "Parametros: \n"
        			"\n"
        			"Descripcion: \n"
					"Termina la ejecucion de la aplicacion\n"
						},
		{"guardar", "Parametros: \n"
        			"<nombre_archivo>\n"
        			"Descripcion: \n"
					"El estado actual del juego es guardado en un archivo de texto\n"
					},
		{"guardar_comprimido", "Parametros: \n"
        						"<nombre_archivo>\n"
        						"Descripcion: \n"
								"El estado actual del juego es guardado en un archivo binario (con extensión .bin)\n"
						},
		{"inicializar <nombre_archivo>", "Parametros: \n"
        								"<nombre_archivo>\n"
        								"Descripcion: \n"
										": Inicializa el juego con los datos contenidos en el archivo identificado por <nombre_archivo>\n"
						},
		{"costo_conquista", "Parametros: \n"
        					"<territorio>\n"
        					"Descripcion: \n"
							"El programa debe calcular el costo y la secuencia de territorios a ser conquistados para lograr "
							"controlar el territorio dado por el usuario\n"
						},
		{"conquista_mas_barata", "Parametros: \n"
        						"\n"
        						"Descripcion: \n"
								"De todos los territorios posibles, calcular aquel que pueda implicar un menor numero de "
								"unidades de ejercito perdidas\n"
						}
    };

Sistema juegosistema;

int main() {
    printRISK();
    while (true) {
        
        string entrada = "";
        cout << "$ ";
        getline(cin, entrada);
		if (entrada == "salir"){
            break;
        }
        tratarComando(entrada);
        
    }

    return 0;
}

Comando obtenerComando(string comando){
    Comando resultado;
    size_t espacio = comando.find_first_of(' ');
    string nombreComando = comando.substr(0, espacio);
    string parametro = comando.substr(espacio+1);
    string parametro2 = parametro;
    if (espacio != std::string::npos){
    	parametro.erase(remove_if(parametro.begin(), parametro.end(), ::isspace), parametro.end());
    	if(parametro.empty()){
    		resultado.par = "null";
		}else{
			resultado.par = parametro2;
		}
	}else{
		resultado.par = "null";
	}
    for (Comando it: comandos){
        if (it.comando==nombreComando){
            resultado.comando=it.comando;
            resultado.desc=it.desc;
            return resultado;
        }
    }
    resultado.comando="null";
    resultado.desc="null";
    resultado.par="null";
    return resultado;
}

void tratarComando(string entrada) {
    transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);
    if (entrada == "ayuda") {
            for(Comando it: comandos) {
    			cout << it.comando <<endl;
			}
            cout << ""<<endl;
    } else if (entrada.compare(0, 5, "ayuda") == 0) {
        string comando = entrada.substr(6);
        Comando resultado = obtenerComando(comando);
        if (resultado.desc!="null"){
            cout << resultado.desc <<endl;
        } else{
            cout << "Comando invalido" <<endl;
        }
    } else {
        Comando resultado = obtenerComando(entrada);
        if (resultado.comando!="null"){
            juegosistema.ejecutarComando(resultado.comando, resultado.par);
            //cin.ignore();
        } else{
            cout << "Comando invalido" <<endl;
        }
    }
}

void printRISK()
{
    cout << "RRRRR  IIIII  SSSSS  K   K\n";
    cout << "R   R    I    S      K  K \n";
    cout << "RRRRR    I    SSSSS  KK   \n";
    cout << "R  R     I        S  K  K \n";
    cout << "R   R  IIIII  SSSSS  K   K\n";
    cout << "\n";
}




