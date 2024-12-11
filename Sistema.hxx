#include "Sistema.h"

void Sistema::crearGrafo(){
    Grafo <int> grafonuevo;
    int i;
    vector<Territorio> territorios = partida.getCTerritorios();
    int numTerritorios = territorios.size();

    for(i = 0; i<numTerritorios; i++){
        grafonuevo.insertarVertice(territorios[i].getId());
    }

    for(i = 0; i<numTerritorios; i++){
        for(int vecinoId: territorios[i].getVecinos()){
            grafonuevo.insertarArista(vecinoId, territorios[i].getId(), territorios[i].getGuarnicion());
        }
    }

    grafo = grafonuevo;
}

void Sistema::inicializar(){
    int numj =0;
    cout<<"Ingrese la cantidad de jugadores que tendra la partida"<<endl;
    if(cin>>numj && numj>2 && numj<7){
        int tropas = 35;
        if (numj == 4){
            tropas = 30;
        }else if (numj==5){
            tropas = 25;
        }else if (numj==6){
            tropas = 20;
        }
        vector<Jugador> jugadoresvect;
        Jugador J0;
        J0.setId(0);
        jugadoresvect.push_back(J0);
        vector<string> nombres;
        for(int i = 1; i<=numj;i++){
            bool terminado = false;
            while(!terminado){
                string nombre;
                cout<<"Ingrese el nombre del jugador "<<i<<""<<endl;
                cin>>nombre;
                if(nombre.size()>0 && !nombreRepetido(nombres, nombre)){
                    Jugador jugador;
                    jugador.setId(i);
                    jugador.setnombre(nombre);
                    jugador.setTropas(tropas);
                    jugadoresvect.push_back(jugador);
                    nombres.push_back(nombre);
                    terminado = true;
                }
                else{
                    cout<<"Nombre invalido o repetido"<<endl;
                }
            }
        }
        partida.setNumJugadores(numj);
        partida.setJugadores(jugadoresvect);
        vector<Jugador*> vectPunJug = partida.getJugadores();
        asignarTerritorios(vectPunJug);
        repartirTropas(vectPunJug);
        crearGrafo();
        partida.setTurno(1);
        partida.setInicializado(true);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "El juego ha sido inicializado exitosamente"<<endl;
    }else{
        cout<<"Entrada invalida o numero incorrecto (deben ser entre 3-6)"<<endl;
        cin.clear();
        cin.ignore();
    }
}

void Sistema::asignarTerritorios(vector<Jugador*> &jugadores){
    vector<Territorio*> territorios = partida.getTerritorios();
    vector<Territorio*>::iterator terrIte;
    int asignados = 0;
    int numTerritorios = territorios.size();
    int jugid = 1;
    while(asignados != numTerritorios){
        cout<<"ID | Continente, Nombre"<<endl;
        int i = 1;
        for(terrIte = territorios.begin(); terrIte != territorios.end(); terrIte++){
            Territorio *it = *terrIte;
            if (it->getJugador()==0){
                cout<<it->getId()<<" | "<<it->getContinente()<<", "<<it->getNombre()<<endl;
            }
        }
        Jugador* jugador = jugadores[jugid];
        cout<<"Turno del jugador "<<jugid<<" "<<jugador->getnombre()<<endl;
        bool provcorrecto = false;
        while(!provcorrecto){
            cout<<"Elija el numero de la provincia a tomar"<<endl;
            int prov = 0;
            if(cin>>prov && prov>=0 && prov<numTerritorios && territorios[prov]->getJugador()==0){
                provcorrecto = true;
                jugador->agregarPosesion(prov);
                jugador->quitarTropas(1);
                Territorio* terElegido = territorios[prov];
                terElegido->setJugador(jugid);
                terElegido->setGuarnicion(1);
                asignados++;
            }else{
                cout<<"Entrada invalida"<<endl;
                cin.clear();
                cin.ignore();
            }
        }
        if(jugid == (jugadores.size()-1)){
            jugid = 1;
        }else{
            jugid++;
        }
    }
}

