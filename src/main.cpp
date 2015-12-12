#include "draw/draw.h"
#include "render/renderer.h"
#include "render/optimize.h"
#include "render/input.h"
#include "generate/cavernas.h"
#include "generate/labirinto.h"
#include "generate/diamondSquare.h"
#include "generate/perlinNoise.h"
#include "parser.h"
#include "parsing/mapParser.h"
#include "matrixToQ3Map.h"
#include "generate/sala.h"

/***TODO::
Em ordem de prioridade
Renderer:
    1-Arrays separados de posicao, cor,textura, normal, index na criacao de cubos(com triangulos) para otimizacao
    2-camera melhorada/visao do player
    3-Sombras
    4-otimizacao geral na renderizacao caso necessario(raycasting, wavesurfing, octree de voxels)
    5-Skybox
    6-Fog

Draw:
    1-plano
    2-poligono cilindrico
    3-elipses?
    5-implementar angulacao x, y, z em quase tudo
    6-otimizacao geral/melhoria do codigo

Comecar arquitetura da geracao de mapas:
	Salas
		Labirintos
			Quantos tipos diferentes eu conseguir implementar
		Todas as formas geometricas normais
		Formas geometricas anormais
		Prefab
			Fixo
			Variavel
		Recursao de salas
		Regras de criacao de estruturas grandes/complexas
		Posicionamento de objetos de cena
	Corredores
		Pathfinding de verdade(escavacao)
			Pathfinding bebado(escavacao)
		Corredores grossos
	Simetria
		Em locais especificos da matriz
		Resolver o problema de sanidade do mapa
	Mapas naturais
		Cavernas
			Achar mutacoes interessantes no codigo
			Multiplas cavernas ao mesmo tempo
		Overworld em geral
			Corpos de agua?!
			FUTURO DISTANTE
				Clima de regioes
				Biomas

		Posicionamento de objetos de cena

	Integracao final de tudo em um unico mapa

	Bonus:
		Texturas procedurais?
		Scaling?
***/
static Input 		* input;
static Renderer 	* printer;

Json::Value iniSettings(string nome)
{
	std::cout<<"Pegando settings...";
	Parser parse(SETTINGS_FILE, PARSE_JSON_FILE);
	Json::Value aux = parse.getValue(parse.getJson(), "settings");
		aux = aux.get(nome,0);
	std::cout<<"OK"<<std::endl;
	return aux;
}

#ifdef TESTANDOMATRIZ
Matriz cleanMatriz(Matriz a)
{
	Matriz mat = a;
	for(unsigned int i=0;i<mat.size();++i)
		for(unsigned int j=0;j<mat[0].size();++j)
			for(unsigned int j=0;j<mat[0][0].size();++j)
				mat[0][0][0]=0;

	return mat;
}
#endif

