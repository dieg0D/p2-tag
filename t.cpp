#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <queue>
#include <ctime>
#include <math.h>
#include <stdlib.h>
#define GNUPLOT "gnuplot -persist"




using namespace std;

FILE *TDFS;
FILE *KAN;


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
        fprintf(TDFS, "%d ", pilha.top());
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
        fprintf(KAN, "%d ", topOrd[j]);
    }
    cout << endl;
}

void Plotar(int x){
    FILE *gp;
    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }
    if(x == 1){
        fprintf(gp, "set key above center\n");
        fprintf(gp, "set xlabel 'TEMPO EM SEGUNDOS'\n");
        fprintf(gp, "set ylabel 'QUANTIDADE DE NÓS'\n");
        fprintf(gp, "plot 'Tdata1.txt' title 'ORDENAÇÃO TOPOLÓGICA (DFS)' lt rgb 'red' with lines smooth csplines, 'Kdata1.txt' title 'KAHNS' lt rgb 'blue' with lines smooth csplines\n");
    }
    if(x == 2){
        fprintf(gp, "set key above center\n");
        fprintf(gp, "set xlabel 'TEMPO EM SEGUNDOS'\n");
        fprintf(gp, "set ylabel 'QUANTIDADE DE NÓS'\n");
        fprintf(gp, "plot 'Tdata2.txt' title 'ORDENAÇÃO TOPOLÓGICA (DFS)' lt rgb 'red' with lines smooth csplines, 'Kdata2.txt' title 'KAHNS' lt rgb 'blue' with lines smooth csplines\n");
    }
    if(x == 3){
        fprintf(gp, "set key above center\n");
        fprintf(gp, "set xlabel 'TEMPO EM SEGUNDOS'\n");
        fprintf(gp, "set ylabel 'QUANTIDADE DE NÓS'\n");
        fprintf(gp, "plot 'Tdata3.txt' title 'ORDENAÇÃO TOPOLÓGICA (DFS)' lt rgb 'red' with lines smooth csplines, 'Kdata3.txt' title 'KAHNS' lt rgb 'blue' with lines smooth csplines\n");
    }
    if(x == 4){
        fprintf(gp, "set key above center\n");
        fprintf(gp, "set xlabel 'TEMPO EM SEGUNDOS'\n");
        fprintf(gp, "set ylabel 'QUANTIDADE DE NÓS'\n");
        fprintf(gp, "plot 'Tdata4.txt' title 'ORDENAÇÃO TOPOLÓGICA (DFS)' lt rgb 'red' with lines smooth csplines, 'Kdata4.txt' title 'KAHNS' lt rgb 'blue' with lines smooth csplines\n");
    }
    fclose(gp);
}



int main(){
	TDFS = fopen("TDFS.txt", "wt");
	KAN = fopen("KAN.txt", "wt");
    int vertices, n, vert;
    double inicio,fim;
    double tempo, tempno, g;
    string FileName;
    vector<double> tempos;
    int nos[4];
    nos[0] = 10;
    nos[1] = 100;
    nos[2] = 1000;
    nos[3] = 10000;
    FILE *Tarq1;
    FILE *Tarq2;
    FILE *Tarq3;
    FILE *Tarq4;

    FILE *Karq1;
    FILE *Karq2;
    FILE *Karq3;
    FILE *Karq4;

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    Tarq1 = fopen("Tdata1.txt", "wt");
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
    tempno = tempo/10;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Tarq1, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Tarq1);

    Karq1 = fopen("Kdata1.txt", "wt");
    inicio = clock();
    grafo1.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    tempno = tempo/10;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Karq1, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Karq1);

    ///////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////
   
    Tarq2 = fopen("Tdata2.txt", "wt");
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
    tempno = tempo/100;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Tarq2, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }    
    fclose(Tarq2);

    Karq2 = fopen("Kdata2.txt", "wt");
    inicio = clock();
    grafo2.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    tempno = tempo/100;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Karq2, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Karq2);

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    Tarq3 = fopen("Tdata3.txt", "wt");        
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
    tempno = tempo/10000;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Tarq3, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Tarq3);

    Karq3 = fopen("Kdata3.txt", "wt");
    inicio = clock();
    grafo3.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    tempno = tempo/10000;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Karq3, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Karq3);

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    Tarq4 = fopen("Tdata4.txt", "wt");
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
    tempno = tempo/100000;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Tarq4, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Tarq4);

    Karq4 = fopen("Kdata4.txt", "wt");
    inicio = clock();
    grafo4.Kahns();
    fim = clock();
    tempo = (double(fim-inicio)/CLOCKS_PER_SEC);
    tempos.push_back(tempo);
    tempno = tempo/100000;
    g = 0.0;
    vert = 1;
    while(g<=tempo && vert<=vertices){
        fprintf(Karq4, "%f %d\n", g, vert);
        g = g + tempno;
        vert++;
    }
    fclose(Karq4);

    //////////////////////////////////////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    fclose(TDFS);
	fclose(KAN);
    
    int x;
    do {
    	printf("\n           Graficos        \nOrdenacao Topologica VS Kahns\n\n1. 10 vertices\n2. 100 vertices\n3. 10000 vertices\n4. 100000 vertices\n5. Sair\n\n(Imprime o digrafo e plota o grafico de exec.temporal)\n Opcao:   ");
	    scanf("%d", &x);
	    switch(x){
	    	case 1:	grafo1.Imprimir(10);
        			printf("Como pudemos ver no grafico a escolha do algoritmo de ordenacao topologica e clara, pois seu tempo de execucao e muito menor.\n");
	    			Plotar(x); break;

	    	case 2: grafo2.Imprimir(100);
            		printf("Como pudemos ver no grafico a escolha do algoritmo de ordenacao topologica e clara, pois seu tempo de execucao e muito menor.\n");
	    			Plotar(x); break;

	    	case 3: grafo3.Imprimir(10000);
        			printf("Em alguns casos da execucao da ordenacao, o algoritmo de Kahns pode ser mais rapido nesse caso especifico de numero de vertices, mas na maioria das vezes o de Ordenacao topologica sera mais eficiente.\n");
	    			Plotar(x); break;

	    	case 4: grafo4.Imprimir(100000);
       				printf("Como pudemos ver no grafico a escolha do algoritmo de ordenacao topologica e clara, pois seu tempo de execucao e muito menor.\n");
	    			Plotar(x); break;

	    	case 5:	printf("Valeu mano Dibio, dibioa!!"); break;
	    	
	    	default: printf("Opcao invalida!!");
	    }
	}while(x!=5);


    return 0;
}