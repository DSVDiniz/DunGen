#ifndef OPTIMIZE_H_
#define OPTIMIZE_H_

#include "../defines.h"
#include "inttypes.h"
#include "../point.h"

#include <vector>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;
#ifdef TESTANDOMATRIZ
	typedef std::vector <std::vector <std::vector <UFINT8> > > Matriz;
#else
	typedef UFINT16 Matriz [TAMX][TAMY][TAMZ];
#endif

class Optimize
{
private:
    static UFINT8 vec[TAMX*TAMY*TAMZ];
    static UFINT8 m[TAMX][TAMY][TAMZ];
public:
    Optimize();
    virtual ~Optimize();
    inline bool shellCheck(Matriz m,int x, int y, int z);

    inline bool shellCheckWater(Matriz m,int x, int y, int z);

    void matrizToVector(Matriz mat);

    void matrizShell(Matriz mat);

    void matrizShellWater(Matriz mat);


    vector < vector< Point<UFINT8> > > matrizLeastRectanglesEW(Matriz mat);
    vector < vector< Point<UFINT8> > > matrizLeastRectanglesNS(Matriz mat);

};

#endif /*OPTIMIZE_H_*/
