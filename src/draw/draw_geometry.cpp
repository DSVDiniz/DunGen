#include "draw.h"

void Draw::ponto(Matriz m,Point<UFINT16> pt)
{
    m[pt.x][pt.y][pt.z]=pt.t;
}

void Draw::ponto(Matriz m,UFINT8 tipo,UFINT16 x,UFINT16 y,UFINT16 z)
{
    m[x][y][z]=tipo;
}

void Draw::simpSqrFill(Matriz m, Point<UFINT16> xy, Point<UFINT16> wh)
{
    for(UFINT16 k = xy.z; k <= wh.z; ++k)
        for(UFINT16 j = xy.y; j <= wh.y; ++j)
            for(UFINT16 i = xy.x; i <= wh.x; ++i)
            {
                m[i][j][k]=xy.t;
            }
}

void Draw::sqrFill(Matriz m,Point<UFINT16> p1,Point<UFINT16> p2,Point<UFINT16> p3, Point<UFINT16> limInf, Point<UFINT16> limSup)
{
    float A, B, C, D;
    Point<UFINT16> xy , wh;
    xy = wh = *new Point<UFINT16>();
    A=B=C=D=0;

    A 	= p1.y*(p2.z - p3.z) + p2.y*(p3.z - p1.z) + p3.y*(p1.z - p2.z);
    B 	= p1.z*(p2.x - p3.x) + p2.z*(p3.x - p1.x) + p3.z*(p1.x - p2.x);
    C 	= p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y - p2.y);
    D 	= -(p1.x*(p2.y*p3.z - p3.y*p2.z) + p2.x*(p3.y*p1.z - p1.y*p3.z) + p3.x*(p1.y*p2.z - p2.y*p1.z));

    std::cout<<"A: "<<A<<" B: "<<B<<" C: "<<C<<" D: "<<D<<std::endl;

    if((A==0)&&(B==0))
    {
        //no eixo z?
        xy.x=p1.x;
        wh.x=p3.x;
        xy.y=p1.y;
        wh.x=p3.y;
        xy.z=p1.z;
        wh.x=p3.z;
    }
    else
    {
        if((C==0)&&(B==0))
        {
            //no eixo y?
            xy.x=p1.x;
            wh.x=p3.x;
            xy.y=p1.y;
            wh.x=p3.y;
            xy.z=p1.z;
            wh.x=p3.z;
        }
        else
        {
            if((A==0)&&(C==0))
            {
                //no eixo x?
                xy.x=p1.x;
                wh.x=p3.x;
                xy.y=p1.y;
                wh.x=p3.y;
                xy.z=p1.z;
                wh.x=p3.z;
            }
            else
            {
                for(			UFINT16 k = limInf.z;	k < limSup.z; ++k)
                    for(		UFINT16 j = limInf.y;	j < limSup.y; ++j)
                        for(	UFINT16 i = limInf.x;	i < limSup.x; ++i)
                        {
                            //A*i+B*j+C*k+D = s //se s<0 pt no lado abaixo, s>0 lado da normal, s=0 no plano
                            if((A*i + B*j + C*k + D <= 5.0)&&(A*i + B*j + C*k + D >= -5.0))
                                m[i][j][k]=1;
                        }
                return;
            }
        }
    }

    for(			UFINT16 k = xy.z	; k < wh.z; ++k)
        for(		UFINT16 j = xy.y	; j < wh.y; ++j)
            for(	UFINT16 i = xy.x	; i < wh.x; ++i)
            {
                m[i][j][k]=1;
            }
}

