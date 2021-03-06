#include "diamondSquare.h"

DiamondSquare::DiamondSquare()
{

}

DiamondSquare::~DiamondSquare()
{

}
//calcula a media entre 2 numeros
inline int med2(int a,int b)
{
    return ceil((a+b)/2);
}

//calcula a media entre 3 numeros
inline int med3(int a,int b,int c)
{
    return ceil((a+b+c)/3);
}

//calcula a media entre 4 numeros
inline int med4(int a,int b,int c,int d)
{
    return ceil((a+b+c+d)/4);
}

//Inicia a geracao de terreno
void DiamondSquare::ini(Matriz m,Point<UFINT16> ini,Point<UFINT16> fim ,int rnd_cantos,int rnd_dif)
{
    //Primeiro setamos quatro pontos, cada um localizado em um canto do quadrado(mapa ou regiao)
    //	X---X
    //	|	|
    //	X---X
    //cada um com um valor aletorio na altura Z

    //a matriz precisa ser de tamanho impar na altura e largura
    if( (((fim.x-1)%2)!=0) && (((fim.y-1)%2)!=0) && (((fim.x-1)%9)!=0) && (((fim.x-1)%9)!=0) )
    {
        Point<UFINT16> a=*new Point<UFINT16>(ini.x,		ini.y,		Draw::rngi(rnd_cantos),ini.t);
        Point<UFINT16> b=*new Point<UFINT16>(fim.x-1,	ini.y,		Draw::rngi(rnd_cantos),ini.t);
        Point<UFINT16> c=*new Point<UFINT16>(fim.x-1,	fim.y-1,	Draw::rngi(rnd_cantos),ini.t);
        Point<UFINT16> d=*new Point<UFINT16>(ini.x,		fim.y-1,	Draw::rngi(rnd_cantos),ini.t);

        //inserimos os pontos no vetor de picos(que sera depois usado para a insercao na matriz do mapa)
        picos.push_back(a);
        picos.push_back(b);
        picos.push_back(c);
        picos.push_back(d);

        //chamamos a funcao principal do diamond-square
        recursive(a,b,c,d,rnd_dif-1);
        //recursiveWrappable1(a,b,c,d,rnd_dif-1);

        //pegamos a matriz do mapa e alteramos ela
        insereMatriz(m);
    }

}
/**ALGORITMO DIAMOND-SQUARE**/
/**
		A--AB--B
		|      |
	   DA  CT  BC
		|  	   |
		D--CD--C
*/

/*void DiamondSquare::iterative(Matriz mat, std::vector< Point<UFINT16> > cantos, int rnd)
{
	int a,b,c,d,e,f,g,h,ct;
	a=b=c=d=e=f=g=h=ct=0;

	mat[cantos[0].x]	[cantos[0].y]	[0] = a = Draw::rngi(rnd);
	mat[cantos[1].x]	[cantos[0].y]	[0] = b = Draw::rngi(rnd);
	mat[cantos[1].x]	[cantos[1].y]	[0] = c = Draw::rngi(rnd);
	mat[cantos[0].x]	[cantos[1].y]	[0] = d = Draw::rngi(rnd);

	mat[cantos[1].x/2]	[cantos[0].y]	[0] = e = med2(a,b);
	mat[cantos[1].x/2]	[cantos[1].y]	[0] = f = med2(b,c);
	mat[cantos[0].x]	[cantos[1].y/2]	[0] = g = med2(c,d);
	mat[cantos[0].x]	[cantos[1].y/2]	[0] = h = med2(d,a);

	mat[cantos[1].x/2]	[cantos[1].y/2]	[0] = ct = med4(e,f,g,h);

	while(true)
	{

	}

}*/

