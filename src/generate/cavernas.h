#ifndef CAVERNA_H_
#define CAVERNA_H_


#include <iostream>
#include <math.h>
#include "../draw/draw.h"


class Caverna
{
private:
    UFINT8 numDir, wall_tile,floor_tile,empty_tile;
    UFINT16 vol;
    Point<int> *xy,*wh;
public:
    Caverna();
    ~Caverna();


	//argumentos:
	//	matriz a ser utilizada;
	//	tipos de tiles que vao compor as paredes, os chaos e o espaço vazio da caverna(nesta ordem);
	//	coordenada inicial da area em que a caverna sera gerada;
	//	coordenada final da area em que a caverna sera gerada;
	//	numero de direcoes disponiveis para se movimentar na caverna (4,6,8,27);
	//	volume maximo ocupado pela caverna;
    void iniCaverna(Matriz m,Point<UFINT8> tiles,Point<int> xy_i,Point<int> wh_i,UFINT8 numDir, UFINT16 vol);


    bool gerador3D(Matriz m);

};
#endif /*CAVERNA_H_*/
