#ifndef MATRIXTOQ3MAP_H_
#define MATRIXTOQ3MAP_H_

#include "defines.h"
#include "point.h"
#include "draw/draw.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <cstring>
#include <stdlib.h>
using namespace std;

class MatrixToMap
{
	private:
		string nomeMapa;
		int tamBloco;
		int brushNum;
	public:
		MatrixToMap(Matriz mat ,string nomeMapa, int tamBloco);
		MatrixToMap();
		~MatrixToMap();
		void ini(Matriz mat ,string nomeMapa, int tamBloco);
		string pointToBlock(Point<int>p);
		string pointToString(Point<int>p);
};
#endif /*MATRIXTOQ3MAP_H_*/
