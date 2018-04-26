#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <queue>
#include <ctime>

using namespace std;
vector<int> top[8];
int Gcount= 0;
class Graph{ // Definição da classe grafo
    int vertices;
    list<int> *adj;
    
    public:
        Graph(int vertices);
        void CriaListaAdj(string FileName);
        void Imprimir(int vertices);
        void DFS(int vertices, bool visitado[], stack<int> &pilha);
        void OrdenacaoTopologica();
        void Kahns();
};

Graph::Graph(int vertices){ //Construtor da classe grafo
    this->vertices = vertices;
    adj = new list<int>[vertices];
}

void Graph::CriaListaAdj(string FileName){//Metodo que cria a lista de adjacencia do grafo
    ifstream file;
	file.open(FileName, ios::in);
	string linha,sub;
	 int j,k,c,tam;
     int s;
     int t;
     int i = 1;
	while( getline(file,linha)){
        tam = linha.length();
		if(i != 1){
            k=0;
            while((linha[k] >= '0') && (linha[k]) <= '9'){
                k++;
            }
            sub = linha.substr(0,k);
            s = stoll(sub);
            c= k;
            k++;
            while((linha[k] >= '0') && (linha[k]) <= '9'){
                k++;
            }
            sub = linha.substr(c,k);
            t = stoll(sub);
            adj[s].push_back(t);
		}
        i= 0;
    }
	file.close();
}

void Graph::Imprimir(int vertices){//Imprime a lista de adjacencia
    list<int>::iterator it;
    int i,j = 0;
    for( j ; j != vertices; j++){
	cout << j;
        for(it = adj[j].begin(); it != adj[j].end(); it++){
            i = *it;
            cout << " -> " << i;
        }
	cout << endl;
    }

}

void Graph::DFS(int vert, bool visitado[], stack<int> &pilha){
    visitado[vert] = true;
    list<int>::iterator it;

    for(it=adj[vert].begin(); it != adj[vert].end(); it++){
        if(!visitado[*it]){
            DFS(*it,visitado,pilha);
    
        }
    }
    pilha.push(vert);

}

void Graph::OrdenacaoTopologica(){
    stack<int> pilha;
    bool *visitado = new bool[vertices];
    for(int i=0; i<vertices; i++){
        visitado[i] = false;
    }

    for(int j=0; j < vertices; j++){
        if(visitado[j] == false){
            DFS(j,visitado,pilha);
        }
    }

    while(pilha.empty()== false){
        // cout << pilha.top() << " ";
        pilha.pop();

    }    
}

void Graph::Kahns(){
    vector<int> grau(vertices, 0);

    for (int i=0; i<vertices; i++){
        list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); it++){
            grau[*it]++;
        }     
    }
 
    queue<int> fila;
    for (int i = 0; i < vertices; i++){
        if (grau[i] == 0){
            fila.push(i);
        }
    }
        

    int count = 0;
 
    vector <int> topOrd;
 
    while (!fila.empty()){

        int i = fila.front();
        fila.pop();
        topOrd.push_back(i);
 
        list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); it++){
            if (--grau[*it] == 0){
                fila.push(*it);
            }
        }
        count++;
    }
 
    if (count != vertices){
        cout << "Existe um ciclo no grafo \n";
        return;
    }
 
    for (int j=0; j<topOrd.size(); j++){
        // cout << topOrd[j] << " ";
    }
    cout << endl;
}

int main(){
    int vertices,n;
    double inicio,fim;
    double tempo;
    string FileName;
    vector<double> tempos;

    vertices = 10;
    FileName = "top_small.txt";
    Graph grafo1(vertices);
    grafo1.CriaListaAdj(FileName);
    // grafo1.Imprimir(vertices);
    inicio = clock();
    grafo1.OrdenacaoTopologica();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;
    inicio = clock();
    grafo1.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;

    vertices = 100; 
    FileName = "top_med.txt";
    Graph grafo2(vertices);
    grafo2.CriaListaAdj(FileName);
    // grafo2.Imprimir(vertices);
    inicio = clock();
    grafo2.OrdenacaoTopologica();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;
    inicio = clock();
    grafo2.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;

    vertices = 10000;
    FileName = "top_large.txt";
    Graph grafo3(vertices);
    grafo3.CriaListaAdj(FileName);
    // grafo3.Imprimir(vertices);
    inicio = clock();
    grafo3.OrdenacaoTopologica();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;
    inicio = clock();
    grafo3.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;

    vertices = 100000;
    FileName = "top_huge.txt";
    Graph grafo4(vertices);
    grafo4.CriaListaAdj(FileName);
    // grafo4.Imprimir(vertices);
    inicio = clock();
    grafo4.OrdenacaoTopologica();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;
    inicio = clock();
    grafo4.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    printf("Tempo em segundos: %f", tempo);
    cout <<endl;
    
    for( int i : tempos){
        cout << tempos[i]<<endl;
    }
    return 0;
}