void Sistema::repartirTropas(vector<Jugador*> &jugadores){
    int numJugadores = jugadores.size();
    vector<Territorio*> territorios = partida.getTerritorios();
    int numTerr = territorios.size();
    for(int i = 0; i<numJugadores-1; i++){
        Jugador* jugador = jugadores[i+1];
        list<int> posesiones = jugador->getPosesiones();
        cout<<"Turno del jugador "<<i+1<<" "<<jugador->getnombre()<<endl;
        while (jugador->getTropas()!=0){
            int tropasDisponibles = jugador->getTropas();
            printPosesiones(posesiones, territorios);
            cout<<"Usted tiene "<<tropasDisponibles<<" tropas"<<endl;
            bool opcorrecto = false;
            while(!opcorrecto){
                cout<<"Eliga la provincia a destinar soldados"<<endl;
                int prov;
                if(cin>>prov && prov>=0 && prov<numTerr && territorios[prov]->getJugador()==i+1){
                    opcorrecto = true;
                    bool tropcorrecto = false;
                    while(!tropcorrecto){
                        cout<<"Ingrese cantidad de soldados a destinar"<<endl;
                        int trop;
                        if(cin>>trop && trop<=tropasDisponibles && trop>0){
                            jugador->quitarTropas(trop);
                            territorios[prov]->agregarTropas(trop);
                            tropcorrecto = true;
                        }else{
                            cout<<"Entrada invalida"<<endl;
                        }
                    }
                }else{
                    cout<<"Entrada invalida"<<endl;
                }
            }
        }
    }
}

bool Sistema::nombreRepetido (vector<string> &nombres, string nombre){
    nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());
    transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
    bool resultado = false;
    if(!nombres.empty()){
        for (int i = 0; i<nombres.size();i++){
            string nombreIt = nombres[i];
            nombreIt.erase(remove_if(nombreIt.begin(), nombreIt.end(), ::isspace), nombreIt.end());
            transform(nombreIt.begin(), nombreIt.end(), nombreIt.begin(), ::tolower);
            if(nombreIt==nombre){
                resultado = true;
                return resultado;
            }
        }
    }
    return resultado;
}

void Sistema::turno(int id){
    vector<Jugador*> njugadores = partida.getJugadores();
    vector<Territorio*> nterritorios = partida.getTerritorios();
    Jugador* jugador = njugadores[id];
    int nuevastropas = partida.getJugTropas(id);
    int numTerr = nterritorios.size();
    list<int> posesiones = jugador->getPosesiones();
    if(nuevastropas==0){
        cout<<"Usted no dispone de tropas a colocar"<<endl;
    }
    while (nuevastropas!=0 && posesiones.size()>=1){
        cout<<"Usted dispone de: "<<nuevastropas<< " tropa(s) para colocar"<<endl;
        printPosesiones(posesiones, nterritorios);
        cout<<"Seleccione la provincia a agregar tropas"<<endl;
        int prov;
        if(cin>>prov && prov>=0 && prov<numTerr && nterritorios[prov]->getJugador()==id){
            int tropasasig;
            cout<<"Ingrese el numero tropas a agregar"<<endl;
            if(cin>>tropasasig && tropasasig>0 && tropasasig<=nuevastropas){
                nuevastropas-=tropasasig;
                nterritorios[prov]->agregarTropas(tropasasig);
                cin.clear();
                cin.ignore();
            }else{
                cout<<"Entrada invalida"<<endl;
                cin.clear();
                cin.ignore();
            }
        }else{
            cout<<"Entrada invalida"<<endl;
            cin.clear();
            cin.ignore();
        }
    }
    if(posesiones.empty()){
        cout<<"Usted ya no dispone de territorios"<<endl;
    }
    int a = -1;
    while (a!=0 && a!=1 && posesiones.size()>=1){
        cout<<"Ingrese 1 para proceder a atacar o 0 para no atacar este turno"<<endl;
        if(cin>>a && (a==1 || a==0)){
            if(a==1){
                cout<<"Ataque"<<endl<<endl;
                atacar(nterritorios, jugador, njugadores);
                cout<<"Fortalecer"<<endl<<endl;
                fortalecer(nterritorios, jugador);
            }else if(a==0){
                cout<<"Fortalecer"<<endl<<endl;
                fortalecer(nterritorios, jugador);
            }
            cin.clear();
            cin.ignore();   
        }
        else{
            cout<<"Entrada invalida"<<endl;
            cin.clear();
            cin.ignore();
        }
    }
    
    if (id == partida.getNumjugadores()){
        partida.setTurno(1);
    }else{
        id++;
        partida.setTurno(id);
    }
    crearGrafo();
    cout<<"Turno terminado"<<endl;
}

