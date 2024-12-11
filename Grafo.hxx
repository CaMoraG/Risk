#include "Grafo.h"

const int INF = 100000000;

template <class V>
Grafo<V>::Grafo(){
    dirigido = false;
}

template <class V>
Grafo<V>::~Grafo(){

}

template <class V>
int Grafo<V>::numVertices(){
    return vertices.size();
}

template <class V>
int Grafo<V>::numAristas(){
    int total = 0;
    typename std::list<std::list<std::pair<V, int>>>::iterator it;
    for(it=aristas.begin(); it!=aristas.end(); it++){
        total+=it->size();
    }
    return total;
}

template <class V>
void Grafo<V>::insertarVertice(V nvertice){
    if(buscarVertice(nvertice)!=-1){
        return;
    }
    std::list<std::pair<V, int>> nlista;
    vertices.push_back(nvertice);
    aristas.push_back(nlista);
}

template <class V>
void Grafo<V>::insertarArista(V orVertice, V destVertice, int costo){
    bool existe = false;
    int idorigen = buscarVertice(orVertice);
    int idDestino = buscarVertice(destVertice);
    if(idorigen!=-1 && idDestino!=-1){
        typename std::list<std::list<std::pair<V, int>>>::iterator mit = aristas.begin();
        std::advance(mit, idorigen);
        std::list<std::pair<V, int>> verticelista = *mit;
        typename std::list<std::pair<V, int>>::iterator it;
        for(it=verticelista.begin(); it!=verticelista.end();it++){
            if(it->first==destVertice){
                existe = true;
                break;
            }
        }
        if(!existe){
            mit->push_back(std::make_pair(destVertice, costo));
        }
    }
}

template <class V>
int Grafo<V>::buscarVertice(V vertice){
    int id = -1;
    for(int i = 0; i<vertices.size(); i++){
        if(vertices[i]==vertice){
            id = i;
            break;
        }
    }
    return id;
}

template <class V>
int Grafo<V>::buscarArista(V orVertice, V destVertice){
    int costo = -1;
    int idorigen = buscarVertice(orVertice);
    int idDestino = buscarVertice(destVertice);
    if(idorigen!=-1 && idDestino!=-1){
        typename std::list<std::list<std::pair<V, int>>>::iterator mit = aristas.begin();
        std::advance(mit, idorigen);
        std::list<std::pair<V, int>> verticelista = *mit;
        typename std::list<std::pair<V, int>>::iterator it;
        for(it=verticelista.begin(); it!=verticelista.end();it++){
            if(it->first==destVertice){
                costo = it->second;
                break;
            }
        }
    }
    return costo;
}

template <class V>
void Grafo<V>::eliminarVertice(V vertice){
    int id = buscarVertice(vertice);
    if(id!=-1){
        typename std::list<std::list<std::pair<V, int>>>::iterator mit = aristas.begin();
        std::advance(mit, id);
        aristas.erase(mit);
        typename std::list<std::pair<V, int>>::iterator it;
        for(mit = aristas.begin(); mit != aristas.end(); mit++){
            std::list<std::pair<V, int>> &verticelista = *mit;
            for(it = verticelista.begin(); it!=verticelista.end(); it++){
                if(it->first==vertice){
                    it = verticelista.erase(it);
                }
            }
        }
        vertices.erase(vertices.begin()+id);
    }
}

template <class V>
void Grafo<V>::eliminarArista(V orVertice, V destVertice){
    int idorigen = buscarVertice(orVertice);
    int idDestino = buscarVertice(destVertice);
    if(idorigen!=-1 && idDestino!=-1){
        typename std::list<std::list<std::pair<V, int>>>::iterator mit = aristas.begin();
        std::advance(mit, idorigen);
        std::list<std::pair<V, int>> &verticelista = *mit;
        typename std::list<std::pair<V, int>>::iterator it;
        for(it=verticelista.begin(); it!=verticelista.end();it++){
            if(it->first==destVertice){
                it = verticelista.erase(it);
                break;
            }
        }
    }
}

template <class V>
void Grafo<V>::recorridoPlano(){
    for(int i = 0; i<vertices.size(); i++){
        std::cout<<vertices[i]<<" ";
    }
}

template <class V>
void Grafo<V>::DFS(V vertice){
    int id;
    if(buscarVertice(vertice)==-1)
        return;
    
    typename std::list<std::list<std::pair<V, int>>>::iterator mit;
    std::list<std::pair<V, int>> verticelista;
    typename std::list<std::pair<V, int>>::iterator it;

    std::vector<bool> visitado(vertices.size(), false);
    std::stack<V> pila;
    pila.push(vertice);

    while(!pila.empty()){
        vertice = pila.top();
        pila.pop();
        id = buscarVertice(vertice);

        if(!visitado[id]){
            visitado[id] = true;
            std::cout<<vertice<<" ";

            mit = aristas.begin();
            std::advance(mit, id);
            verticelista = *mit;

            for(it=verticelista.begin(); it!=verticelista.end();it++){
                pila.push(it->first);
            }
        }
    }
}

