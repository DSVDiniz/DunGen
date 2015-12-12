#include "draw.h"
//static int aux_dir[][3] = {{0,1,0},{1,1,0},{1,0,0},{1,-1,0},{0,-1,0},{-1,-1,0},{-1,0,0},{-1,1,0}};

std::vector<double>Draw::addWave(std::vector<double> pontos,int escolha)
{
    int a =0;
    if(escolha == -1)
        escolha =rngi(6);

    switch(escolha)
    {
    case 0://montanhas senoidais
        for(int i=0; i<TAMX; ++i)
            for(int j=0; j<TAMY; ++j)
            {
                pontos[a] += sin(j/(360*RAD))*10;
                a++;
            }
        break;

    case 1://montanhas cosseno
        for(int i=0; i<TAMX; ++i)
            for(int j=0; j<TAMY; ++j)
            {
                pontos[a] += cos(i/(360*RAD))*10;
                a++;
            }
        break;

    case 2://picos sen+cos
        for(int i=0; i<TAMX; ++i)
            for(int j=0; j<TAMY; ++j)
            {

                pontos[a] += (cos((i-64)/(360*3*RAD))*15) + ( sin((j-34)/(360*3*RAD))*15);
                a++;
            }
        break;

    case 3://rosas

        break;

    case 4:
        for(int i=0; i<TAMX; ++i)
            for(int j=0; j<TAMY; ++j)
            {
                pontos[a] += (i/4) - (j/4)+cos((j)/(1080*RAD))*10;
                a++;
            }
        break;

    case 5://vales angulares
        for(int i=0; i<TAMX; ++i)
            for(int j=0; j<TAMY; ++j)
            {
                pontos[a] += (cos((i+j)/(360*5*RAD))*10 )+( sin((i+j)/(360*5*RAD))*10);
                a++;
            }
        break;

    case 6:
        break;
    }


    return pontos;
}

std::vector < Point <int> > Draw::getArea(Matriz m ,Point<UFINT16> p)
{
    {
        //	 -y
        //-x	+x
        //	 +y
        //	+1   //    0    //   -1
        // 0 1 2 // 9 10 11 //18 19 20
        // 3 4 5 //12 13 14 //21 22 23
        // 6 7 8 //15 16 17 //24 25 26
    }

    std::vector < Point <int> > vec;
    Point <int> pt;
    int aux =0,aux2=0;
    int cima, baixo, esq, dir,cima_l,baixo_l,esq_l,dir_l;

    cima=baixo=esq=dir=cima_l=baixo_l=esq_l=dir_l=0;
    pt.set(9,9,9);
    vec.push_back(pt);

    if(p.z-1>1)
    {
        aux = get(m,p.x,p.y,p.z-1);
        if(aux==air)
        {
            pt.set(0,0,-1);
            vec[0]=pt;
            return vec;
        }
        else
        {
            cima	=	get(m,p.x,	 p.y+1,	p.z);
            cima_l	=	get(m,p.x,	 p.y+1,	p.z-1);
            baixo	=	get(m,p.x,	 p.y-1,	p.z);
            baixo_l	=	get(m,p.x,	 p.y-1,	p.z-1);
            esq		=	get(m,p.x-1, p.y,	p.z);
            esq_l	=	get(m,p.x-1, p.y,	p.z-1);
            dir		=	get(m,p.x+1, p.y,	p.z);
            dir_l	=	get(m,p.x+1, p.y,	p.z-1);

            if((cima==air)&&
                    ((cima_l==air)||(cima_l==water9)))
            {
                pt.set(0,1,0);
                vec.push_back(pt);
                aux2++;
            }
            if((baixo==air)&&
                    ((baixo_l==air)||(baixo_l==water9)))
            {
                pt.set(0,-1,0);
                vec.push_back(pt);
                aux2++;
            }
            if((esq==air)&&
                    ((esq_l==air)||(esq_l==water9)))
            {
                pt.set(-1,0,0);
                vec.push_back(pt);
                aux2++;
            }
            if((dir==air)&&
                    ((dir_l==air)||(dir_l==water9)))
            {
                pt.set(1,0,0);
                vec.push_back(pt);
                aux2++;
            }
        }
        if(aux2==0)
        {
            pt.set(7,7,7);
            vec[0]=pt;
            return vec;
        }
    }
    return vec;
}

