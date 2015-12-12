#include "labirinto.h"

//gerador de numeros aleatorios inteiros
int Labirinto::rngi(int max, int min)
{
    return min+rand() % (max-min);
    //return min + rand() / ( RAND_MAX / ( max - min ) + 1 );
}

//essa funcao pega o tipo de ponto em um local, se ele for igual ao tipo "alvo", ele o substitui pelo tipo "troca"
Point<UFINT16>* comp(Matriz m,UFINT16 x, UFINT16 y,UFINT16 z,unsigned int alvo, unsigned int troca)
{
    if(m[x][y][z]==alvo)
        m[x][y][z]=troca;
    return new Point<UFINT16>(x,y,z);
}

//construtor
Labirinto::Labirinto()
{
}

//inicializador, recebe a matriz, a posicao centro do labirinto, e suas dimensoes(raio)
Labirinto::Labirinto(Matriz m,Point<UFINT16> pos,Point<UFINT16> dim, int stepsize)
{
    bool salaCriada=false;
    int numEm =0;
    step=stepsize;

    if((pos.x-dim.x<0)||(pos.y-dim.y<0)||(pos.z-dim.z<0))//vendo se nao eh um valor invalido
        return;

    //setando os limites superiores e inferiores
    limInf.set(pos.x-dim.x,pos.y-dim.y,pos.z-dim.z);
    limSup.set(pos.x+dim.x,pos.y+dim.y,pos.z+dim.z);

    srand(time(NULL));
    while ((!salaCriada)&&(numEm<MAX_TENTATIVAS))//loop de tentativas
    {
        wh = dim;
        xy = pos;
        salaCriada=Draw::checkArea(m,limInf, limSup,1);//checando se tem espaco na matriz
        numEm++;
    }
    if(salaCriada)
        depthFirst(m,xy);//inicio da funcao recusiva de profundidade
}

//deconstrutor
Labirinto::~Labirinto()
{

}

//codigo principal: funcao recusiva de profundidade
void Labirinto::depthFirst(Matriz m,Point<UFINT16> pt)
{
    //colocamos um ponto
    m[pt.x][pt.y][pt.z]=cav_f;

    //checamos se há vizinhos (para onde podemos andar) em torno do ponto, e colocamos suas posicoes em uma lista
    //std::vector<Point<UFINT16> > vizinhos = checkVizinhos(m,pt);
    std::vector<Point<UFINT16> > vizinhos = checkVizinhosEsf(m,pt);

    if(vizinhos.size()<=0)//se a lista de vizinhos for nula, nao ha vizinhos -> fim do caminho, voltar
        return;
    else//caso haja vizinhos...
    {
        std::random_shuffle(vizinhos.begin(),vizinhos.end());//aleatorizamos a lista de vizinhos

        //aqui ligamos o ponto que estamos com o ponto que queremos ir (escolhendo o ponto de ida aleatoriamente)
        Point<UFINT16> aux = ligaVizinho(m,pt, vizinhos[rngi(vizinhos.size())]);

        //abrimos um novo ramo de recursao em cada um dos vizinhos
        for(unsigned int i=0; i<vizinhos.size(); ++i)
            depthFirst(m,aux);
    }
    vizinhos.clear();
}

//funcao que checa os vizinhos (em uma area retangular) e retorna um vetor de pontos (x,y,z) com os vizinhos disponiveis
std::vector<Point<UFINT16> > Labirinto::checkVizinhos(Matriz m ,Point<UFINT16> i)
{
    std::vector<Point<UFINT16> >vizinhos;
    int k=0;
    Point <UFINT16> * aux = new Point<UFINT16>();

    //cada if checa se o ponto de destino (vizinho) esta nos limites do labirinto e se esta vazio
    if((i.x+step+1 <= limSup.x)&&(m[i.x+step+1][i.y][i.z]==air))
    {
        aux->set(i.x+step+1,i.y,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.x-step-1 > limInf.x)&&(m[i.x-step-1][i.y][i.z]==air))
    {
        aux->set(i.x-step-1,i.y,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.y+step+1 <= limSup.y)&&(m[i.x][i.y+step+1][i.z]==air))
    {
        aux->set(i.x,i.y+step+1,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.y-step-1 > limInf.y)&&(m[i.x][i.y-step-1][i.z]==air))
    {
        aux->set(i.x,i.y-step-1,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.z+step+1 <= limSup.z)&&(m[i.x][i.y][i.z+step+1]==air))
    {
        aux->set(i.x,i.y,i.z+step+1,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.z-step-1 > limInf.z)&&(m[i.x][i.y][i.z-step-1]==air))
    {
        aux->set(i.x,i.y,i.z-step-1,air);
        vizinhos.push_back(*aux);
        k++;
    }
    delete(aux);
    vizinhos.resize(k);
    return vizinhos;
}