bool esVecino(vector<Territorio*> &vecinos, int id){
    bool vecino = false;
    for(int i = 0; i<vecinos.size(); i++){
        if(vecinos[i]->getId()==id){
            vecino = true;
            break;
        }
    }
    return vecino;
}

void Sistema::atacar(vector<Territorio*> &territorios, Jugador* jugador, vector<Jugador*> jugadores){
    int prov = -1;
    int numTerr = territorios.size();
    int jugid = jugador->getId();
    while (prov !=0){
        list<int> posesiones = jugador->getPosesiones();
        printPosesiones(posesiones, territorios);
        cout<<"Seleccione la provincia desde donde desea atacar o ingrese (n) para dejar de atacar"<<endl;
        cout<<"Recuerde que necesita al menos 2 tropas para atacar"<<endl;
        if(cin>>prov && prov>=0 && prov<numTerr && territorios[prov]->getJugador()==jugid){
            Territorio* terreleg = territorios[prov];
            cout<<"Usted puede atacar desde "<<terreleg->getNombre()<<" a las siguientes provincias:"<<endl;
            vector<Territorio*> vecinos = Vecinos(terreleg, territorios, true, jugid);
            if(vecinos.size()>=1 && terreleg->getGuarnicion()>=2){
                cout<<"ID | Continente, Nombre,  guarnicion:"<<endl;
                for (int i=0;i<vecinos.size();i++){
                    Territorio* itterritorio = vecinos[i];
                    int enemid = itterritorio->getJugador();
                    cout<<itterritorio->getId()<< " | "<<itterritorio->getContinente()<<", "<<itterritorio->getNombre()<<", guarnicion: "<<
                    itterritorio->getGuarnicion()<<" | pertenece al jugador "<<enemid<<", "<<jugadores[enemid]->getnombre()<<endl;  
                }   
                int atacarnum = -1; 
                cout<<"Seleccione la provincia que desea atacar"<<endl;
                if(cin>>atacarnum && atacarnum>=0 && atacarnum<numTerr && esVecino(vecinos, atacarnum) && territorios[atacarnum]->getJugador()!=jugid){
                    Territorio* def = territorios[atacarnum];
                    combate(terreleg, def, jugid);
                    prov++;
                }else{
                    cout<<"Entrada invalida"<<endl;
                    cin.clear();
                    cin.ignore();
                }  
            }
            else{
                cout<<"No hay vecinos que pueda atacar, o no tiene soldados suficientes, elija otra provincia"<<endl;
                cin.clear();
                cin.ignore();
            }
        }
        else{
            cin.clear();
            cin.ignore();
        }
    }
}