//funcao checkDirection
//recebe uma matriz e um ponto da matriz
//retorna uma lista de direcoes disponiveis ao redor do ponto.
std::deque< Point<int> > Draw::checkDirection(Matriz m, Point<UFINT16> p)
{
    std::deque <Point <int> > v_agua, v_chao;
    Point <int> aux;
    int DIR [8];
    static int aux_dir[][3] = {{0,1,0},{1,1,0},{1,0,0},{1,-1,0},{0,-1,0},{-1,-1,0},{-1,0,0},{-1,1,0}};

	//iniciamos um vetor de direcoes pre-definido para receber os valores da matriz emvolta do ponto p
    DIR[0]	=	get(m,p.x,		p.y+1,	p.z);
    DIR[1]	=	get(m,p.x+1,	p.y+1,	p.z);
    DIR[2] =	get(m,p.x+1,	p.y,	p.z);
    DIR[3] =	get(m,p.x+1,	p.y-1,	p.z);
    DIR[4] =	get(m,p.x,		p.y-1,	p.z);
    DIR[5] =	get(m,p.x-1,	p.y-1,	p.z);
    DIR[6] = 	get(m,p.x-1,	p.y,	p.z);
    DIR[7] =	get(m,p.x-1,	p.y+1,	p.z);

	//se o ponto p tiver um volume de agua maior que 1
    if((p.t>water1)&&(p.t<=water9))
    {
		//passamos por todas as direcoes emvolta dele
        for(int i=0; i<8; ++i)
        {
            if(DIR[i]	==air) //se a direcao for vazia
            {
                aux.set(aux_dir[i][0],aux_dir[i][1],aux_dir[i][2],0);
                v_chao.push_front(aux);//inserimos suas coordenadas no vetor de posicoes vazias
            }
            else//caso contrario
            {
				//se a direcao for uma agua com volume entre 1 e 9
				// E se o volume contido nessa direcao for MENOR que o volume contido pelo ponto p
                if((DIR[i]	>=water1)&&(DIR[i]	<water9)&&(DIR[i]<(int)p.t))
                {
                    aux.set(aux_dir[i][0],aux_dir[i][1],aux_dir[i][2],1);
                    v_agua.push_front(aux);//inserimos suas coordenadas no vetor de posicoes com agua
                }
            }
        }
    }
    else
		return v_chao;

    //retornamos um vetor que tenha direcoes disponiveis
    #ifdef AGUA_PRIMEIRO
		if(v_agua.size()>0)
			return v_agua;
		else
			return v_chao;
	#else
		if(v_chao.size()>0)
			return v_chao;
		else
			return v_agua;
	#endif
}



void Draw::waterSim(Matriz m)
{
	//arrumar transicao horizontal da agua
	unsigned int dif=0;
	unsigned int teste =0;
    std::deque < Point<UFINT16> > vec_pts, vec_pts_antigo, vec_pts_aux, vec_flush;;
    std::deque < Point<int> > dir_disp;
    std::vector < Point<int> > aux;
    Point <UFINT16>pt_abaixo,pt,pt2;

    //pegar posições da agua
    vec_pts_antigo = vec_pts = getTilePosWaterDeque(m);

    for(int z=0; z<70; z++)
    {
		std::cout<<z<<std::endl;
		pt2.set(0,0,0,0);
        vec_pts_antigo = vec_pts;
        //passamos pela lista de pontos do mapa que sao agua
        for(unsigned int i =0; i<vec_pts.size();++i)
        {
			//retirando os membros vazios (que nao sao agua) se o numero deles ficar muito grande
			if(teste>vec_pts.size()/2)
			{
				std::cout<<"flushing"<<std::endl;
				for(unsigned int j =0; j<vec_pts.size();++j)
				{
					if(vec_pts[j].t!=0)
						vec_flush.push_back(vec_pts[j]);
				}
				vec_pts=vec_flush;
				teste=0;
			}

			if((vec_pts[i].t<water1)||(vec_pts[i].t>water9))
			{
				//std::cout<<"overflow ou underflow"<<std::endl;
				vec_pts[i].t=air;
				teste++;
				//continue;
			}
			pt.set(vec_pts[i]);

            //criamos um ponto auxiliar que tem o tipo de tile abaixo do ponto que estamos vendo
            pt_abaixo.set(pt.x,pt.y,pt.z-1,	m[pt.x][pt.y][pt.z-1]);

            if(pt_abaixo.t==air)//se ele for vazio
            {
                --pt.z;
                --vec_pts[i].z;
            }
            else//se ele for chao ou agua
            {
				//se ele for agua(nao cheia)
                if((pt_abaixo.t>=water1)&&(pt_abaixo.t<water9))
                {
					dif=water9-pt_abaixo.t;
					if(pt.t>=dif)
					{
						pt.t-=dif;
						if(pt.t<water1)
							vec_pts[i].t=air;
						else
							vec_pts[i].t=pt.t;
						pt_abaixo.t+=dif;
					}
					else
					{
						pt_abaixo.t+=pt.t;
						pt.t=air;
						vec_pts[i].t=air;
					}

                    //precisamos passar por toda lista de pontos de agua para alterar o tipo de tile de baixo
                    //melhor do que passar por toda matriz em busca da agua denovo
                    //usar ponteiros e modificar direto na matriz?
                    for(unsigned int j=0; j<vec_pts.size();++j)
                    {
                        if(vec_pts[j].comp(pt_abaixo))
                            vec_pts[j].t=pt_abaixo.t;
                    }
                }
                else//se for chao ou a agua abaixo estiver cheia (water9)
                {
                    dir_disp = checkDirection(m,vec_pts[i]);//checamos as direcoes possiveis para mover a agua

                    if(dir_disp.size()>0)
                    {
                        if(dir_disp.front().t==1)//caso ha direcoes com agua
                        {
							//colocamos um ponto temporario pt2 com as posicoes atuais do ponto
                            pt2.set(vec_pts[i]);
                            //adicionamos a ele as posicoes disponiveis
                            int rand = Draw::rngi(dir_disp.size());
                            pt2.add(dir_disp[rand].x,dir_disp[rand].y,dir_disp[rand].z);
                            //precisamos passar por toda lista de pontos de agua para encontrar a posicao nova
                            for(unsigned int j=0; j<vec_pts.size();++j)
                            {
                            	if(vec_pts[j].comp(pt2))//quando achamos ele
                            	{
									//pegamos seu volume de agua+1
                            		if((vec_pts[j].t<water9)&&(vec_pts[i].t>water1))
									{
										vec_pts[j].t++;
										vec_pts[i].t--;
									}
                            	}
                            }
                            pt2.set(0,0,0,0);
                        }
                        else//caso nao ha direcoes com agua
                        {
							pt2.set(vec_pts[i].x,vec_pts[i].y,vec_pts[i].z,water1);
                            pt2.add(dir_disp.front().x,dir_disp.front().y,dir_disp.front().z);
                            vec_pts[i].t--;
                            vec_pts_aux.push_back(pt2);
                        }
                    }
                }
            }
        }

        for(unsigned int i=0; i<vec_pts_antigo.size();++i)
        {
            insert(m,vec_pts_antigo[i].x
					,vec_pts_antigo[i].y
					,vec_pts_antigo[i].z
					,air);
        }
		for(unsigned int j=0;j<vec_pts_aux.size();++j)
		{
			vec_pts.push_back(vec_pts_aux[j]);
		}
		vec_pts_aux.clear();
		for(unsigned int i=0; i<vec_pts.size();++i)
        {
			insert(m,vec_pts[i]);
        }

    }
}

