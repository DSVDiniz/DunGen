#ifndef CORREDOR_H_
#define CORREDOR_H_

#include "../draw/draw.h"

using namespace std;

class Corredor
{
	private:
		Point < UFINT16 > ini, fim;

	public:
		Corredor(Matriz m, Point<UFINT16> ini, Point<UFINT16>dim);
		Corredor();
		~Corredor();
		void iniCorredor(Matriz m, Point<UFINT16> ini, Point<UFINT16>fim);
		void achaCaminho();
};
#endif /*CORREDOR_H_*/