void DiamondSquare::recursive(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d, int rnd)
{
    Point<UFINT16> ab,bc,cd,da,ct;

    if(rnd<0)
        rnd = 1;

    if((c.x-a.x>1)&&(c.y-a.y>1))
    {
        int xaux = ceil(((c.x-a.x)/2)+a.x),	yaux =ceil(((c.y-a.y)/2)+a.y);

        ct 		= *new Point<UFINT16>(xaux,	yaux,	med4(a.z,b.z,c.z,d.z)+Draw::rngi(rnd)			,1);
        ab 		= *new Point<UFINT16>(xaux,	a.y,	med3(a.z,b.z,ct.z)+Draw::rngi(rnd)				,1);
        bc 		= *new Point<UFINT16>(b.x,	yaux,	med3(b.z,c.z,ct.z)+Draw::rngi(rnd)				,1);
        cd 		= *new Point<UFINT16>(xaux,	c.y,	med3(c.z,d.z,ct.z)+Draw::rngi(rnd)				,1);
        da 		= *new Point<UFINT16>(d.x,	yaux,	med3(d.z,a.z,ct.z)+Draw::rngi(rnd)				,1);

        picos.push_back(ab);
        picos.push_back(bc);
        picos.push_back(cd);
        picos.push_back(da);
        picos.push_back(ct);

        recursive(a,ab,ct,da,rnd-1);
        recursive(ab,b,bc,ct,rnd-1);
        recursive(ct,bc,c,cd,rnd-1);
        recursive(da,ct,cd,d,rnd-1);
    }
    else
        return;
}

void DiamondSquare::recursiveWrappable1(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d,int rnd)
{
    Point<UFINT16> ct,ab,bc,cd,da;

    if(rnd<0)
        rnd = 1;

    if((c.x-a.x>1)&&(c.y-a.y>1))
    {
        int xaux = floor(((c.x-a.x)/2)+a.x),	yaux =floor(((c.y-a.y)/2)+a.y);

        ct 	= *new Point<UFINT16>(xaux,	yaux,	med4(a.z,b.z,c.z,d.z)+Draw::rngi(rnd)	,1);
        ab 	= *new Point<UFINT16>(xaux,	a.y,	med4(a.z,b.z,ct.z,ct.z)+Draw::rngi(rnd)	,1);
        bc 	= *new Point<UFINT16>(b.x,	yaux,	med4(b.z,c.z,ct.z,ct.z)+Draw::rngi(rnd)	,1);
        cd 	= *new Point<UFINT16>(xaux,	c.y,	med4(c.z,d.z,ct.z,ct.z)+Draw::rngi(rnd)	,1);
        da 	= *new Point<UFINT16>(d.x,	yaux,	med4(d.z,a.z,ct.z,ct.z)+Draw::rngi(rnd)	,1);

        picos.push_back(ct);
        picos.push_back(ab);
        picos.push_back(bc);
        picos.push_back(cd);
        picos.push_back(da);

        recursiveWrappable2(a,b,c,d,ct,ab,bc,cd,da,rnd-1);
    }
    else
        return;
}

