#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include "../draw/draw.h"
#include <algorithm>

//TOU COM PREGUICA
class Labirinto
{
private:
    std::vector <Point<UFINT16>*>direcoes;
    Point<UFINT16> wh, xy, limInf, limSup;
    int step;
public:
    Labirinto();


    //argumentos:
	//	matriz a ser utilizada;
	//	coordenada inicial do labirinto;
	//	dimensoes do labirinto
	//	espacamento, ou tamanho dos passos no labirinto;
    Labirinto(Matriz m,Point<UFINT16> pos,Point<UFINT16> dim,int stepsize);

    virtual ~Labirinto();
    int rngi(int max, int min=0);
    void depthFirst(Matriz m,Point<UFINT16> xy);
    void depthFirstBacktracker(Point<UFINT16> xy);
    std::vector<Point<UFINT16> > checkVizinhos(Matriz m,Point<UFINT16> i);
    Point<UFINT16> ligaVizinho(Matriz m,Point<UFINT16> i,Point<UFINT16>f);
    Point<UFINT16> ligaVizinhoEsferico(Matriz m,Point<UFINT16> i, Point<UFINT16> f);
    std::vector<Point<UFINT16> > checkVizinhosEsf(Matriz m ,Point<UFINT16> i);
};
#endif /*LABIRINTO_H_*/
