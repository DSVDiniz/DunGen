#ifndef RENDERER_H_
#define RENDERER_H_

#include "../defines.h"
#include "../point.h"
#include "input.h"

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

#include <GLFW/glfw3.h>

using namespace std;
#ifdef TESTANDOMATRIZ
	typedef std::vector <std::vector <std::vector <UFINT8> > > Matriz;
#else
	typedef UFINT16 Matriz [TAMX][TAMY][TAMZ];
#endif


class Renderer
{
	private:
		static UFINT16 optMatriz[TAMX*TAMY*TAMZ];
		static int high,low;
		static GLuint mapList;
		static bool instanceFlag;
		static Renderer * printerVariable;
		vector < vector <Point<UFINT8> > >vec_ret;
		GLFWwindow * window;

	public:
		Input *inputs;
		static bool displayListInit;

		static Renderer * GetInstance();

		virtual ~Renderer();

		bool ini();

		bool iniWindow();

		void iniArrays();

		void iniLight();

		bool isWindowClosed();

		//void GLFWCALL windowResize(int width, int height);
		void windowResize(int width, int height);

		//static void GLFWCALL resolveHook(int action, int key);
		static void resolveHook(int action, int key);

		void moveView(Point <GLfloat> pos, Point <GLfloat> ang);

		void render();

		bool shellCheck(Matriz mat,int x, int y, int z);
		bool shellCheck2(Matriz mat,int x, int y, int z);

		void optimizeRect(vector<vector<Point<UFINT8> > > a);

		void optimizeMatrix(Matriz mat);

		void optimizeMatrix2(Matriz mat);

		void optimizeMatrix3(Matriz mat);

		void clearMatrix();

		void setHighLow(Point<int> p);

		void cubo(int x,int y,int z,int tipo,double s=CUBE_SIZE, double t=CUBE_SIZE, double u=CUBE_SIZE );
		void cuboLines(int x, int y, int z,int r,int g,int b,double s=CUBE_SIZE,double t=CUBE_SIZE,double u=CUBE_SIZE);

		void drawObject();

		void mesh(double x, double y, double z, double a);

		void marchingCubes();

		bool checkSair();
		int checkOp();
		void changeOp(int i);
		GLuint loadTextura(const char * nomeTextura);
};
#endif /*RENDERER_H_*/
