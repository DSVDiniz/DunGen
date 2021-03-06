#include "parser.h"

Parser::Parser(string fileName, int operation)
{
	string contents = fileToString(fileName);
	if(contents.compare("null")==0)
	{
		cout<<"Erro: Falha na inicializacao do parser."<<endl;
		return;
	}
	else
	{
		switch (operation)
		{
			case PARSE_JSON_FILE:
				json = stringToJSON(contents);
			break;

			case PARSE_MAP_FILE:
			break;
		}
	}
}

Parser::Parser()
{
}

Parser::~Parser()
{

}

string Parser::fileToString(string fileName)
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

Json::Value Parser::stringToJSON(string conteudo)
{
    Json::Value root;
    Json::Reader reader;
    if(reader.parse(conteudo,root))
		return root;
    else
    {
		cout<<"\nErro(stringToJson):"<<reader.getFormatedErrorMessages()<<"\n";
		return 0;
    }
}
Json::Value Parser::getValue(Json::Value root, string nome)
{
	if((root.isObject())&&(!root.empty()))
	{
		if(root.isMember(nome))
			return root.get(nome, 0);
		else
		{
			cout<<"\nErro(getValue): membro nao encontrado no json"<<"\n";
			return 0;
		}
	}
	else
	{
		cout<<"\nErro(getValue): root nao eh um objeto ou json vazio"<<"\n";
		return 0;
	}

}

deque< double >Parser::getDequeDouble(Json::Value root, string nome)
{
	deque<double> resultado;
	Json::Value jarray = root[nome];
	for(unsigned int i=0; i<jarray.size();++i )
	{
		resultado.push_back(jarray[i].asDouble());
	}
	return resultado;
}

bool Parser::getBool(Json::Value root, string nome)
{
	return root[nome].asBool();
}

int Parser::getInt(Json::Value root, string nome)
{
	return root[nome].asInt();
}

double Parser::getDouble(Json::Value root, string nome)
{
	return root[nome].asDouble();
}

Json::Value Parser::getJson()
{
	return json;
}


