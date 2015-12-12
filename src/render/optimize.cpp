#include "optimize.h"

UFINT8 Optimize::vec[TAMX*TAMY*TAMZ];
UFINT8 Optimize::m[TAMX][TAMY][TAMZ];

Optimize::Optimize()
{
}

Optimize::~Optimize()
{
}

inline bool Optimize::shellCheck(Matriz m,int x, int y, int z)
{
    if((m[x][y][z-1]!=0)&&(m[x][y-1][z]!=0)&&(m[x-1][y][z]!=0)&&(m[x+1][y][z])&&
            (m[x][y+1][z]!=0)&&(m[x][y][z+1]!=0))
        return false;
    else
        return true;

}

inline bool Optimize::shellCheckWater(Matriz m,int x, int y, int z)
{
    if((m[x][y][z-1]!=0)&&(m[x][y-1][z]!=0)&&(m[x-1][y][z]!=0)&&(m[x+1][y][z])&&
            (m[x][y+1][z]!=0)&&(m[x][y][z+1]!=0))
    {
        if((m[x][y][z-1]!=water9)&&(m[x][y-1][z]!=water9)&&(m[x-1][y][z]!=water9)&&(m[x+1][y][z])&&
                (m[x][y+1][z]!=water9)&&(m[x][y][z+1]!=water9))
        {
            return false;
        }
        else
            return true;
    }
    else
        return true;

}

void Optimize::matrizToVector(Matriz mat)
{
    int pos = 0;
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                    vec[pos]=mat[i][j][k];
                ++pos;
            }
}

void Optimize::matrizShell(Matriz mat)
{
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                {
                    if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                    {
                        if(shellCheck(mat,i,j,k))
                            m[i][j][k]=mat[i][j][k];
                    }
                    else
                    {
                        m[i][j][k]=mat[i][j][k];
                    }
                }
            }
}

void Optimize::matrizShellWater(Matriz mat)
{
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                {
                    if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                    {
                        if(shellCheckWater(mat,i,j,k))
                            m[i][j][k]=mat[i][j][k];
                    }
                    else
                    {
                        m[i][j][k]=mat[i][j][k];
                    }
                }
            }
}

/**completamente experimental, nem faz o que deveria direito**/
vector < vector< Point<UFINT8> > > Optimize::matrizLeastRectanglesEW(Matriz mat)
{
    bool junto = false;
    vector < vector< Point<UFINT8> > > retangulos;
    vector<Point<UFINT8> > aux;
    Point<UFINT8>p;

    for(unsigned int k = 0; k < TAMZ; ++k)
    {

        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(junto)
                {
                    if(mat[i][j][k]!=0)
                    {
                        if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                            p.set(i,j,k,mat[i][j][k]);
                    }
                    else
                    {
                        aux.push_back(p);
                        p.set(0,0,0,0);
                        junto=false;
                        retangulos.push_back(aux);
                        aux.clear();
                    }
                }
                else
                {
                    if(mat[i][j][k]!=0)
                    {
                        if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                        {
                            junto=true;
                            p.set(i,j,k,mat[i][j][k]);
                            aux.push_back(p);
                        }
                    }
                }
            }
    }
    return retangulos;
}

vector < vector< Point<UFINT8> > > Optimize::matrizLeastRectanglesNS(Matriz mat)
{
    bool junto = false;
    vector < vector< Point<UFINT8> > > retangulos;
    vector<Point<UFINT8> > aux;
    Point<UFINT8>p;

    for(unsigned int k = 0; k < TAMZ; ++k)
    {

        for(unsigned int i = 0; i < TAMX; ++i)
            for(unsigned int j = 0; j < TAMY; ++j)
            {
                if(junto)
                {
                    if(mat[i][j][k]!=0)
                    {
                        if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                            p.set(i,j,k,mat[i][j][k]);
                    }
                    else
                    {
                        aux.push_back(p);
                        p.set(0,0,0,0);
                        junto=false;
                        retangulos.push_back(aux);
                        aux.clear();
                    }
                }
                else
                {
                    if(mat[i][j][k]!=0)
                    {
                        if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                        {
                            junto=true;
                            p.set(i,j,k,mat[i][j][k]);
                            aux.push_back(p);
                        }
                    }
                }
            }
    }
    return retangulos;
}
