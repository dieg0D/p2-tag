/*
  a saida deste programa contera duas colunas de dados separadas por tabulacao
  coluna 1 - contem os valores do eixo x
  coluna 2 - contem o valores do eixo y (f(x)).
*/
 
#include <stdio.h>
#include <math.h>
 
int main ( ) {
    double x0 = -10.0;     // valor inicial
    double xf = 10.0; // valor final
    double step = 0.01;
     
    printf ( "# x \t f(x) \n" );
 
    while ( x0 <= xf ) {
        printf ( "%.3f \t %.3f \n", x0, pow(x0, 2)/20 );
        x0 += step;
    }
 
    return 0;
}