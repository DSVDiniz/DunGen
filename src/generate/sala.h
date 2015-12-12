#ifndef SALA_H_
#define SALA_H_

#include "../draw/draw.h"

using namespace std;

typedef struct
{
	Point<UFINT16> ini;
	Point<UFINT16> fim;
} Conjunto;

typedef struct
{
	Point<UFINT16> pos;
	int posCardinal;
} ObjetoNaParede;

class Sala
{
	private:
		Point < UFINT16 > dimensoes;
		deque < Conjunto > wallAreas;//areas onde eh possivel colocar portas/janelas
		deque < ObjetoNaParede > portas;
		deque < ObjetoNaParede > janelas;

		int numPortas;
		int numJanelas;

	public:
		Sala(Matriz m, Point<UFINT16> ini, Point<UFINT16>dim);
		Sala();
		~Sala();
		void iniSala(Matriz m, Point<UFINT16> ini, Point<UFINT16>dim, int numPortas, int numJanelas);
		void preparaWallAreas(Point<UFINT16>ini, Point<UFINT16>fim);
		void addDoor(Point<UFINT16> pos, int posCardinal);
		void addWindow(Point<UFINT16> pos, int posCardinal);
		void drawDoor();
		void drawWindow();
};
#endif /*SALA_H_*/
