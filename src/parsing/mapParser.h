#ifndef MAPPARSER_H_
#define MAPPARSER_H_

#include "../draw/draw.h"
#include "../defines.h"
#include "../point.h"

#include "strtk.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <cstring>
#include <stdlib.h>


using namespace std;

class MapParser
{
	private:
		string fileName;
		fstream fileSettings;
		deque<deque <Point<int> > > pontos;
	public:
		MapParser(string fileName);
		~MapParser();

		string fileToString(string fileName);
		deque<deque<Point<int> > > stringTo2dDeque(string content);
		void _2dDequeToMatrix(Matriz m, Point <int> position, Point<int> rotation);
};
#endif /*MAPPARSER_H_*/