//funcao auxiliar para calcular a distancia de um ponto a outro
inline bool dentroRaio(int x,int y,int z,double r)
{
    if((x*x)+(y*y)+(z*z)>(r*r))
        return false;
    else
        return true;
}

//funcao que checa os vizinhos (em uma area esferica) e retorna um vetor de pontos (x,y,z) com os vizinhos disponiveis
std::vector<Point<UFINT16> > Labirinto::checkVizinhosEsf(Matriz m ,Point<UFINT16> i)
{
    std::vector<Point<UFINT16> >vizinhos;
    int k=0;
    double raio=wh.x;
    Point <UFINT16> * aux = new Point<UFINT16>();

    //cada if checa se o ponto de destino (vizinho) esta nos limites do labirinto, se esta dentro do raio esferico e se esta vazio
    if((i.x+step+1 <= limSup.x)	&&(dentroRaio(xy.x-i.x+step+1,xy.y-i.y,xy.z-i.z,raio))	&&(m[i.x+step+1][i.y][i.z]==air))
    {
        aux->set(i.x+step+1,i.y,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.x-step-1 > limInf.x)	&&(dentroRaio(xy.x-i.x-step-1,xy.y-i.y,xy.z-i.z,raio))	&&(m[i.x-step-1][i.y][i.z]==air))
    {
        aux->set(i.x-step-1,i.y,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.y+step+1 <= limSup.y)	&&(dentroRaio(xy.x-i.x,xy.y-i.y+step+1,xy.z-i.z,raio))	&&(m[i.x][i.y+step+1][i.z]==air))
    {
        aux->set(i.x,i.y+step+1,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.y-step-1 > limInf.y)	&&(dentroRaio(xy.x-i.x, xy.y-i.y-step-1, xy.z-i.z, raio))	&&(m[i.x][i.y-step-1][i.z]==air))
    {
        aux->set(i.x,i.y-step-1,i.z,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.z+step+1 <= limSup.z)	&&(dentroRaio(xy.x-i.x, xy.y-i.y, xy.z-i.z+step+1, raio))	&&(m[i.x][i.y][i.z+step+1]==air))
    {
        aux->set(i.x,i.y,i.z+step+1,air);
        vizinhos.push_back(*aux);
        k++;
    }

    if((i.z-step-1 > limInf.z)	&&(dentroRaio(xy.x-i.x,	xy.x-i.y ,xy.z-i.z-step-1 ,raio))	&&(m[i.x][i.y][i.z-step-1]==air))
    {
        aux->set(i.x,i.y,i.z-step-1,air);
        vizinhos.push_back(*aux);
        k++;
    }

    delete(aux);
    vizinhos.resize(k);
    return vizinhos;
}

//funcao que liga os pontos
Point<UFINT16> Labirinto::ligaVizinho(Matriz m,Point<UFINT16> i, Point<UFINT16> f)
{
    for(int j=0; j<step; ++j)
    {
        if(i.x<f.x)
            i.x+=1;
        else if(i.x>f.x)
            i.x-=1;
        else if(i.y<f.y)
            i.y+=1;
        else if(i.y>f.y)
            i.y-=1;
        else if(i.z<f.z)
            i.z+=1;
        else if(i.z>f.z)
            i.z-=1;
        m[i.x][i.y][i.z]=cav_f; // aqui fazemos a ligacao em si de um ponto a outro. O ponto destino nao eh alterado aqui, mas sim na funcao recursiva.
    }
    return f;
}