inline void Draw::areaPrint2D(Matriz m, Point<int> xy,UFINT8 t1,UFINT8 t2)
{
    m[xy.x-1]	[xy.y-1]	[xy.z]=t2;
    m[xy.x]		[xy.y-1]	[xy.z]=t2;
    m[xy.x+1]	[xy.y-1]	[xy.z]=t2;
    m[xy.x-1]	[xy.y]		[xy.z]=t2;
    m[xy.x]		[xy.y]		[xy.z]=t1;
    m[xy.x+1]	[xy.y]		[xy.z]=t2;
    m[xy.x-1]	[xy.y+1]	[xy.z]=t2;
    m[xy.x]		[xy.y+1]	[xy.z]=t2;
    m[xy.x+1]	[xy.y+1]	[xy.z]=t2;
}
inline void Draw::starPrint2D(Matriz m, Point<int> xy,UFINT8 t1,UFINT8 t2)
{
    m[xy.x]	[xy.y-1]	[xy.z]=t2;
    m[xy.x-1]	[xy.y]		[xy.z]=t2;
    m[xy.x]	[xy.y]		[xy.z]=t1;
    m[xy.x+1]	[xy.y]		[xy.z]=t2;
    m[xy.x]	[xy.y+1]	[xy.z]=t2;
}
void Draw::areaPrint3D(Matriz m, Point<int> xy,UFINT8 t1,UFINT8 t2)
{
    areaPrint2D(m,	xy.x,xy.y,xy.z+1,t2	,t2);
    areaPrint2D(m,	xy				,t1	,t2);
    areaPrint2D(m,	xy.x,xy.y,xy.z-1,t2	,t2);
}
void Draw::starPrint3D(Matriz m, Point<int> xy,UFINT8 t1,UFINT8 t2)
{
    starPrint2D(m,	xy.x,xy.y,xy.z+1,t2	,t2);
    areaPrint2D(m,	xy				,t1	,t2);
    starPrint2D(m,	xy.x,xy.y,xy.z-1,t2	,t2);
}

inline void Draw::areaPrint2D(Matriz m, int x, int y, int z,UFINT8 t1,UFINT8 t2)
{
    m[x-1][y-1][z]=t2;
    m[x][y-1][z]=t2;
    m[x+1][y-1][z]=t2;
    m[x-1][y][z]=t2;
    m[x][y][z]=t1;
    m[x+1][y][z]=t2;
    m[x-1][y+1][z]=t2;
    m[x][y+1][z]=t2;
    m[x+1][y+1][z]=t2;
}
inline void Draw::starPrint2D(Matriz m, int x, int y, int z,UFINT8 t1,UFINT8 t2)
{
    m[x][y-1][z]=t2;
    m[x-1][y][z]=t2;
    m[x][y][z]=t1;
    m[x+1][y][z]=t2;
    m[x][y+1][z]=t2;
}
void Draw::areaPrint3D(Matriz m, int x, int y, int z,UFINT8 t1,UFINT8 t2)
{
    areaPrint2D(m,	x,y,z+1	,t2	,t2);
    areaPrint2D(m,	x,y,z	,t1	,t2);
    areaPrint2D(m,	x,y,z-1	,t2	,t2);
}
void Draw::starPrint3D(Matriz m, int x, int y, int z,UFINT8 t1,UFINT8 t2)
{
    m[x][y][z+2]=t2;
    m[x][y+2][z]=t2;
    m[x+2][y][z]=t2;
    starPrint2D(m,	x,y,z+1	,t2	,t2);
    areaPrint2D(m,	x,y,z	,t1	,t2);
    starPrint2D(m,	x,y,z-1	,t2	,t2);
    m[x][y][z-2]=t2;
    m[x][y-2][z]=t2;
    m[x-2][y][z]=t2;
}

void Draw::linha(Matriz m,Point<UFINT16> ini,Point<UFINT16> fim)
{
    Point <UFINT16> aux;
    float dx=(int)(fim.x-ini.x), dy=(int)(fim.y-ini.y), dz=(int)(fim.z-ini.z);
    float diag = sqrt((dx*dx)+(dy*dy)+(dz*dz));
    dx=dx/diag;
    dy=dy/diag;
    dz=dz/diag;
    for(int i=0; i<diag; ++i)
    {
        aux = *new Point<UFINT16>((UFINT16)(i*dx)+ini.x,(UFINT16) (i*dy)+ini.y,(UFINT16) (i*dz)+ini.z,ini.t);
        m[aux.x][aux.y][aux.z]=aux.t;
    }
}