void Sistema::combate(Territorio* atacante, Territorio* defensor, int id){
    int atacantes = atacante->getGuarnicion();
    int defensores = defensor->getGuarnicion();
    int num = -1;
    vector<Jugador*> jugadores = partida.getJugadores();
    cout<<"Informacion del combate: "<<endl;
    cout<<"Usted dispone de: "<<atacantes<<" tropas para atacar"<<endl;
    cout<<"El defensor tiene: "<<defensores<<" tropas"<<endl;
    while (num!=0){
        cout<<"Ingrese 1 para atacar o ingrese 0 para dejar de atacar"<<endl;
        if(cin>>num && num==1){
            cout<<"-----------------------------------------------------------"<<endl;
            bool conquista = partida.combate(atacantes, defensores);
            atacante->setGuarnicion(atacantes);
            defensor->setGuarnicion(defensores);
            cout<<"\nResultados de la batalla:"<<endl;
            cout<<"Usted ahora dispone de: "<<atacantes<<" tropas para atacar"<<endl;
            cout<<"El defensor ahora tiene: "<<defensores<<" tropas"<<endl;
            cout<<"-----------------------------------------------------------"<<endl;
            if(conquista){
                if (atacantes<2){
                    cout<<"Usted gano pero no le quedan tropas suficientes para tomar la provincia"<<endl;
                    num = 0;
                    break;
                }
                bool reclamado = false;
                int nuevastropas = 0;
                while(!reclamado && atacantes>=2){
                    cout<<"Usted ha salido victorioso!"<<endl;
                    cout<<"Ingrese las tropas que desea mover a su nueva provincia"<<endl;
                    if(cin>>nuevastropas && nuevastropas>=1 && nuevastropas<atacantes){
                        atacantes-=nuevastropas;
                        int defid = defensor->getId();
                        int jugdef = defensor->getJugador();
                        jugadores[id]->agregarPosesion(defid);
                        jugadores[jugdef]->eliminarPosesion(defid);
                        atacante->setGuarnicion(atacantes);
                        defensor->setJugador(id);
                        defensor->setGuarnicion(nuevastropas);
                        //ganarcarta
                        reclamado = true;
                        num = 0;
                        //cin.clear();
                        //cin.ignore();
                    }else{
                        cout<<"Entrada invalida"<<endl;
                        cin.clear();
                        cin.ignore();
                    }
                } 
            }else{
                if(atacantes == 1){
                    cout<<"Ya no tiene suficientes tropas para atacar"<<endl;
                    num = 0;
                    cin.clear();
                    cin.ignore();
                }
            }
        }else if(num!=0){
            cout<<"Entrada invalida"<<endl;
            cin.clear();
            cin.ignore();
        }
    }
    if(num==0){
        cin.clear();
        cin.ignore();
    }
}

void Sistema::fortalecer(vector<Territorio*> &territorios, Jugador* jugador){
    int prov = -1;
    int jugid = jugador->getId();
    int numTerr = territorios.size();
    while (prov !=0){
        list<int> posesiones = jugador->getPosesiones();
        printPosesiones(posesiones, territorios);
        cout<<"Seleccione la provincia desde donde desea mover tropas o ingrese (n) para no fortalecer"<<endl;
        if(cin>>prov && prov>=0 && prov<numTerr && territorios[prov]->getJugador()==jugid){
            Territorio* terreleg = territorios[prov];
            cout<<"Usted puede mover desde "<<terreleg->getNombre()<<" a las siguientes provincias:"<<endl;
            vector<Territorio*> vecinos = Vecinos(terreleg, territorios, false, jugid);
            if(vecinos.size()>=1 && terreleg->getGuarnicion()>=2){
                for (int i=0;i<vecinos.size();i++){
                    Territorio* itterritorio = vecinos[i];
                    cout<<itterritorio->getId()<<" | "<<itterritorio->getContinente()<<", "<<itterritorio->getNombre()<<": "<<itterritorio->getGuarnicion()<<" tropas"<<endl; 
                }   
                int movernum = -1; 
                cout<<"Seleccione la provincia a la que desea mover tropas"<<endl;
                if(cin>>movernum && movernum>=0 && movernum<numTerr && esVecino(vecinos, movernum) && territorios[movernum]->getJugador()==jugid){
                    Territorio* mov = territorios[movernum];
                    int nuevastropas;
                    cout<<"En "<<terreleg->getNombre()<<" usted dispone de "<<terreleg->getGuarnicion()<<" tropas"<<endl;
                    cout<<"Ingrese la cantidad de tropas de desea mover"<<endl;
                    if(cin>>nuevastropas && nuevastropas>0 && nuevastropas<terreleg->getGuarnicion()){
                        terreleg->quitarTropas(nuevastropas);
                        mov->agregarTropas(nuevastropas);
                        prov = 0;
                    }else{
                        cout<<"Entrada invalida"<<endl;
                        cin.clear();
                        cin.ignore();
                    }
                }
                else{
                    cout<<"Entrada invalida"<<endl;
                    cin.clear();
                    cin.ignore();
                }  
            }
            else{
                cout<<"No hay vecinos que pueda fortalecer, o no tiene soldados suficientes, elija otra provincia"<<endl;
                cin.clear();
                cin.ignore();
            }
        }
        else{
            cin.clear();
            cin.ignore();
        }
    }
}

