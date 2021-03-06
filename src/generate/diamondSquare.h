#ifndef DIAMONDSQUARE_H_
#define DIAMONDSQUARE_H_

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../draw/draw.h"

/**ALGORITMO DIAMOND-SQUARE**/
/**Descricao:
		Este algoritmo recursivo recebe quatro pontos iniciais, cada um localizado em um canto
	do mapa e um int que descreve o numero maximo aleatorio possivel na altura dos proximos
	pontos do mapa. A largura(x) e altura(y) entre o ponto superior esquerdo e o ponto
	inferior direito nao podem ser pares e o numero aleatorio maximo nao pode ser 0.

	Funcionamento:
		A cada recursao, checamos primeiramente se o numero aleatorio recebido nao eh menor que
		zero, caso seja, forcamos que ele seja 1.
		Testamos entao se ha espaco entre os pontos A e C o bastante para calcular o ponto central
		CT e os pontos marginais AB, BC, CD e DA. Caso nao seja possivel, retornamos.

		Calculamos entao os pontos:
		AB se posiciona entre A e B e sua altura eh a media entre as alturas de A e B + numero aleatorio.
		BC, CD e DA seguem a mesma logica.
		CT se posiciona no centro da area e tem como altura a media entre A, B, C, e D + numero aleatorio.

		Empilhamos todos os pontos calculados na pilha de picos.
		E finalmente chamamos a funcao diamondSquare novamente, para cada area que dividimos.
		Areas divididas:
			A, AB, CT, DA
			AB, B, BC, CT
			CT, BC, C, CD
			DA, CT, CD, D

		A--AB--B
		|      |
	  DA   CT  BC
		|      |
		D--CD--C
*/

class DiamondSquare
{
private:
    std::vector <Point <UFINT16> > picos;
public:
    DiamondSquare();
    ~DiamondSquare();

    void ini(Matriz m,Point<UFINT16> ini,Point<UFINT16> fim ,int rnd_cantos,int rnd_dif);

    void iterative(Matriz mat, int rnd);

    void recursive(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d, int rnd);

    void recursiveWrappable1(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d,int rnd);

    void recursiveWrappable2(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d,Point<UFINT16> ct,
                             Point<UFINT16> ab,Point<UFINT16> bc,Point<UFINT16> cd,Point<UFINT16> da, int rnd);

    void insereMatriz(Matriz m);

    void cleanUp();
};
#endif /*DIAMONDSQUARE_H_*/