void Draw::linha(Matriz m,UFINT8 tipo,UFINT16 ix,UFINT16 fx,UFINT16 iy,UFINT16 fy,UFINT16 iz,UFINT16 fz)
{
    Point <UFINT16> aux;
    float dx=(int)fx-ix, dy=(int)fy-iy, dz=(int)fz-iz;
    float diag = sqrt((dx*dx)+(dy*dy)+(dz*dz));
    dx=dx/diag;
    dy=dy/diag;
    dz=dz/diag;
    for(int i=0; i<diag; ++i)
    {
        aux = *new Point<UFINT16>((UFINT16)(i*dx)+ix,(UFINT16) (i*dy)+iy,(UFINT16) (i*dz)+iz,tipo);
        m[aux.x][aux.y][aux.z]=aux.t;
    }
}

void Draw::rectangleWire(Matriz m,Point<UFINT16> a,Point<UFINT16> b,Point<UFINT16> c,Point<UFINT16> d)
{
    linha(m,a,b);
    linha(m,b,c);
    linha(m,c,d);
    linha(m,d,a);
}

void Draw::simpRectangleWire(Matriz m,Point<UFINT16> a,Point<UFINT16> c)
{
    Point<UFINT16> b = *new Point<UFINT16>(c.x,a.y,a.z,a.t);
    Point<UFINT16> d = *new Point<UFINT16>(a.x,c.y,a.z,a.t);
    linha(m,a,b);
    linha(m,b,c);
    linha(m,c,d);
    linha(m,d,a);
}

void Draw::cuboideWire(Matriz m,std::vector < Point<UFINT16> > pts)
{
    //pts a,b,c,d,
    //    e,f,g,h horario
    rectangleWire(m,pts[0],pts[1],pts[2],pts[3]);
    linha(m,pts[0],pts[4]);
    linha(m,pts[1],pts[5]);
    linha(m,pts[2],pts[6]);
    linha(m,pts[3],pts[7]);
    rectangleWire(m,pts[4],pts[5],pts[6],pts[7]);
}

void Draw::simpCuboideWire(Matriz m,Point<UFINT16>a,Point<UFINT16>g)
{
    //pts a,b,c,d,
    //    e,f,g,h horario
    Point<UFINT16> b = *new Point<UFINT16>(g.x,a.y,a.z,a.t);
    Point<UFINT16> c = *new Point<UFINT16>(g.x,g.y,a.z,a.t);
    Point<UFINT16> d = *new Point<UFINT16>(a.x,g.y,a.z,a.t);

    Point<UFINT16> e = *new Point<UFINT16>(a.x,a.y,g.z,a.t);
    Point<UFINT16> f = *new Point<UFINT16>(g.x,a.y,g.z,a.t);
    Point<UFINT16> h = *new Point<UFINT16>(a.x,g.y,g.z,a.t);

    simpRectangleWire(m,a,c);
    linha(m,a,e);
    linha(m,b,f);
    linha(m,c,g);
    linha(m,d,h);
    simpRectangleWire(m,e,g);
}

void Draw::simpCuboideShell(Matriz m,Point<UFINT16>a,Point<UFINT16>dim)
{
    //pts a,b,c,d,
    //    e,f,g,h horario
    Point<UFINT16> g = *new Point<UFINT16>(a.x+dim.x,	a.y+dim.y,	a.z+dim.z,	a.t);

    Point<UFINT16> b = *new Point<UFINT16>(g.x,	a.y,	a.z,	a.t);
    Point<UFINT16> c = *new Point<UFINT16>(g.x,	g.y,	a.z,	a.t);
    Point<UFINT16> d = *new Point<UFINT16>(a.x,	g.y,	a.z,	a.t);

    Point<UFINT16> e = *new Point<UFINT16>(a.x,	a.y,	g.z,	a.t);
    Point<UFINT16> f = *new Point<UFINT16>(g.x,	a.y,	g.z,	a.t);
    Point<UFINT16> h = *new Point<UFINT16>(a.x,	g.y,	g.z,	a.t);

    simpSqrFill(m,a,c);
    simpSqrFill(m,e,g);

    simpSqrFill(m,a,h);
    simpSqrFill(m,b,g);

    simpSqrFill(m,d,g);
    simpSqrFill(m,a,f);
}