void Sistema::printPosesiones (list<int> &posesiones, vector<Territorio*> &territorios){
    cout<<"ID | Continente, Nombre: Guarnicion"<<endl;
    for(int pos : posesiones){
        Territorio* terr = territorios[pos];
        cout<<terr->getId()<<" | "<<terr->getContinente()<<", "<<terr->getNombre()<<": "<<terr->getGuarnicion()<<" tropas"<<endl;
    }
}

vector<Territorio*> Sistema::Vecinos (Territorio* &territorio, vector<Territorio*> &territorios, bool enemigos, int id){
    vector<Territorio*> vecinos;
    list<int> indicevecinos = territorio->getVecinos();
    //list<int>::iterator it;
    for (int &it : indicevecinos){
        Territorio* itterritorio = territorios[it];
        if(enemigos){
            if(itterritorio->getJugador()!=id){
                vecinos.push_back(itterritorio);
            }
        }else{
            if(itterritorio->getJugador()==id){
                vecinos.push_back(itterritorio);
            }
        }
    }
    return vecinos;
}

void Sistema::ejecutarComando (string comando, string parametro){
	if (comando=="inicializar" && parametro=="null"){
		if(partida.getInicializado()){
            cout << "El juego ya ha sido inicializado" <<endl;
        }else{
            inicializar();
        }
	}
    else if(comando=="turno"){
        try {
            int idjugador = partida.getJugadorId(parametro);
            if(!partida.getInicializado()){
                cout << "Esta partida no ha sido inicializada correctamente" <<endl;
            } 
            else if (partida.getTerminado()){
                cout << "Esta partida ya tuvo un ganador" <<endl;
            }else if (idjugador == -1){
                cout << "El jugador " <<parametro<< " no forma parte de esta partida" <<endl;
            }else if (idjugador!=partida.getTurno()){
                cout << "No es el turno del jugador "<<parametro <<endl;
            }else{
                turno(idjugador);
            }
        } catch (const invalid_argument& e) {
            cout << "Comando invalido" <<endl;
        } catch (const out_of_range& e) {
            cout << "Comando invalido" <<endl;
        }
    }
    
    else if(comando=="guardar" and parametro!="null"){
        if (archivoValido(parametro, ".txt")){
            guardar(parametro);
        }else{
            cout << "Comando invalido" <<endl;
        }
        
    }else if(comando=="guardar_comprimido" and parametro!="null"){
        if (archivoValido(parametro, ".bin")){
            guardar_comprimido(parametro);
        }else{
            cout << "Comando invalido" <<endl;
        }
    }else if(comando=="inicializar" and parametro!="null"){
        if(partida.getInicializado()){
            cout << "Juego en curso)" <<endl;
        }
        else if (archivoValido(parametro, ".txt")){
            cargarTXT(parametro);
        }
        else if (archivoValido(parametro, ".bin")){
            cargarBIN(parametro);
        }else{
            cout << "Comando invalido" <<endl;
        }
    }
    
    else if(comando=="costo_conquista" and parametro!="null"){
        if(!partida.getInicializado()){
            cout << "Esta partida no ha sido inicializada correctamente" <<endl;
        } else if (partida.getTerminado()){
            cout << "Esta partida ya tuvo un ganador" <<endl;
        }else
            costo_conquista(parametro);
        
    }else if(comando=="conquista_mas_barata" and parametro=="null"){
        if(!partida.getInicializado()){
            cout << "Esta partida no ha sido inicializada correctamente" <<endl;
        } else if (partida.getTerminado()){
            cout << "Esta partida ya tuvo un ganador" <<endl;
        }else
            conquista_barata();
    }
    else{
		cout << "Comando invalido" <<endl;
	}
}

