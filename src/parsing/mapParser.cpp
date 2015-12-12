#include "mapParser.h"


MapParser::MapParser(string nome)
{
	fileName = nome;
	string content = fileToString(nome);
    pontos = stringTo2dDeque(content);
}

MapParser::~MapParser()
{

}

string MapParser::fileToString(string fileName)
{
    ifstream file;
    file.open(fileName.c_str(),ios::out);
    if((file.is_open())&&(file.good()))//tudo ok?
    {
        string contents;
        file.seekg(0, ios::end);//ponteiro pro fim
        contents.resize(file.tellg());//tamanho da string mudada pra aguentar tudo
        file.seekg(0,ios::beg);//voltando pro inicio
        file.read(&contents[0],contents.size());//bota tudo na string
        file.close();
        return contents;
    }
    else//escreve o nome desse arquivo direito mano
    {
        file.close();
        cout<<"\nErro(fileToString): arquivo nao existe"<<endl;
        return "null";
    }
}

deque<deque<Point<int> > > MapParser::stringTo2dDeque(string content)
{
	deque<deque<Point<int> > > pts;
	deque<int>valores;

	strtk::parse(content,",",valores);

	int width	=	valores[0];
	int heigth	=	valores[1];

	pts.resize(width);

	for(unsigned int i=0; i<pts.size();++i)
		pts[i].resize(heigth);

	int k=3;
	for(int j=0;j<heigth; ++j)
	{
		for(int i=0; i<width; ++i)
		{
			pts[i][j] = * new Point<int>(i,j,0,valores[k]);
			k++;
		}
	}
	return pts;
}

void MapParser::_2dDequeToMatrix(Matriz m, Point <int> position, Point<int> rotation)
{
	int width = pontos.size(), height = pontos[0].size();

	for(int j=0; j<height; ++j)
	{
		for(int i=0; i<width; ++i)
		{
			if(pontos[i][j].t==5)
			{
				Draw::insert(m,pontos[i][j].x+position.x,	pontos[i][j].y+position.y,	pontos[i][j].z+position.z,pontos[i][j].t);
			}
		}
	}
}