template <class V>
void Grafo<V>::BFS(V vertice){
    int id;
    if(buscarVertice(vertice)==-1)
        return;
    
    typename std::list<std::list<std::pair<V, int>>>::iterator mit;
    std::list<std::pair<V, int>> verticelista;
    typename std::list<std::pair<V, int>>::iterator it;

    std::vector<bool> visitado(vertices.size(), false);
    std::queue<V> cola;
    cola.push(vertice);

    while(!cola.empty()){
        vertice = cola.front();
        cola.pop();
        id = buscarVertice(vertice);

        if(!visitado[id]){
            visitado[id] = true;
            std::cout<<vertice<<" ";

            mit = aristas.begin();
            std::advance(mit, id);
            verticelista = *mit;

            for(it=verticelista.begin(); it!=verticelista.end();it++){
                cola.push(it->first);
            }
        }
    }
}

template <class V>
struct cmpCola{
    bool operator()(std::pair<V, int> a, std::pair<V, int> b) {
        return a.second > b.second; 
    }
};

template <class V>
std::vector<std::pair<int, int>> Grafo<V>::dijkstra(V vertice){
    int id = buscarVertice(vertice);
    
    int nvertices = numVertices();
    std::vector<V> predecesor;
    std::vector<int> costos;
    std::vector<bool> visitado(vertices.size(), false);
    predecesor.resize(nvertices);
    costos.assign(nvertices, 1000000);
    costos[id] = 0;
    predecesor[id] = vertice;
    visitado[id] = true;


    std::priority_queue <std::pair<V, int>, std::vector<std::pair<V, int>>, cmpCola<V>> heap;
    heap.push(std::make_pair(vertice, 0));
    V hvertice;
    int hcosto, idestino, costodestino;
    typename std::list<std::list<std::pair<V, int>>>::iterator mit;
    std::list<std::pair<V, int>> verticelista;
    typename std::list<std::pair<V, int>>::iterator it;

    while(!heap.empty()){
        hvertice = heap.top().first;
        hcosto = heap.top().second;
        heap.pop();

        id = buscarVertice(hvertice);
        mit = aristas.begin();
        std::advance(mit, id);
        verticelista = *mit;
        for(it=verticelista.begin(); it!=verticelista.end();it++){
            idestino = buscarVertice(it->first);
            costodestino = it->second;

            if(costos[id]+costodestino < costos[idestino]){
                costos[idestino] = costos[id]+costodestino;
                predecesor[idestino] = hvertice;
            }

            if(!visitado[idestino]){
                heap.push(std::make_pair(it->first, costos[idestino]));
                visitado[idestino] = true;
            }
        }
    }

    std::vector<std::pair<int, int>> resultado;
    resultado.resize(nvertices);
    for(int i = 0; i<numVertices(); i++){
        resultado[i] = std::make_pair(costos[i], predecesor[i]);
    }
    return resultado;
}

template <class V>
void Grafo<V>::aristasde(V vertice){
    int id = buscarVertice(vertice);
    if(id!=-1){
        std::cout<<vertice<<": ";
        typename std::list<std::list<std::pair<V, int>>>::iterator mit = aristas.begin();
        std::advance(mit, id);
        typename std::list<std::pair<V, int>>::iterator it;
        std::list<std::pair<V, int>> &verticelista = *mit;
        for(it = verticelista.begin(); it!=verticelista.end(); it++){
            std::cout<<it->first<<" ";
        }
    }
}

template <class V>
std::vector<std::vector<float>> Grafo<V>::matrizFW (){
    int n = numVertices();
    std::vector<std::vector<float>> matriz(n, std::vector<float>(n));
    int costo;

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(i==j){
                matriz[i][j] = 0;
            }else{
                costo = buscarArista(vertices[i], vertices[j]);
                if (costo==-1){
                    matriz[i][j] = INF;
                }else{
                    matriz[i][j] = costo;
                }
            }
        }
    }

    return matriz;
}

template <class V>
void Grafo<V>::floydwarshall(){
    std::vector<std::vector<float>> costos;
    costos = matrizFW();
    int n = numVertices();

    std::cout<<"Matriz original"<<std::endl;
    printMatriz(costos, n);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (costos[i][j] > costos[i][k] + costos[k][j]){
                    costos[i][j] = costos[i][k] + costos[k][j];
                }
            }
        }
    }
    std::cout<<"Matriz resultado"<<std::endl;
    printMatriz(costos, n);
}

template <class V>
void Grafo<V>::printMatriz(std::vector<std::vector<float>> matriz, int n){
    std::cout<<"  ";
    for(int i = 0; i<n; i++){
        std::cout<<vertices[i]<<" ";
    }
    std::cout<<std::endl;

    for(int i = 0; i < n; i++){
        std::cout<<vertices[i]<<" ";
        for(int j = 0; j<n; j++){
            if(matriz[i][j]==INF){
                std::cout<<"I ";
            }else{
                std::cout<<matriz[i][j]<<" ";
            }
        }
        std::cout<<std::endl;
    }
}