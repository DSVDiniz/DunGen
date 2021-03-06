#ifndef PARSER_H_
#define PARSER_H_

#include "defines.h"
#include "point.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <cstring>
#include <stdlib.h>
#include <jsoncpp/json.h>

using namespace std;

class Parser
{
	private:
		string fileNameSettings;
		fstream fileSettings;
		Json::Value json;
	public:
		Parser(string fileName, int operation);
		Parser();
		~Parser();
		string fileToString(string fileName);
		Json::Value stringToJSON(string conteudo);
		deque< double >getDequeDouble(Json::Value root, string nome);
		Json::Value getValue(Json::Value root, string nome);
		bool getBool(Json::Value root, string nome);
		int getInt(Json::Value root, string nome);
		double getDouble(Json::Value root, string nome);
		Json::Value getJson();




};
#endif /*PARSER_H_*/
