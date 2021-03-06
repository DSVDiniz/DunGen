#include "draw.h"

/**
	@function:rngi
	@param: maximo e minimo
	@return: numero aleatorio entre maximo e minimo.
	@description:gerador de numeros aleatorios
**/
int Draw::rngi(int max, int min)
{
    //se o maximo for igual ao minimo, retornar maximo
    if(max!=min)
    {
        if(max!=0)//se max for igual a zero, retornamos zero
            return min+rand() % (max-min);
        else
            return 0;
    }
    else
        return max;
}

/**
	@function: newSeed
	@param: a seed desejada
	@return: void
	@description:usada para setar uma nova seed de numeros aleatorios
**/
void Draw::newSeed(int seed)
{
    srand(seed);
}

/**

	@function:getTilePosition
	@param: matriz onde se quer procurar o tile e o tipo do tile
	@return: a lista de pontos de tiles
	@description: pega a posicao de todos os tiles do tipo especificado
**/
std::list <Point<UFINT16> > Draw::getTilePosition(Matriz m, unsigned int t)
{
    std::list<Point<UFINT16> > aux;
    Point<UFINT16> a;
    for(int k = 0; k < TAMZ; ++k)
        for(int j = 0; j < TAMY; ++j)
            for(int i = 0; i < TAMX; ++i)
                if(m[i][j][k]==t)
                {
                    a.set(i,j,k,t);
                    aux.push_back(a);
                }
    return aux;
}


/**
	@function:getTilePosWater
	@param: matriz onde se quer procurar os tiles de agua
	@return: a lista de pontos de tiles
	@description: pega a posicao de todos os tiles de agua
	Obs: essa funcao existe pois ha varios tiles considerados como "agua"
	a funcao getTilePos poderia ser usada multiplas vezes com os mesmos resultados, mas
	isso seria muito mais lento e ineficiente.
**/
std::list <Point<UFINT16> > Draw::getTilePosWater(Matriz m)
{
    std::list<Point<UFINT16> > aux;
    Point<UFINT16> a;
    for(int k = 0; k < TAMZ; ++k)
        for(int j = 0; j < TAMY; ++j)
            for(int i = 0; i < TAMX; ++i)
            {
                if((m[i][j][k]>=water1)&&(m[i][j][k]<=water9))
                {
                    a.set(i,j,k,m[i][j][k]);
                    aux.push_front(a);
                }
            }
    return aux;
}
std::deque <Point<UFINT16> > Draw::getTilePosWaterDeque(Matriz m)
{
    std::deque<Point<UFINT16> > aux;
    Point<UFINT16> a;
    for(int k = 0; k < TAMZ; ++k)
        for(int j = 0; j < TAMY; ++j)
            for(int i = 0; i < TAMX; ++i)
            {
                if((m[i][j][k]>=water1)&&(m[i][j][k]<=water9))
                {
                    a.set(i,j,k,m[i][j][k]);
                    aux.push_front(a);
                }
            }
    return aux;
}

/**
	@function:get
	@param: matriz onde se quer procurar o tile e as coordenadas do tile(inteiros)
	@return: o tipo do tile
	@description: pega o tipo do tle na posicao desejada em uma matriz
	Obs: se as coordenadas nao estiverem dentro dos limites da matriz, 255 eh retornado
**/
UFINT8 Draw::get(Matriz m ,int x, int y, int z)
{
    if((x<TAMX)&&(x>0)&&(y<TAMY)&&(y>0)&&(z<TAMZ)&&(z>0))
        return m[x][y][z];
    else
        return 255;
}
UFINT8 Draw::get(Matriz m ,Point<UFINT16> p)
{
    if((p.x<TAMX)&&(p.x>0)&&(p.y<TAMY)&&(p.y>0)&&(p.z<TAMZ)&&(p.z>0))
        return m[p.x][p.y][p.z];
    else
        return 255;
}

