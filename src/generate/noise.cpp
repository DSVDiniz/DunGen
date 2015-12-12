#include "noise.h"

/*
static int primos [] ={7927, 8387, 8563, 8713, 8501, 8423, 8807, 8629, 8111, 8089};
static int p1,p2,p3,p4,p5;
Noise::Noise()
{

}

Noise::~Noise()
{

}

double inline Interpolate(double a, double b, double x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * .5;

	return  a*(1-f) + b*f;
}

double PerlinNoise::Noise(int x, int y)
{
    //int n=(int)x+(int)y*57;
	//n=(n<<13)^n;
	//int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
	//return 1.0-((double)nn/1073741824.0);
	int n=(int)x+(int)y*p1;
	n=(n<<p2)^n;
	int nn=(n*(n*n*p3+p4)+p5)&0x7fffffff;
	return 1.0-((double)nn/1073741824.0);
}



double PerlinNoise::SmoothNoise_1(float x, float y)
{
	double corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
	double sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8;
	double center  =  Noise(x, y) / 4;
	return corners + sides + center;
}

double PerlinNoise::InterpolatedNoise_1(float x, float y)
{
	int integer_X    = int(x);
	int fractional_X = x - integer_X;

	int integer_Y    = int(y);
	int fractional_Y = y - integer_Y;

	double v1 = SmoothNoise_1(integer_X,     integer_Y);
	double v2 = SmoothNoise_1(integer_X + 1, integer_Y);
	double v3 = SmoothNoise_1(integer_X,     integer_Y + 1);
	double v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);

	double i1 = Interpolate(v1 , v2 , fractional_X);
	double i2 = Interpolate(v3 , v4 , fractional_X);

	return Interpolate(i1 , i2 , fractional_Y);

  }


double PerlinNoise::PerlinNoise_2D(Matriz mat, int oct, double pers, double amp)
{
	double total = 0;
	double n = oct;
	p1=primos[Draw::rngi(9,0)];
	p2=primos[Draw::rngi(9,0)];
	p3=primos[Draw::rngi(9,0)];
	p4=primos[Draw::rngi(9,0)];
	p5=primos[Draw::rngi(9,0)];
	std::vector < std::vector<double> > pontos;
	pontos.resize(TAMX);
	for(unsigned int i=0;i<TAMX;++i)
		pontos[i].resize(TAMY);

	for(int j = 0;j < TAMY; ++j)
	{
		for(int i = 0;i < TAMX; ++i)
		{
			for(int a=1;a<=n;++a)
			{
				double frequency = pers	/	(2*a);
				double amplitude = amp	*	(2*a);
				total += InterpolatedNoise_1(i * frequency, j * frequency) * amplitude;
			}
			pontos[i][j] = total;
			total=0;
		}
	}
	double aux=0.0;
	for(int j = 0;j < TAMY; ++j)
		for(int i = 0;i < TAMX; ++i)
		{
			aux = 20+pontos[i][j];
			for(int l=0;l<=aux;++l)
			{
				Draw::insertSafe(mat,*new Point<UFINT16>(i,j,l,l));
			}
		}

	return total;
}*/