bool Sistema::extension(string nombre) {
    size_t punto = nombre.find_last_of('.');
    return (punto != std::string::npos) && (punto != nombre.length() - 1);
}

bool Sistema::archivoValido(string nombre, string extension){
    if (nombre.length() >= extension.length()) {
        return nombre.substr(nombre.length() - extension.length()) == extension;
    }
    return false;
}

void Sistema::guardar(string nombreArchivo){
    ofstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        cerr << "No se pudo leer el archivo" << endl;
        return;
    }

    try{
        archivo<<generarLinea();

        archivo.close();
        cout << "Juego guardado" <<endl;
    } catch(...){
        cout << "La partida no ha sido guardada correctamente" <<endl;
    }
}

void Sistema::guardar_comprimido(string nombreArchivo){
    try{
        ArbolHuffman arbol;
        string linea = generarLinea();

        arbol.codificar(linea, nombreArchivo);
        cout << "Juego guardado" <<endl;
    } catch(...){
        cout << "La partida no ha sido guardada correctamente" <<endl;
    }
}

void Sistema::cargarBIN(string nombreArchivo){
    try{
        ArbolHuffman arbol;
        string linea = arbol.leerArchivo(nombreArchivo);
        cargarLinea(linea);
        crearGrafo();
    }catch(...){
        cout << nombreArchivo+" no contiene información válida para inicializar el juego" <<endl;
    }
}

void Sistema::cargarTXT(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    string lineaGuardado = "";
    if(!archivo.is_open()){
        cerr << "No se pudo leer el archivo" << endl;
        exit(1);
    }
    try{
        string linea;
        while (getline(archivo, linea)) {
            lineaGuardado += linea;
            lineaGuardado += '\n';
        }
        archivo.close();
        cargarLinea(lineaGuardado);
        crearGrafo();
    }catch(...){
        cout << nombreArchivo+" no contiene información válida para inicializar el juego" <<endl;
    }
}

void Sistema::cargarLinea(string linea){
    std::istringstream stream(linea);
    std::queue<std::string> lineas;
    std::string token;

    while (std::getline(stream, token, '\n')){
        lineas.push(token);
    }

    vector<Territorio*> territorios = partida.getTerritorios();
    vector<Jugador> jugadores;
    Jugador J0;
    J0.setId(0);
    jugadores.push_back(J0);

    int turno = stoi(lineas.front());
    lineas.pop();
    partida.setTurno(turno);

    int numjugadores = stoi(lineas.front());
    lineas.pop();
    partida.setNumJugadores(numjugadores);

    for(int i = 1; i<=numjugadores; i++){
        Jugador jugadorn;
        jugadorn.setId(i);
        jugadorn.setnombre(lineas.front());
        lineas.pop();
        int numposesiones = stoi(lineas.front());
        lineas.pop();

        for (int j = 0; j<numposesiones; j++){
            int terid = stoi(lineas.front());
            lineas.pop();
            int terrtropas = stoi(lineas.front());
            lineas.pop();
            jugadorn.agregarPosesion(terid);
            territorios[terid]->setGuarnicion(terrtropas);
            territorios[terid]->setJugador(i);
        }
        jugadores.push_back(jugadorn);
    }

    partida.setJugadores(jugadores);
    partida.setInicializado(true);
    cout<<"Juego inicializado"<<endl;
}

string Sistema::generarLinea(){
    vector<Territorio*> territorios = partida.getTerritorios();
    vector<Jugador*> jugadores = partida.getJugadores();
    string linea = "";

    int turno = partida.getTurno();
    linea+=to_string(turno);
    linea+='\n';

    int numjugadores = partida.getNumjugadores();
    linea+=to_string(numjugadores);
    linea+='\n';

    for(int i = 1; i<=numjugadores; i++){
        linea+=jugadores[i]->getnombre();
        linea+='\n';
        int numposesiones = jugadores[i]->getPosesiones().size();
        list<int> posesiones = jugadores[i]->getPosesiones();
        linea+=to_string(numposesiones);;
        linea+='\n';
        for(int idpos: posesiones){
            linea+=to_string(idpos);
            linea+='\n';
            linea+=to_string(territorios[idpos]->getGuarnicion());
            linea+='\n';
        }
    }

    return linea;
}