void Draw::poligono(Matriz m,Point<UFINT16> centro,UFINT16 arestas, UFINT16 raio,UFINT16 angulo)
{
    float step=360/arestas;
    float angAux		=	0;
    float angStepAux	=	0;
    for(UFINT16 i=0; i<arestas; ++i)
    {
        angulo+=step;
        angAux		=	angulo*RAD;
        angStepAux	=	(angulo+step)*RAD;
        linha(m,centro.t,(cos(angAux)		*raio)+centro.x,
              (cos(angStepAux)	*raio)+centro.x,
              (sin(angAux)		*raio)+centro.y,
              (sin(angStepAux)	*raio)+centro.y,
              centro.z,
              centro.z);
    }
}

void Draw::circulo(Matriz m,Point<UFINT16> centro, int raio)
{
    float cosAux, senAux,cosAuxRAlt, senAuxRAlt;
    for(UFINT16 i=0; i<90; ++i)
    {
        cosAux 		= cos(i*RAD)*raio;
        cosAuxRAlt 	= cos(i*RAD)*(raio-0.2);
        senAux 		= sin(i*RAD)*raio;
        senAuxRAlt 	= sin(i*RAD)*(raio-0.2);
        //circulo inicial
        ponto(m,centro.t,centro.x+(cosAux),centro.y,centro.z+(senAux));
        ponto(m,centro.t,centro.x-(cosAux),centro.y,centro.z-(senAux));
        ponto(m,centro.t,centro.x+(cosAux),centro.y,centro.z-(senAux));
        ponto(m,centro.t,centro.x-(cosAux),centro.y,centro.z+(senAux));
        //arredondamento
        ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y,centro.z+(senAuxRAlt));
        ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y,centro.z-(senAuxRAlt));
        ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y,centro.z-(senAuxRAlt));
        ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y,centro.z+(senAuxRAlt));
    }
}

