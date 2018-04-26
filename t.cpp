#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <queue>
using namespace std;

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
        cout << pilha.top() << " ";
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
        cout << topOrd[j] << " ";
    }
    cout << endl;
}

int main(){
    int vertices,n;
    string FileName;
    cout << "Insira a opção:"<<endl;
    cout << "Digite: 1 para small "<<endl;
    cout << "Digite: 2 para med "<<endl;
    cout << "Digite: 3 para large "<<endl;
    cout << "Digite: 4 para huge"<<endl;
    cout << "Opção:";
    cin >> n;
    switch(n){
        case 1: vertices = 10; FileName = "top_small.txt";
        break;
        case 2: vertices = 100; FileName = "top_med.txt";
        break;
        case 3: vertices = 10000; FileName = "top_large.txt";
        break;
        case 4: vertices = 100000; FileName = "top_huge.txt";
    }

    Graph grafo(vertices);
    grafo.CriaListaAdj(FileName);
    grafo.Imprimir(vertices);
    grafo.OrdenacaoTopologica();
    cout <<endl;
    grafo.Kahns();
    return 0;
}
