#include <bits/stdc++.h>
using namespace std;

class Graph{ // Definição da classe grafo
    int vert;
    list<int> *adj;

    public:
        Graph(int vert);
        void CriaListaAdj(string FileName);
        void Imprimir(int vertices);
};

Graph::Graph(int vert){ //Construtor da classe grafo
    this->vert = vert;
    adj = new list<int>[vert];
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
    return 0;
}