void Draw::circulo(Matriz m,Point<UFINT16> centro, Point<UFINT16> superficie1,Point<UFINT16> superficie2)
{
    int dx1,dy1,dz1,dx2,dy2,dz2,raio=0;
    float cosAux, senAux,cosAuxRAlt, senAuxRAlt;
    dx1=centro.x-superficie1.x;
    dy1=centro.y-superficie1.y;
    dz1=centro.z-superficie1.z;
    dx2=centro.x-superficie2.x;
    dy2=centro.y-superficie2.y;
    dz2=centro.z-superficie2.z;

    if((dz1==0)&&(dz2==0))
    {
        raio = dx1+dx2;
        for(UFINT16 i=0; i<90; ++i)
        {
            cosAux 		= cos(i*RAD)*raio;
            cosAuxRAlt 	= cos(i*RAD)*(raio-0.2);
            senAux 		= sin(i*RAD)*raio;
            senAuxRAlt 	= sin(i*RAD)*(raio-0.2);
            //circulo inicial
            ponto(m,centro.t,centro.x+(cosAux),centro.y+(senAux),centro.z);
            ponto(m,centro.t,centro.x-(cosAux),centro.y-(senAux),centro.z);
            ponto(m,centro.t,centro.x+(cosAux),centro.y-(senAux),centro.z);
            ponto(m,centro.t,centro.x-(cosAux),centro.y+(senAux),centro.z);
            //arredondamento
            ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y+(senAuxRAlt),centro.z);
            ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y-(senAuxRAlt),centro.z);
            ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y-(senAuxRAlt),centro.z);
            ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y+(senAuxRAlt),centro.z);
        }
    }
    else
    {
        if((dy1==0)&&(dy2==0))
        {
            raio = dz1+dz2;
            for(UFINT16 i=0; i<90; ++i)
            {
                cosAux 		= cos(i*RAD)*raio;
                cosAuxRAlt 	= cos(i*RAD)*(raio-0.2);
                senAux 		= sin(i*RAD)*raio;
                senAuxRAlt 	= sin(i*RAD)*(raio-0.2);
                //circulo inicial
                ponto(m,centro.t,centro.x+(cosAux),centro.y,centro.z+(senAux));
                ponto(m,centro.t,centro.x-(cosAux),centro.y,centro.z-(senAux));
                ponto(m,centro.t,centro.x+(cosAux),centro.y,centro.z-(senAux));
                ponto(m,centro.t,centro.x-(cosAux),centro.y,centro.z+(senAux));
                //arredondamento
                ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y,centro.z+(senAuxRAlt));
                ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y,centro.z-(senAuxRAlt));
                ponto(m,centro.t,centro.x+(cosAuxRAlt),centro.y,centro.z-(senAuxRAlt));
                ponto(m,centro.t,centro.x-(cosAuxRAlt),centro.y,centro.z+(senAuxRAlt));
            }
        }
        else
        {
            if((dx1==0)&&(dx2==0))
            {
                raio = dy1+dy2;
                for(UFINT16 i=0; i<90; ++i)
                {
                    cosAux 		= cos(i*RAD)*raio;
                    cosAuxRAlt 	= cos(i*RAD)*(raio-0.2);
                    senAux 		= sin(i*RAD)*raio;
                    senAuxRAlt 	= sin(i*RAD)*(raio-0.2);
                    //circulo inicial
                    ponto(m,centro.t,centro.x,centro.y+(cosAux),centro.z+(senAux));
                    ponto(m,centro.t,centro.x,centro.y-(cosAux),centro.z-(senAux));
                    ponto(m,centro.t,centro.x,centro.y+(cosAux),centro.z-(senAux));
                    ponto(m,centro.t,centro.x,centro.y-(cosAux),centro.z+(senAux));
                    //arredondamento
                    ponto(m,centro.t,centro.x,centro.y+(cosAuxRAlt),centro.z+(senAuxRAlt));
                    ponto(m,centro.t,centro.x,centro.y-(cosAuxRAlt),centro.z-(senAuxRAlt));
                    ponto(m,centro.t,centro.x,centro.y+(cosAuxRAlt),centro.z-(senAuxRAlt));
                    ponto(m,centro.t,centro.x,centro.y-(cosAuxRAlt),centro.z+(senAuxRAlt));
                }
            }
        }
    }
}

void Draw::esfera(Matriz m,Point<UFINT16> c, UFINT16 raio)
{
    float cosAux, senAux;

    for(int i=0; i<360; ++i)
    {
        cosAux 		= cos(i*RAD)*raio;
        senAux 		= sin(i*RAD)*raio;
        circulo(m,*new Point<UFINT16>(c.x,c.y+senAux,c.z,c.t),cosAux);
    }

}

//void Draw::poligono_3d(Matriz m,Point<UFINT16> centro,UFINT16 arestas, UFINT16 altura, UFINT16 raio)

void Draw::fill_4(Matriz m, UFINT8 fill_paint, UFINT8 filled,UFINT16 x, UFINT16 y,UFINT16 z)
{
    if((x<1)||(y<1)||(z<1)||(x>TAMX-2)||(y>TAMY-2)||(z>TAMZ-2))
        return;
    UFINT16 pt=m[x][y][z];
    if((pt==filled))
    {
        m[x][y][z]=fill_paint;
        fill_4(m,fill_paint,filled,x-1  ,y      ,z);
        fill_4(m,fill_paint,filled,x+1  ,y      ,z);
        fill_4(m,fill_paint,filled,x    ,y+1    ,z);
        fill_4(m,fill_paint,filled,x    ,y-1    ,z);
    }
    else
        return;
}

