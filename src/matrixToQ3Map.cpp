#include "matrixToQ3Map.h"

MatrixToMap::MatrixToMap(Matriz mat ,string nomeMapa, int tamBloco)
{
	this->brushNum=0;
	this->tamBloco=tamBloco;
	ofstream fileOutput;
	ostringstream texto;

	fileOutput.open(nomeMapa.c_str(),ios::out | ios::trunc);

	texto<<"//entity 0\n{\n";
	texto<<"\"classname\"  \"worldspawn\"\n";
	for(int k=0;k<TAMZ; ++k)
		for(int j=0;j<TAMY; ++j)
			for(int i=0;i<TAMX; ++i)
			{
				if(mat[i][j][k]!=0)
				{
					pointToBlock(*new Point<int>(i,j,k));
				}
			}
	texto<<"}\n";
	fileOutput<<texto.str();
	fileOutput.close();
}

MatrixToMap::MatrixToMap()
{

}

MatrixToMap::~MatrixToMap()
{

}

void MatrixToMap::ini(Matriz mat ,string nomeMapa, int tamBloco)
{
	this->brushNum=0;
	this->tamBloco=tamBloco;
	ofstream fileOutput;
	ostringstream texto;
	texto<<"//entity 0\n{\n";
	texto<<"\"classname\" \"worldspawn\"\n";
	fileOutput.open(nomeMapa.c_str(),ios::out | ios::trunc);
	for(int k=0;k<TAMZ; ++k)
		for(int j=0;j<TAMY; ++j)
			for(int i=0;i<TAMX; ++i)
			{
				if(mat[i][j][k]!=0)
				{
					texto<<pointToBlock(*new Point<int>(i,j,k));
				}
			}
	texto<<"}\n";
	fileOutput<<texto.str();
	fileOutput.close();
}

string MatrixToMap::pointToBlock(Point<int>p)
{
	ostringstream bloco;
	bloco<<"//brush "<<brushNum<<"\n";
	bloco<<pointToString(p);
	brushNum++;
	return bloco.str();
}

inline string p3(int x, int y, int z)
{
	ostringstream aux;
	aux<<"("<<x<<" "<<y<<" "<<z<<") ";
	return aux.str();
}

string MatrixToMap::pointToString(Point<int>p)
{
	ostringstream coordenadas;
	Point<int>q = p;
	int t=tamBloco;
	q.mul(t);
	coordenadas<<"{\n";
	//linha 1
	coordenadas<<p3(q.x+t	,q.y+t	,0)<<p3(q.x		,q.y+t	,0)<<p3(q.x		,q.y	,0);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	//linha 2
	coordenadas<<p3(q.x		,q.y	,t)<<p3(q.x		,q.y+t	,t)<<p3(q.x+t	,q.y+t	,t);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	//linha 3
	coordenadas<<p3(q.x		,q.y	,t)<<p3(q.x+t	,q.y	,t)<<p3(q.x+t	,q.y	,0);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	//linha 4
	coordenadas<<p3(q.x+t	,q.y	,t)<<p3(q.x+t	,q.y+t	,t)<<p3(q.x+t	,q.y+t	,0);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	//linha 5
	coordenadas<<p3(q.x+t	,q.y+t	,t)<<p3(q.x		,q.y+t	,t)<<p3(q.x		,q.y+t	,0);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	//linha 6
	coordenadas<<p3(q.x		,q.y+t	,t)<<p3(q.x		,q.y	,t)<<p3(q.x		,q.y	,0);
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";

	coordenadas<<"}\n";
	return coordenadas.str();
}
/*coordenadas<<"("<<q.x	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y		<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y		<<" "<<q.z		<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";
	//linha 2
	coordenadas<<"("<<q.x+t	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y+t	<<" "<<q.z		<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";
	//linha 3
	coordenadas<<"("<<q.x+t	<<" "<<q.y		<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x+t	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x+t	<<" "<<q.y+t	<<" "<<q.z		<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";
	//linha 4
	coordenadas<<"("<<q.x	<<" "<<q.y		<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x+t	<<" "<<q.y		<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x+t	<<" "<<q.y		<<" "<<q.z		<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";
	//linha 5
	coordenadas<<"("<<q.x	<<" "<<q.y		<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"("<<q.x+t	<<" "<<q.y+t	<<" "<<q.z+t	<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";
	//linha 6
	coordenadas<<"("<<q.x+t	<<" "<<q.y+t	<<" "<<q.z		<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y+t	<<" "<<q.z		<<") ";
	coordenadas<<"("<<q.x	<<" "<<q.y		<<" "<<q.z		<<") ";
	coordenadas<<"common/caulk 0 0 0 0.500000 1.000000 0 4 0\n";*/
