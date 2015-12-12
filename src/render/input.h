#ifndef INPUT_H_
#define INPUT_H_
#include "../defines.h"
#include "../point.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Input
{
	private:

		int positionx, positiony,positionz,op;
		int anglex,angley,anglez;
		int xSpeed,ySpeed,zSpeed,xAngSpeed,yAngSpeed,zAngSpeed,oct;
		double amp,pers;
		bool sair, mudou;
		static bool instanceFlag;
		static Input * inputVariable;
		GLFWwindow * window;

	public:

		static Input * GetInstance();

		virtual ~Input();

		void ini(Point<UFINT16>pos,Point<UFINT16>ang, GLFWwindow * w);

		//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		//void resolve();

		Point<GLfloat> getPosition();

		void setPosition(Point<GLfloat> p);

		void setPosition(GLfloat x,GLfloat y,GLfloat z);

		Point<GLfloat> getAngularPosition();

		void setAngularPosition(Point<GLfloat> p);

		void setAngularPosition(GLfloat x,GLfloat y,GLfloat z);

		void setSpeed(Point<GLfloat> p);

		void setAngularSpeed(Point<GLfloat> p);
		bool getSair();
		void setSair(bool s);
		bool getMudou();
		void setMudou(bool m);
		int getOp();
		int getO();
		double getA();
		double getP();
		void setOp(int o);
		void setPosition(int x, int y, int z);
		void setAngle(int x, int y, int z);
		void addPosition(int p, char axis);
		void addAngle(int a, char axis);
		int getAngleSpeed(char axis);
		int getPositionSpeed(char axis);
};
#endif /*INPUT_H_*/