void Draw::fill_8(Matriz m,UFINT8 fill_paint, UFINT8 filled,UFINT16 x,UFINT16 y,UFINT16 z)
{
    if((x<1)||(y<1)||(z<1)||(x>TAMX-2)||(y>TAMY-2)||(z>TAMZ-2))
        return;
    UFINT16 pt=m[x][y][z];
    if(pt==filled)
    {
        m[x][y][z]=fill_paint;
        fill_8(m,fill_paint,filled,x-1  ,y      ,z);
        fill_8(m,fill_paint,filled,x+1  ,y      ,z);
        fill_8(m,fill_paint,filled,x    ,y-1    ,z);
        fill_8(m,fill_paint,filled,x    ,y+1    ,z);
        fill_8(m,fill_paint,filled,x-1  ,y-1    ,z);
        fill_8(m,fill_paint,filled,x+1  ,y+1    ,z);
        fill_8(m,fill_paint,filled,x+1  ,y-1    ,z);
        fill_8(m,fill_paint,filled,x-1  ,y+1    ,z);
    }
    else
        return;
}

void Draw::fill_6(Matriz m,UFINT8 fill_paint, UFINT8 filled,UFINT16 x, UFINT16 y,UFINT16 z)
{
    if((x<1)||(y<1)||(z<1)||(x>TAMX-2)||(y>TAMY-2)||(z>TAMZ-2))
        return;
    UFINT16 pt=m[x][y][z];
    if(pt==filled)
    {
        m[x][y][z]=fill_paint;
        fill_6(m,fill_paint,filled,x    ,y      ,z-1);
        fill_6(m,fill_paint,filled,x    ,y      ,z+1);
        fill_6(m,fill_paint,filled,x-1  ,y      ,z);
        fill_6(m,fill_paint,filled,x+1  ,y      ,z);
        fill_6(m,fill_paint,filled,x    ,y-1    ,z);
        fill_6(m,fill_paint,filled,x    ,y+1    ,z);
    }
    else
        return;
}

void Draw::fill_26(Matriz m,UFINT8 fill_paint, UFINT8 filled,UFINT16 x, UFINT16 y,UFINT16 z)
{
    if((x<1)||(y<1)||(z<1)||(x>TAMX-2)||(y>TAMY-2)||(z>TAMZ-2))
        return;
    UFINT16 pt=m[x][y][z];
    if((pt==filled))
    {
        m[x][y][z]=fill_paint;
        fill_26(m,fill_paint,filled,x-1  ,y      ,z);
        fill_26(m,fill_paint,filled,x+1  ,y      ,z);
        fill_26(m,fill_paint,filled,x    ,y-1    ,z);
        fill_26(m,fill_paint,filled,x    ,y+1    ,z);
        fill_26(m,fill_paint,filled,x+1  ,y+1    ,z);
        fill_26(m,fill_paint,filled,x-1  ,y+1    ,z);
        fill_26(m,fill_paint,filled,x+1  ,y-1    ,z);
        fill_26(m,fill_paint,filled,x-1  ,y-1    ,z);

        fill_26(m,fill_paint,filled,x    ,y      ,z-1);
        fill_26(m,fill_paint,filled,x-1  ,y      ,z-1);
        fill_26(m,fill_paint,filled,x+1  ,y      ,z-1);
        fill_26(m,fill_paint,filled,x    ,y-1    ,z-1);
        fill_26(m,fill_paint,filled,x    ,y+1    ,z-1);
        fill_26(m,fill_paint,filled,x+1  ,y+1    ,z-1);
        fill_26(m,fill_paint,filled,x-1  ,y+1    ,z-1);
        fill_26(m,fill_paint,filled,x+1  ,y-1    ,z-1);
        fill_26(m,fill_paint,filled,x-1  ,y-1    ,z-1);

        fill_26(m,fill_paint,filled,x    ,y      ,z+1);
        fill_26(m,fill_paint,filled,x-1  ,y      ,z+1);
        fill_26(m,fill_paint,filled,x+1  ,y      ,z+1);
        fill_26(m,fill_paint,filled,x    ,y-1    ,z+1);
        fill_26(m,fill_paint,filled,x    ,y+1    ,z+1);
        fill_26(m,fill_paint,filled,x+1  ,y+1    ,z+1);
        fill_26(m,fill_paint,filled,x-1  ,y+1    ,z+1);
        fill_26(m,fill_paint,filled,x+1  ,y-1    ,z+1);
        fill_26(m,fill_paint,filled,x-1  ,y-1    ,z+1);
    }
    else
        return;
}
