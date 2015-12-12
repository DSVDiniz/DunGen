#include "renderer.h"

UFINT16 Renderer::optMatriz[TAMX*TAMY*TAMZ];

bool 	Renderer::displayListInit = false;
int		Renderer::high=255;
int		Renderer::low=0;

std::vector< Point<float> > colorVec;
GLuint Renderer::mapList;

GLfloat LightPosition[] 	= {TAMX, TAMX, TAMZ/2, 0.2};

static int iNormal, iVertex, iColor, iIndex;

bool Renderer::instanceFlag = false;
Renderer* Renderer::printerVariable = NULL;

Renderer * Renderer::GetInstance ()
{
    if (!instanceFlag)
    {
        printerVariable = new Renderer();
        instanceFlag =true;
        return printerVariable;
    }
    else
    {
        return(printerVariable);
    }
}

Renderer::~Renderer()
{
    instanceFlag=false;
    glfwDestroyWindow(window);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glfwTerminate();
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static Input * input;
	input = Input::GetInstance();
	Point <GLfloat> xyz, abc;

	int xSpeed = input->getPositionSpeed('x');
	int ySpeed = input->getPositionSpeed('y');
	int zSpeed = input->getPositionSpeed('z');

	int xAngSpeed = input->getAngleSpeed('x');
	int yAngSpeed = input->getAngleSpeed('y');
	int zAngSpeed = input->getAngleSpeed('z');

	if((key == GLFW_KEY_ESCAPE)&&(action == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, true);
		input->setSair(true);
	}
	else if((key == GLFW_KEY_P)&&(action == GLFW_PRESS))
    {
        xyz=input->getPosition();
        abc=input->getAngularPosition();
        std::cout<<"X:"<<xyz.x<<"\t"<<"Y:"<<xyz.y<<"\t"<<"Z:"<<xyz.z<<"\n";
        std::cout<<"A:"<<abc.x<<"\t"<<"B:"<<abc.y<<"\t"<<"C:"<<abc.z<<"\n";
    }
    else if((key == GLFW_KEY_T)&&(action == GLFW_PRESS))
    {
        input->setPosition(TAMX/2,TAMY/2,-180);
        input->setAngle(0,0,180);
    }
    else if((key == GLFW_KEY_Q)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(-zSpeed, 'z');
    else if((key == GLFW_KEY_E)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(+zSpeed, 'z');
    else if((key == GLFW_KEY_W)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(-ySpeed, 'y');
    else if((key == GLFW_KEY_A)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(-xSpeed, 'x');
    else if((key == GLFW_KEY_S)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(+ySpeed, 'y');
    else if((key == GLFW_KEY_D)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addPosition(+xSpeed, 'x');
    else if((key == GLFW_KEY_UP)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addAngle(-xAngSpeed,'x');
    else if((key == GLFW_KEY_DOWN)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addAngle(+xAngSpeed,'x');
    else if((key == GLFW_KEY_LEFT)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addAngle(-yAngSpeed,'y');
    else if((key == GLFW_KEY_RIGHT)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        input->addAngle(+yAngSpeed,'y');


	else if((key == GLFW_KEY_0)&&(action == GLFW_PRESS))
    {
        input->setOp(0);
        input->setMudou(true);
    }
    else if((key == GLFW_KEY_1)&&(action == GLFW_PRESS))
    {
        input->setOp(1);
        input->setMudou(true);
    }
    else if((key == GLFW_KEY_2)&&(action == GLFW_PRESS))
    {
        input->setOp(2);
        input->setMudou(true);
    }
    else if((key == GLFW_KEY_3)&&(action == GLFW_PRESS))
    {
        input->setOp(3);
        input->setMudou(true);
    }
    else if((key == GLFW_KEY_4)&&(action == GLFW_PRESS))
    {
        input->setOp(4);
        input->setMudou(true);
    }
    else if((key == GLFW_KEY_5)&&(action == GLFW_PRESS))
    {
        input->setOp(5);
        input->setMudou(true);
    }
    /*else if((key == GLFW_KEY_U)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        oct+= 1;
    else if((key == GLFW_KEY_J)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        oct-= 1;

    else if((key == GLFW_KEY_I)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        amp+= 0.5;
    else if((key == GLFW_KEY_K)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        amp-= 0.5;

    else if((key == GLFW_KEY_O)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        pers+= 0.5;
    else if((key == GLFW_KEY_L)&&((action == GLFW_PRESS)||(action == GLFW_REPEAT)))
        pers-= 0.5;*/
}

bool Renderer::ini()
{
    inputs = Input::GetInstance();
    inputs->ini(*new Point<UFINT16>(-TAMX/2,-TAMY/2,-180,3),*new Point<UFINT16>(0,0,0,3), window);
    //inputs->ini(*new Point<UFINT16>(TAMX/2,TAMY/2,-180,3),*new Point<UFINT16>(0,0,180,3));
    //inputs->ini(*new Point<UFINT16>(55,64,-3,3),*new Point<UFINT16>(0,-54,180,3));

    iNormal=iVertex=iColor=iIndex=0;

    clearMatrix();

    if(!glfwInit())
    {
        std::cout<<"GLFW nao pode ser inicializado"<<std::endl;
        return false;
    }

    glfwSetErrorCallback(error_callback);

    if(!iniWindow())
        return false;

    //iniArrays();
    iniLight();

    /**PROJECAO DA CAMERA**/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = WIN_HEI / WIN_WID;
    glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return true;
}

bool Renderer::iniWindow()
{
    int numVideos;
    GLFWvidmode listaVideos[32];

    //essa funcao tenta botar estes parametros nos valores desejados, caso nao seja possivel, os valores serao diminuidos
	glfwWindowHint(GLFW_AUX_BUFFERS     , 1);
    glfwWindowHint(GLFW_ACCUM_RED_BITS  , 16);
    glfwWindowHint(GLFW_ACCUM_GREEN_BITS, 16);
    glfwWindowHint(GLFW_ACCUM_BLUE_BITS , 16);
    glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, 16);
    glfwWindowHint(GLFW_SAMPLES    		, 1);

    window = glfwCreateWindow	(WIN_WID,WIN_HEI,//width e height da janela
								"Dungen",
								NULL,//monitor
								NULL);//share
	if(!window)
    {
        std::cout<<"Janela nao pode ser aberta"<<std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window , key_callback);

    //versao
    std::cout<<glGetString(GL_VERSION)<<std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    return true;
}

void Renderer::iniArrays()
{
    /**ARRAYS**/
    /*glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glColorPointer	(3,	GL_UNSIGNED_BYTE,	0,	colorArray);
    glVertexPointer	(3,	GL_FLOAT, 			0,	vertexArray);

    glIndexPointer	(GL_INT,	0,	indexArray);
    glNormalPointer	(GL_FLOAT, 	0,	normalArray);

    glTexCoordPointer(GLint size, GLenum type, GLsizei stride,const GLvoid *pointer);*/
}

void Renderer::iniLight()
{
    GLfloat LightAmbient	[] 	= {L_AMB_R, L_AMB_G, L_AMB_B, L_AMB_I};
    GLfloat LightDiffuse	[] 	= {L_DIF_R, L_DIF_G, L_DIF_B, L_DIF_I};
    GLfloat light_specular	[] 	= {L_SPC_R, L_SPC_G, L_SPC_B, L_SPC_I};
    GLfloat mat_specular	[]	= {M_SPC_R, M_SPC_G, M_SPC_B, M_SPC_I};
    GLfloat mat_shininess	[] 	= {MAT_SHINE};

    /**LUZ E SHADING **/
    glEnable(GL_LIGHTING);
    glShadeModel (GL_FLAT);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHT0);
}

bool Renderer::isWindowClosed()
{
	return glfwWindowShouldClose(window);
}

void Renderer::windowResize(int width, int height)
{
    /**PROJECAO DA CAMERA**/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect_ratio = width / height;
    glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::clearMatrix()
{
    memset(optMatriz,0, sizeof(optMatriz));
    glDeleteLists(mapList,1);
}

inline bool Renderer::shellCheck(Matriz m,int x, int y, int z)
{
    if((m[x][y][z-1]!=0)&&(m[x][y-1][z]!=0)&&(m[x-1][y][z]!=0)&&(m[x+1][y][z])&&
            (m[x][y+1][z]!=0)&&(m[x][y][z+1]!=0))
        return false;
    else
        return true;

}

inline bool Renderer::shellCheck2(Matriz m,int x, int y, int z)
{
    if((m[x][y][z-1]!=0)&&(m[x][y-1][z]!=0)&&(m[x-1][y][z]!=0)&&(m[x+1][y][z])&&
            (m[x][y+1][z]!=0)&&(m[x][y][z+1]!=0))
    {
        if((m[x][y][z-1]!=water9)&&(m[x][y-1][z]!=water9)&&(m[x-1][y][z]!=water9)&&(m[x+1][y][z])&&
                (m[x][y+1][z]!=water9)&&(m[x][y][z+1]!=water9))
        {
            return false;
        }
        else
            return true;
    }
    else
        return true;

}

void Renderer::optimizeRect(vector<vector<Point<UFINT8> > > a)
{
    vec_ret=a;
}

void Renderer::optimizeMatrix(Matriz mat)
{
    int pos = 0;
    clearMatrix();
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                    optMatriz[pos]=mat[i][j][k];
                ++pos;
            }
}

void Renderer::optimizeMatrix2(Matriz mat)
{
    int pos = 0;
    clearMatrix();
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                {
                    if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                    {
                        if(shellCheck(mat,i,j,k))
                            optMatriz[pos]=mat[i][j][k];
                    }
                    else
                    {
                        optMatriz[pos]=mat[i][j][k];
                    }
                }
                ++pos;
            }
}

void Renderer::optimizeMatrix3(Matriz mat)
{
    int pos = 0;
    clearMatrix();
    for(unsigned int k = 0; k < TAMZ; ++k)
        for(unsigned int j = 0; j < TAMY; ++j)
            for(unsigned int i = 0; i < TAMX; ++i)
            {
                if(mat[i][j][k]!=0)
                {
                    if(!((k==0)||(j==0)||(i==0)||(k==TAMZ-1)||(j==TAMY-1)||(i==TAMX-1)))
                    {
                        if(shellCheck2(mat,i,j,k))
                            optMatriz[pos]=mat[i][j][k];
                    }
                    else
                    {
                        optMatriz[pos]=mat[i][j][k];
                    }
                }
                ++pos;
            }
}

void Renderer::setHighLow(Point<int> p)
{
    high = p.x;
    low  = p.y;
}

void Renderer::moveView(Point <GLfloat> pos,Point <GLfloat> ang)
{
    glTranslatef(pos.x, pos.y, pos.z);

    glRotatef(ang.x, 1, 0, 0);
    glRotatef(ang.y, 0, 1, 0);
    glRotatef(ang.z, 0, 0, 1);
}

void Renderer::drawObject ()
{
    if(displayListInit)
        glCallList(mapList);
    else
    {
        mapList = glGenLists(1);
        glNewList(mapList, GL_COMPILE);
        {
            cuboLines(0,0,0,255,255,255,TAMX,TAMY,TAMZ);
			#ifdef OPTIMIZE_TEST
				for(int i=0; i<vec_ret.size(); ++i)
				{
					/*cubo(vec_ret[i][0].x,vec_ret[i][0].y,vec_ret[i][0].z,vec_ret[i][0].t);
					cubo(vec_ret[i][1].x,vec_ret[i][1].y,vec_ret[i][1].z,vec_ret[i][1].t);*/
					cubo(vec_ret[i][0].x,vec_ret[i][0].y,vec_ret[i][0].z,vec_ret[i][0].t,vec_ret[i][1].x-vec_ret[i][0].x,1,1);
				}
			#else
				int pos=0;
				for(unsigned int k = 0; k < TAMZ; ++k)
					for(unsigned int j = 0; j < TAMY; ++j)
						for(unsigned int i = 0; i < TAMX; ++i)
						{
							if(optMatriz[pos]!=0)
							{
								#ifdef MESH
									mesh(i,j,k,CUBE_SIZE/2);
								#else
								if((optMatriz[pos]>water9)||(optMatriz[pos]<water1))
								{
									#ifdef LINES
										cuboLines(i,j,k,0,255,0);
									#else
										cubo(i,j,k,optMatriz[pos]);
									#endif
								}
								else
								{
									#ifdef LINES
										cuboLines(i,j,k,0,0,255,CUBE_SIZE,CUBE_SIZE,0.1*(optMatriz[pos]-116.0));
									#else
										#ifdef WATERHEIGHT
											cubo(i,j,k,optMatriz[pos],CUBE_SIZE,CUBE_SIZE, 0.11*(optMatriz[pos]-116.0));
										#else
											cubo(i,j,k,optMatriz[pos],CUBE_SIZE,CUBE_SIZE, CUBE_SIZE);
										#endif
									#endif
								}
								#endif
							}
							++pos;
						}
			#endif
        }
        glEndList();
        displayListInit = true;
    }
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    moveView(inputs->getPosition(),inputs->getAngularPosition());

    glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);

    drawObject();

	glfwSwapBuffers(window);
	glfwWaitEvents();
}
