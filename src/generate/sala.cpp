#include "sala.h"
#include "../draw/draw.h"

Sala::Sala(Matriz m, Point<UFINT16> ini, Point<UFINT16>dim)
{
	this->dimensoes = dim;
	Draw::simpCuboideShell(m, ini, dim);
}

Sala::Sala()
{
}

Sala::~Sala()
{
}

void Sala::drawDoor()
{

}

void Sala::drawWindow()
{

}

void Sala::addDoor(Point<UFINT16> pos, int posCardinal)
{
	ObjetoNaParede obj;
	obj.pos = pos;
	obj.posCardinal = posCardinal;
	this->portas.push_back(obj);
	return;
}

void Sala::addWindow(Point<UFINT16> pos, int posCardinal)
{
	ObjetoNaParede obj;
	obj.pos = pos;
	obj.posCardinal = posCardinal;
	this->janelas.push_back(obj);
	return;
}

void Sala::preparaWallAreas(Point<UFINT16>ini, Point<UFINT16>dim)
{
	Conjunto c;
	Point <UFINT16> fim = dim;
	fim.add(ini);

	//FIXME:: caso nao queira teto ou chao com portas/janelas fazer o que?
	this->wallAreas.resize(6);
	//baixo
	c.ini = ini;
	c.fim = *new Point < UFINT16 > (fim.x,	fim.y,	ini.z);
	this->wallAreas[0] = c;

	//cima
	c.ini = *new Point < UFINT16 > (ini.x,	ini.y,	fim.z);
	c.fim = fim;
	this->wallAreas[1] = c;

	//leste
	c.ini = ini;
	c.fim = *new Point < UFINT16 > (ini.x,	fim.y,	fim.z);
	this->wallAreas[2] = c;

	//oeste
	c.ini = *new Point < UFINT16 > (fim.x,	ini.y,	ini.z);
	c.fim = fim;
	this->wallAreas[3] = c;

	//norte
	c.ini = *new Point < UFINT16 > (ini.x,	fim.y,	ini.z);
	c.fim = fim;
	this->wallAreas[4] = c;

	//sul
	c.ini = ini;
	c.fim = *new Point < UFINT16 > (fim.x,	ini.y,	fim.z);
	this->wallAreas[5] = c;
	return;
}

void Sala::iniSala(Matriz m, Point<UFINT16> ini, Point<UFINT16>dim, int numPortas=0, int numJanelas=0)
{
	if((dim.x<3)||(dim.y<3)||(dim.z<3))
	{
		cout<<"Sala nao tem o tamanho minimo."<<endl;
		return;
	}
	else
	{
		this->dimensoes = dim;
		this->numPortas = numPortas;
		this->numJanelas = numJanelas;

		Draw::simpCuboideShell(m, ini, dim);
		preparaWallAreas(ini, dim);

		int cardinal = 0;
		for(int i=0; i<numPortas; ++i)
		{
			cardinal = Draw::rngi(0,5);
			Point <UFINT16> aux;
			aux.set(Draw::rngi(wallAreas[cardinal].ini.x,wallAreas[cardinal].fim.x),
					Draw::rngi(wallAreas[cardinal].ini.y,wallAreas[cardinal].fim.y),
					Draw::rngi(wallAreas[cardinal].ini.z,wallAreas[cardinal].fim.z));
			addDoor(aux, cardinal);
		}

		for(int i=0; i<numJanelas; ++i)
		{
			cardinal = Draw::rngi(0,5);
			Point <UFINT16> aux;
			aux.set(Draw::rngi(wallAreas[cardinal].ini.x,wallAreas[cardinal].fim.x),
					Draw::rngi(wallAreas[cardinal].ini.y,wallAreas[cardinal].fim.y),
					Draw::rngi(wallAreas[cardinal].ini.z,wallAreas[cardinal].fim.z));
			addWindow(aux, cardinal);
		}

	}
	return;
}