/**
	@function: insert
	@param: matriz onde se quer procurar o tile, coordenadas do tile e tipo do tile
	@return: o tipo do tile
	@description: insere na matriz nas coordenadas desejadas um tile do tipo desejado
	Obs:se nao esta dentro dos limites da matriz, nada eh feito
**/
bool Draw::insert(Matriz m ,int x, int y, int z, int t)
{
    if((x<TAMX)&&(x>0)&&(y<TAMY)&&(y>0)&&(z<TAMZ)&&(z>0))
	{
		m[x][y][z]=t;
		return true;
	}
	else
		return false;

}
bool Draw::insert(Matriz m ,Point<UFINT16> p)
{
    if((p.x<TAMX)&&(p.x>0)&&(p.y<TAMY)&&(p.y>0)&&(p.z<TAMZ)&&(p.z>0))
	{
        m[p.x][p.y][p.z]=p.t;
        return true;
	}
	else
		return false;
}

/**
	@function: checkArea
	@param: matriz, coordenadas do canto 1 , coordenadas do canto 2, tipo a ser procurado
	@return: true ou false
	@description: procura em uma area (limitada por dois pontos num espaco 3d, ou seja, um cubo ou quadrado)
	um tipo de tile. Se este tipo de tile eh encontrado, retorna true. Caso contrario, false.
	Obs:se nao esta dentro dos limites da matriz, nada eh feito
**/
bool Draw::checkArea(Matriz m, Point<UFINT16>xy, Point<UFINT16>wh, UFINT8 t)
{
    for(UFINT16 k = xy.z; k < wh.z; ++k)
        for(UFINT16 j = xy.y; j < wh.y; ++j)
            for(UFINT16 i = xy.x; i < wh.x; ++i)
            {
                if(m[i][j][k]==t)
                    return false;
            }
    return true;
}
/**
	Mesma funcao.
	Unica difereca: trata um vetor de tipos.
**/
bool Draw::checkArea(Matriz m, Point<UFINT16>xy, Point<UFINT16>wh, std::vector<UFINT8> tipos)
{
    for(UFINT16 k = xy.z; k < wh.z; ++k)
        for(UFINT16 j = xy.y; j < wh.y; ++j)
            for(UFINT16 i = xy.x; i < wh.x; ++i)
                for(UFINT8 l = 0; l<tipos.size(); ++l)
                {
                    if(m[i][j][k]==tipos[l])
                        return false;
                }
    return true;
}

/**
	@function: getHighLow
	@param: matriz, um caractere que repesenta o eixo desejado (X, Y, Z)
	@return: retorna o valor minimo e maximo dos pontos inseridos na matriz em um Point<int>, onde o maximo eh x e y eh o minimo.
	@description: checa qual o ponto minimo e qual o ponto maximo (ignorando espacos vazios) em relacao ao eixo escolhido.
**/
Point<int>Draw::getHighLow(Matriz m, char eixo)
{
    int high=0, low=0;
    switch (eixo)
    {
    case 'Z':
    case 'z':
        low=TAMZ;
        for(int k = 0; k < TAMZ; ++k)
            for(int j = 0; j < TAMY; ++j)
                for(int i = 0; i < TAMX; ++i)
                {
                    if(m[i][j][k]!=air)
                    {
                        if(k<low)
                            low=k;
                        if(k>high)
                            high=k;
                    }
                }
        break;

    case 'Y':
    case 'y':
        low=TAMY;
        for(int k = 0; k < TAMZ; ++k)
            for(int j = 0; j < TAMY; ++j)
                for(int i = 0; i < TAMX; ++i)
                {
                    if(m[i][j][k]!=air)
                    {
                        if(j<low)
                            low=j;
                        if(j>high)
                            high=j;
                    }
                }
        break;
    case 'X':
    case 'x':
        low=TAMX;
        for(int k = 0; k < TAMZ; ++k)
            for(int j = 0; j < TAMY; ++j)
                for(int i = 0; i < TAMX; ++i)
                {
                    if(m[i][j][k]!=air)
                    {
                        if(i<low)
                            low=i;
                        if(i>high)
                            high=i;
                    }
                }
        break;
    }
    return *new Point<int>(high,low);
}

/**
	@function: countType
	@param: matriz, tipo
	@return: int
	@description: procura na matriz inteira pontos do tipo desejado e conta quantos foram encontrados
	em toda a matriz.
**/
int Draw::countType(Matriz m, unsigned int t)
{
    int sum=0;
    for(int k = 0; k < TAMZ; ++k)
        for(int j = 0; j < TAMY; ++j)
            for(int i = 0; i < TAMX; ++i)
            {
                if(m[i][j][k]==t)
                    ++sum;
            }
    return sum;
}