void Sistema::costo_conquista(string nomterritorio){
    int destinoId = partida.getTerritorioId(nomterritorio);
    if(destinoId==-1){
        cout<<"Nombre de territorio invalido"<<endl;
        return;
    }
    int turno = partida.getTurno();
    Jugador jugador = partida.getJugador(turno);
    vector<Territorio> territorios = partida.getCTerritorios();
    if(territorios[destinoId].getJugador()==turno){
        cout<<"El jugador "+jugador.getnombre()+" ya posee el territorio de "+territorios[destinoId].getNombre()<<endl;
        return;
    }
    std::vector<std::pair<int, int>> resultado;//pair(distancia, predecesor)
    std::vector<std::pair<int, int>> mejor;
    int mejorIdOrigen, dist = 100000;
    bool cambio = false, finalizado = false;

    for(int posId: jugador.getPosesiones()){
        resultado = grafo.dijkstra(posId);
        if(resultado[destinoId].first<dist){
            mejor = resultado;
            mejorIdOrigen = posId;
            dist = resultado[destinoId].first;
        }
    }

    queue<int> ruta;
    int sig = destinoId;
    while(!finalizado){
        if(mejor[sig].second==mejorIdOrigen)
            finalizado = true;
        else{
            ruta.push(mejor[sig].second);
            sig = mejor[sig].second;
        }
    }
    cout<<"Para conquistar el territorio "+territorios[destinoId].getNombre()+", debe atacar desde "+territorios[mejorIdOrigen].getNombre();
    if(ruta.size()>0){
        cout<<", pasando por los territorios "+territorios[ruta.front()].getNombre();
        ruta.pop();
        while(!ruta.empty()){
            cout<<", ";
            cout<<territorios[ruta.front()].getNombre();
            ruta.pop();
        }  
    }
    cout<<"."<<endl;
    cout<<"Debe conquistar "<<dist<<" unidades de ejército."<<endl;
}

void Sistema::conquista_barata(){
    int turno = partida.getTurno();
    Jugador jugador = partida.getJugador(turno);
    vector<Territorio> territorios = partida.getCTerritorios();
    std::vector<std::pair<int, int>> resultado;//pair(distancia, predecesor)
    std::vector<std::pair<int, int>> mejor;
    int mejorIdDest, mejorIdOrigen, tmpOrigen, dist = 100000;
    bool cambio = false, finalizado = false;

    for(int posId: jugador.getPosesiones()){
        resultado = grafo.dijkstra(posId);
        for(int i = 0; i<resultado.size(); i++){
            if(resultado[i].first < dist && territorios[i].getId()!=turno && resultado[i].first!=0){
                mejorIdDest = i;
                dist = resultado[i].first;
                cambio = true;
            }
            if(resultado[i].second==i)
                tmpOrigen = i;
        }
        if(cambio){
            mejorIdOrigen = tmpOrigen;
            mejor = resultado;
            cambio = false;
        }
    }

    queue<int> ruta;
    int sig = mejorIdDest;
    while(!finalizado){
        if(mejor[sig].second==mejorIdOrigen)
            finalizado = true;
        else{
            ruta.push(mejor[sig].second);
            sig = mejor[sig].second;
        }
    }

    cout<<"La conquista más barata es avanzar sobre el territorio "+ territorios[mejorIdDest].getNombre();
    cout<<" desde el territorio "+ territorios[mejorIdOrigen].getNombre() + "."<<endl;
    cout<<"Para conquistar el territorio "+territorios[mejorIdDest].getNombre()+", debe atacar desde "+territorios[mejorIdOrigen].getNombre();
    if(ruta.size()>0){
        cout<<", pasando por los territorios "+territorios[ruta.front()].getNombre();
        ruta.pop();
        while(!ruta.empty()){
            cout<<", ";
            cout<<territorios[ruta.front()].getNombre();
            ruta.pop();
        }  
    }
    cout<<"."<<endl;
    cout<<"Debe conquistar "<<dist<<" unidades de ejército."<<endl;
}