std::deque< Point<int> > Draw::checkDir(Matriz m, Point<UFINT16> p)
{
    std::deque <Point <int> > v_chao;
    Point <int> aux;
    int DIR [9];
    static int aux_dir[][3] = {{0,1,0},{1,1,0},{1,0,0},{1,-1,0},{0,-1,0},{-1,-1,0},{-1,0,0},{-1,1,0},{0,0,-1}};

	//iniciamos um vetor de direcoes pre-definido para receber os valores da matriz emvolta do ponto p
    DIR[0]	=	get(m,p.x,		p.y+1,	p.z);
    DIR[1]	=	get(m,p.x+1,	p.y+1,	p.z);
    DIR[2] =	get(m,p.x+1,	p.y,	p.z);
    DIR[3] =	get(m,p.x+1,	p.y-1,	p.z);
    DIR[4] =	get(m,p.x,		p.y-1,	p.z);
    DIR[5] =	get(m,p.x-1,	p.y-1,	p.z);
    DIR[6] = 	get(m,p.x-1,	p.y,	p.z);
    DIR[7] =	get(m,p.x-1,	p.y+1,	p.z);
    DIR[8]	=	get(m,p.x,		p.y,	p.z-1);

	//passamos por todas as direcoes emvolta dele
	for(int i=0; i<9; ++i)
	{
		if(DIR[i]	==air) //se a direcao for vazia
		{
			aux.set(aux_dir[i][0],aux_dir[i][1],aux_dir[i][2],0);
			v_chao.push_front(aux);//inserimos suas coordenadas no vetor de posicoes vazias
		}
	}
	return v_chao;
}

//checa se a area esta abaixo de um certo nivel Z e se pode ser alcancada por uma linha que vai de Z=max ate Z=0
//se tiver algum bloco no caminho dessa linha, e o Z minimo alcancado pela linha for <= que o Z minimo, esse bloco vazio
//sera mudado para agua
//Criar versao 2d?
void Draw::simpleWaterSim(Matriz m, unsigned int nivel_agua)
{
	std::deque < Point<UFINT16> > vec;
	Point<UFINT16> aux;
	for(unsigned int i =0; i<TAMX;++i)
		for(unsigned int j =0; j<TAMY;++j)
			for(unsigned int k =TAMZ; k>0;--k)
			{
				if(m[i][j][k]==air)
				{
					if(k<nivel_agua)
					{
						m[i][j][k]=water9;
						aux.set(i,j,k);
						vec.push_back(aux);
					}
					else
						continue;
				}
				else
					break;
			}

	bool atingiu = false;
	std::deque <Point<int> >dir;

	for(unsigned int i =0; i<vec.size();++i)
	{
		dir = checkDir(m,vec[i]);
		for(unsigned int j=0;j<dir.size();++j)
		{
			atingiu = false;
			while(!atingiu)
			{
				aux.set(vec[i]);
				aux.add(dir[j].x,dir[j].y,dir[j].z);
				if(m[aux.x][aux.y][aux.z]==air)
				{
					m[aux.x][aux.y][aux.z]=water9;
					vec.push_back(aux);
				}
				else
					atingiu = true;
			}
		}

	}


}
