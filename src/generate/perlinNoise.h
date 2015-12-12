#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../draw/draw.h"
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

class PerlinNoise
{
private:
    std::vector <int> pRand;
    std::vector <double> pontos;
public:
    PerlinNoise();
    ~PerlinNoise();

    void ini2d(Matriz mat, int oct, double pers, double amp);
    void ini3d(Matriz mat, int oct, double pers, double amp,double d_min,double d_max);
    void shuffle_permutationTable();

    double noise(double x, double y, double z);
    double noise(double x, double y);

};
#endif /*PERLINNOISE_H_*/
