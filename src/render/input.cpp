#include "input.h"

bool Input::instanceFlag = false;
Input* Input::inputVariable = NULL;

Input * Input::GetInstance ()
{
    if (!instanceFlag)
    {
        inputVariable = new Input();
        instanceFlag =true;
        return inputVariable;
    }
    else
    {
		return(inputVariable);
    }
}


Input::~Input()
{
    instanceFlag=false;
}

void Input::ini(Point<UFINT16>pos,Point<UFINT16>ang, GLFWwindow * w)
{
    positionx=pos.x;
    positiony=pos.y;
    positionz=pos.z;
    xSpeed=ySpeed=zSpeed=pos.t;

    anglex=ang.x;
    angley=ang.y;
    anglez=ang.z;
    xAngSpeed=yAngSpeed=zAngSpeed=ang.t;

    op=amp=pers=oct=0;
    sair=mudou=false;

    window = w;
}

bool Input::getSair()
{
    return sair;
}

void Input::setSair(bool s)
{
    sair=s;
}

bool Input::getMudou()
{
    return mudou;
}

void Input::setMudou(bool m)
{
    mudou=m;
}

int Input::getOp()
{
    return op;
}

void Input::setOp(int o)
{
    op=o;
}

double Input::getP()
{
    return pers;
}
int Input::getO()
{
    return oct;
}
double Input::getA()
{
    return amp;
}

Point<GLfloat> Input::getPosition()
{
    Point <GLfloat> aux;
    aux.set(positionx,positiony,positionz);
    return aux;
}

void Input::setPosition(Point<GLfloat> p)
{
    positionx = p.x;
    positiony = p.y;
    positionz = p.z;
}
void Input::setPosition(GLfloat x,GLfloat y,GLfloat z)
{
    positionx = x;
    positiony = y;
    positionz = z;
}

Point<GLfloat> Input::getAngularPosition()
{
    Point <GLfloat> aux;
    aux.set(anglex,angley,anglez);
    return aux;
}

void Input::setAngularPosition(Point<GLfloat> p)
{
    anglex = p.x;
    angley = p.y;
    anglez = p.z;
}

void Input::setAngularPosition(GLfloat x,GLfloat y,GLfloat z)
{
    anglex = x;
    angley = y;
    anglez = z;
}

void Input::setSpeed(Point<GLfloat> p)
{
    xSpeed = p.x;
    ySpeed = p.y;
    zSpeed = p.z;
}

void Input::setAngularSpeed(Point<GLfloat> p)
{
    xAngSpeed = p.x;
    yAngSpeed = p.y;
    zAngSpeed = p.z;

}

void Input::setPosition(int x, int y, int z)
{
	positionx=x;
	positiony=y;
	positionz=z;
}

void Input::setAngle(int x, int y, int z)
{
	anglex=x;
	angley=y;
	anglez=z;
}

void Input::addAngle(int a, char axis)
{
	switch (axis)
	{
		case 'X':
		case 'x':
			anglex+=a;
		break;
		case 'Y':
		case 'y':
			angley+=a;
		break;
		case 'Z':
		case 'z':
			anglez+=a;
		break;
	}
}

void Input::addPosition(int p, char axis)
{
	switch (axis)
	{
		case 'X':
		case 'x':
			positionx+=p;
		break;
		case 'Y':
		case 'y':
			positiony+=p;
		break;
		case 'Z':
		case 'z':
			positionz+=p;
		break;
	}
}

int Input::getAngleSpeed(char axis)
{
	switch (axis)
	{
		case 'X':
		case 'x':
			return xAngSpeed;
		break;
		case 'Y':
		case 'y':
			return yAngSpeed;
		break;
		case 'Z':
		case 'z':
			return zAngSpeed;
		break;
	}
	return 0;
}

int Input::getPositionSpeed(char axis)
{
	switch (axis)
	{
		case 'X':
		case 'x':
			return xSpeed;
		break;
		case 'Y':
		case 'y':
			return ySpeed;
		break;
		case 'Z':
		case 'z':
			return zSpeed;
		break;
	}
	return 0;
}