int main()
{
    input = Input::GetInstance();
    printer = Renderer::GetInstance();

	#ifdef TESTANDOMATRIZ
		Matriz mat;
    #else
		static Matriz mat;
    #endif

    int seed = 3589201295;
    #ifdef MANUAL_SEED
		Draw::newSeed(seed);
	#else
		Draw::newSeed(time(NULL));
    #endif

    DiamondSquare t;
    Caverna c;
    Labirinto l;
    PerlinNoise p;
    Optimize o;
    Point<int>aux;
    Parser jsonParseFile;


    vector<vector<Point<UFINT8> > > a;

    Json::Value contents;
	deque<double> OPA;
	deque<double> limites;

    //inicializando todos os espacos da matriz como air
    #ifdef TESTANDOMATRIZ
		mat.resize(TAMX);
		for(int i=0;i<TAMX;++i)
		{
			mat[i].resize(TAMY);
			for(int j=0;j<TAMY;++j)
			{
				mat[i][j].resize(TAMZ);
			}
		}
		mat = cleanMatriz(mat);
    #else
		memset(mat,air, sizeof(mat));
    #endif


    //inicializando o rand() com uma nova seed

    std::cout<<"Iniciando OpenGL:"<<std::endl;

    if(printer->ini())
    {
        printer->optimizeMatrix2(mat);

        //MAIN LOOP
        std::cout<<"Aperte (1) cavernas, (2) labirintos, (3) perlin noise2d , (4) perlin noise3d, (5) Novo seed."<<std::endl;
        while ((!input->getSair())||(printer->isWindowClosed()))
        {
        	if(input->getSair()==true)
				break;
            if(input->getMudou())
            {
				#ifdef TESTANDOMATRIZ
					cleanMatriz(mat);
				#else
					memset(mat,air, sizeof(mat));
				#endif
                printer->clearMatrix();
                //checamos qual opcao foi escolhida
                int aux;
                Sala s;
                MapParser * mapParseFile;
                std::stringstream arq;
				std::string ini = "./mapfiles/map",fim = ".txt";
                switch(input->getOp())
                {
					case 0:
						for(int i=0; i<31;++i)
						{
							arq.str("");
							arq<<ini<<i<<fim;
							mapParseFile = new MapParser(arq.str());
							mapParseFile->_2dDequeToMatrix(mat,*new Point<int>(10,10,i+1), *new Point<int>(0,0,0));
						}
						std::cout<<"Geracao completa."<<std::endl;
						printer->optimizeMatrix(mat);
					break;

					case 1://caverna

						std::cout<<"Gerando Caverna..."<<std::endl;
						c.iniCaverna(mat,*new Point<UFINT8>(cav_w,cav_f,air),*new Point<int>(2,2,2),*new Point<int>(TAMX-2,TAMY-2,TAMZ-2),26,10000);
						std::cout<<"Geracao completa."<<std::endl;
						printer->optimizeMatrix2(mat);
						//printer->optimizeRect(o.matrizLeastRectanglesEW(mat));
						//ajustando heightmap
						//printer->setHighLow(Draw::getHighLow(mat,'Z'));
						//map.ini(mat, "testeQ3.map", 64);

					break;

					case 2://labirintos
						std::cout<<"Gerando Labirinto..."<<std::endl;
						aux=64;
						l = *new Labirinto(mat,*new Point<UFINT16>(TAMX/2,TAMY/2,TAMZ/2,1),*new Point<UFINT16>(aux,aux,aux,air),1);
						std::cout<<"Geracao completa."<<std::endl;

						//ajustando heightmap
						//printer->setHighLow(Draw::getHighLow(mat,'Z'));

						printer->optimizeMatrix(mat);
						printer->optimizeRect(o.matrizLeastRectanglesEW(mat));

						break;

					case 3://perlin noise
						std::cout<<"Gerando Perlin noise..."<<std::endl;
						p.ini2d(mat, input->getO(), input->getA(),input->getP());
						std::cout<<"Geracao completa. OCT:"<<input->getO()<<" AMP:"<<input->getA()<<" PERS:"<<input->getP()<<std::endl;
						//Draw::simpSqrFill(mat,*new Point<UFINT16>(2,2,62,water9),*new Point<UFINT16>(TAMX-2,TAMY-2,62));
						//Draw::simpSqrFill(mat,*new Point<UFINT16>(64,63,11,72),*new Point<UFINT16>(64,63,11));
						Draw::simpSqrFill(mat,*new Point<UFINT16>(60,60,62,water9),*new Point<UFINT16>(64,64,62));
						//Draw::simpSqrFill(mat,*new Point<UFINT16>(64,64,20,water1),*new Point<UFINT16>(64,64,20));
						//Draw::simpSqrFill(mat,*new Point<UFINT16>(62,62,62,water9),*new Point<UFINT16>(64,64,62));

						//Draw::waterSim(mat);

						printer->optimizeMatrix3(mat);
						printer->optimizeRect(o.matrizLeastRectanglesEW(mat));
					break;

					case 4://perlin noise
						contents = iniSettings("mapa3d");
						OPA = jsonParseFile.getDequeDouble(contents, "OPA");
						limites = jsonParseFile.getDequeDouble(contents, "limites");

						seed = time(NULL);
						Draw::newSeed(seed);
						p.shuffle_permutationTable();
						std::cout<<"SEED:"<<seed<<std::endl;
						std::cout<<"Gerando Perlin noise...";
						p.ini3d(mat,OPA[0],	OPA[1],	OPA[2],	-10,	10);
						std::cout<<"OK.\nOCT:"<<OPA[0]<<" AMP:"<<OPA[1]<<" PERS:"<<OPA[2]<<std::endl;

						//Draw::simpleWaterSim(mat, 10);
						//Draw::simpSqrFill(mat,*new Point<UFINT16>(32,32,62,water9),*new Point<UFINT16>(64,64,62));
						//Draw::waterSim(mat);

						printer->optimizeMatrix2(mat);
						printer->optimizeRect(o.matrizLeastRectanglesEW(mat));
						//map.ini(mat, "testeQ3.map", 32);
					break;

					case 5://novo seed
						std::cout<<"Gerando novo seed...";
						seed = time(NULL);
						Draw::newSeed(seed);
						p.shuffle_permutationTable();
						std::cout<<"OK. SEED:"<<seed<<std::endl;
					break;

					default:
					break;
                }
                //CLEAN UP
                std::cout<<"Re-rendering...\n\n";
                printer->displayListInit = false;
                input->setMudou(false);
                input->setOp(0);
            }
            //Renderizacao
            printer->render();
            //getchar();
        }
    }

    #ifdef TESTANDOMATRIZ
		cleanMatriz(mat);
    #else
		memset(mat,air, sizeof(mat));
    #endif
    return 0;
}