void DiamondSquare::recursiveWrappable2(Point<UFINT16> a,Point<UFINT16> b ,Point<UFINT16> c ,Point<UFINT16> d,Point<UFINT16> ct,
                                        Point<UFINT16> ab,Point<UFINT16> bc,Point<UFINT16> cd,Point<UFINT16> da, int rnd)
{
    Point<UFINT16> c1,c2,c3,c4,e,f,g,h,i,j,k,l,m,n,o,p;

    if(rnd<0)
        rnd = 1;

    if((c.x-a.x>1)&&(c.y-a.y>1))
    {
        int xaux1 = floor(((ct.x-a.x)/2)+a.x),		yaux1 = floor(((ct.y-a.y)/2)+a.y),
            xaux2 = floor(((bc.x-ab.x)/2)+ab.x),	yaux2 = floor(((bc.y-ab.y)/2)+ab.y),
            xaux3 = floor(((c.x-ct.x)/2)+ct.x),		yaux3 = floor(((c.y-ct.y)/2)+ct.y),
            xaux4 = floor(((da.x-cd.x)/2)+cd.x),	yaux4 = floor(((da.y-cd.y)/2)+cd.y);

        c1 	= *new Point<UFINT16>(xaux1,yaux1,	med4(a.z,ab.z,ct.z,da.z)+Draw::rngi(rnd),	1);
        c2	= *new Point<UFINT16>(xaux2,yaux2,	med4(ab.z,b.z,bc.z,ct.z)+Draw::rngi(rnd),	1);
        c3 	= *new Point<UFINT16>(xaux3,yaux3,	med4(ct.z,bc.z,c.z,cd.z)+Draw::rngi(rnd),	1);
        c4 	= *new Point<UFINT16>(xaux4,yaux4,	med4(da.z,ct.z,cd.z,d.z)+Draw::rngi(rnd),	1);

        e 	= *new Point<UFINT16>(xaux1,a.y,	med4(c1.z,a.z,ab.z,c4.z)+Draw::rngi(rnd),	1);
        f 	= *new Point<UFINT16>(xaux2,b.y,	med4(ab.z,b.z,c2.z,c3.z)+Draw::rngi(rnd),	1);
        g 	= *new Point<UFINT16>(b.x,	yaux2,	med4(c1.z,c2.z,b.z,bc.z)+Draw::rngi(rnd),	1);
        h 	= *new Point<UFINT16>(c.x,	yaux3,	med4(c3.z,c4.z,bc.z,c.z)+Draw::rngi(rnd),	1);
        i 	= *new Point<UFINT16>(xaux3,c.y,	med4(c.z,cd.z,c3.z,c2.z)+Draw::rngi(rnd),	1);
        j 	= *new Point<UFINT16>(xaux4,d.y,	med4(c1.z,c4.z,d.z,cd.z)+Draw::rngi(rnd),	1);
        k 	= *new Point<UFINT16>(d.x,	yaux4,	med4(c4.z,c3.z,d.z,da.z)+Draw::rngi(rnd),	1);
        l 	= *new Point<UFINT16>(a.x,	yaux1,	med4(c1.z,c2.z,da.z,a.z)+Draw::rngi(rnd),	1);

        m 	= *new Point<UFINT16>(ct.x,	c1.y,	med4(c1.z,c2.z,ab.z,ct.z)+Draw::rngi(rnd),	1);
        n 	= *new Point<UFINT16>(c2.x, ct.y,	med4(c2.z,c3.z,bc.z,ct.z)+Draw::rngi(rnd),	1);
        o 	= *new Point<UFINT16>(ct.x,	c3.y,	med4(c3.z,c4.z,cd.z,ct.z)+Draw::rngi(rnd),	1);
        p 	= *new Point<UFINT16>(c1.x, ct.y,	med4(c4.z,c1.z,da.z,ct.z)+Draw::rngi(rnd),	1);

        picos.push_back(c1);
        picos.push_back(c2);
        picos.push_back(c3);
        picos.push_back(c4);

        picos.push_back(e);
        picos.push_back(f);
        picos.push_back(g);
        picos.push_back(h);
        picos.push_back(i);
        picos.push_back(j);
        picos.push_back(k);
        picos.push_back(l);
        picos.push_back(m);
        picos.push_back(n);
        picos.push_back(o);
        picos.push_back(p);

        recursiveWrappable2(a,ab,ct,da,c1,e,m,p,l,rnd-1);
        recursiveWrappable2(ab,b,bc,ct,c2,f,g,n,m,rnd-1);
        recursiveWrappable2(ct,bc,c,cd,c3,n,h,i,o,rnd-1);
        recursiveWrappable2(da,ct,cd,d,c4,p,o,j,k,rnd-1);
    }
    else
        return;
}

//insere os valores de picos nas posicoes da matriz e limpa o vetor de picos
void DiamondSquare::insereMatriz(Matriz m)
{
    for(unsigned int l = 0; l<picos.size(); ++l)
        for(unsigned int k = 0; k < picos[l].z; ++k)
        {
            m[picos[l].x][picos[l].y][k]=k+1;
        }
    cleanUp();
}

//limpa o vetor de picos
void DiamondSquare::cleanUp()
{
    picos.clear();
}
