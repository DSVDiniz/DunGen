#include "cavernas.h"
static int dirCardinais[][3] {{0,-1,0},{1,0,0},{0,1,0},{-1,0,0},{0,0,-1},{0,0,1}};
static int dirDiagonais[][3] {{0,-1,0},{1,-1,0},{1,0,0},{1,1,0},{0,1,0},{-1,1,0},{-1,0,0},{-1,-1,0},
    {0,0,-1},{0,-1,-1},{1,-1,-1},{1,0,-1},{1,1,-1},{0,1,-1},{-1,1,-1},{-1,0,-1},{-1,-1,-1},
    {0,0,1},{0,-1,1},{1,-1,1},{1,0,1},{1,1,1},{0,1,1},{-1,1,1},{-1,0,1},{-1,-1,1}
};

Caverna::Caverna()
{

}

Caverna::~Caverna()
{
    numDir=wall_tile=floor_tile=empty_tile=vol=0;
}

void Caverna::iniCaverna(Matriz m,Point<UFINT8> tiles,Point<int> xy_i,Point<int> wh_i,UFINT8 n, UFINT16 v)
{
    wall_tile=tiles.x;
    floor_tile=tiles.y;
    empty_tile=tiles.z;
    xy = &xy_i;
    wh = &wh_i;
    vol=v;
    numDir=n;
    gerador3D(m);
}

bool Caverna::gerador3D(Matriz m)
{
    UFINT16 aux,tentativa,k;
    int a=0;
    Point<int> curPos,oldPos;
    //pegamos um volume inicial

    tentativa = aux = k  = 0;
    k=1;

    //achando um ponto inicial
    curPos.set(Draw::rngi(wh->x	,xy->x),//x
               Draw::rngi(wh->y	,xy->y),//y
               Draw::rngi(wh->z	,xy->z),//z
               floor_tile);

    oldPos=curPos;

    //posicao inicial
    Draw::starPrint3D(m,curPos.x,curPos.y,curPos.z,curPos.t,wall_tile);

    //loop principal, checamos se chegamos ao volume desejado ou se já tentamos MAX_TENTATIVAS
    while ((k < vol)&&(tentativa<MAX_TENTATIVAS))
    {
        ++tentativa;

        switch(numDir)
        {
        case 4:
            a=Draw::rngi(4);
            curPos.add(dirCardinais[a][0],dirCardinais[a][1],dirCardinais[a][2]);
            break;
        case 6:
            a=Draw::rngi(6);
            curPos.add(dirCardinais[a][0],dirCardinais[a][1],dirCardinais[a][2]);
            break;
        case 8:
            a=Draw::rngi(8);
            curPos.add(dirDiagonais[a][0],dirDiagonais[a][1],dirDiagonais[a][2]);
            break;
        case 26:
            a=Draw::rngi(26);
            curPos.add(dirDiagonais[a][0],dirDiagonais[a][1],dirDiagonais[a][2]);
            break;
        }

        if((curPos.y>xy->y)&&(curPos.y<wh->y)//estamos nos limites do mapa?
                &&(curPos.x>xy->x)&&(curPos.x<wh->x)
                &&(curPos.z>xy->z)&&(curPos.z<wh->z))
        {
            aux = Draw::get(m,curPos.x,curPos.y,curPos.z);
            if((aux==empty_tile)||(aux==wall_tile))//caso a posicao nao foi ocupada
            {
                //inserir chao com paredes emvolta
                Draw::starPrint3D(m,curPos.x,curPos.y,curPos.z,curPos.t,wall_tile);
                ++k;//aumentar k, ja que ocupou mais um espaco no volume da m
            }
            oldPos = curPos;
        }
        else//caso nao estamos, voltamos pra posicao inicial
            curPos = oldPos;
    }
    k=0;

    if(tentativa >= MAX_TENTATIVAS)
        return false;
    else
        return true;
}
