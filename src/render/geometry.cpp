#include "renderer.h"
static int colorA [][3]
{
    {6,0,0},	{12,0,0},	{18,0,0},	{24,0,0},	{30,0,0},	{36,0,0},	{42,0,0},	{48,0,0},	{54,0,0},	{60,0,0},
    {66,0,0},	{72,0,0},	{78,0,0},	{84,0,0},	{90,0,0},	{96,0,0},	{102,0,0},	{108,0,0},	{114,0,0},	{120,0,0},
    {126,0,0},	{132,0,0},	{138,0,0},	{144,0,0},	{150,0,0},	{156,0,0},	{162,0,0},	{168,0,0},	{174,0,0},	{180,0,0},
    {186,0,0},	{192,0,0},	{198,0,0},	{204,0,0},	{210,0,0},	{216,0,0},	{222,0,0},	{228,0,0},	{234,0,0},	{240,0,0},
    {246,0,0},	{252,0,0},
    {0,6,0},	{0,12,0},	{0,18,0},	{0,24,0},	{0,30,0},	{0,36,0},	{0,42,0},	{0,48,0},	{0,54,0},	{0,60,0},
    {0,66,0},	{0,72,0},	{0,78,0},	{0,84,0},	{0,90,0},	{0,96,0},	{0,102,0},	{0,108,0},	{0,114,0},	{0,120,0},
    {0,126,0},	{0,132,0},	{0,138,0},	{0,144,0},	{0,150,0},	{0,156,0},	{0,162,0},	{0,168,0},	{0,174,0},	{0,180,0},
    {0,186,0},	{0,192,0},	{0,198,0},	{0,204,0},	{0,210,0},	{0,216,0},	{0,222,0},	{0,228,0},	{0,234,0},	{0,240,0},
    {0,246,0},	{0,252,0},
    {0,0,6},	{0,0,12},	{0,0,18},	{0,0,24},	{0,0,30},	{0,0,36},	{0,0,42},	{0,0,48},	{0,0,54},	{0,0,60},
    {0,0,66},	{0,0,72},	{0,0,78},	{0,0,84},	{0,0,90},	{0,0,96},	{0,0,102},	{0,0,108},	{0,0,114},	{0,0,120},
    {0,0,126},	{0,0,132},	{0,0,138},	{0,0,144},	{0,0,150},	{0,0,156},	{0,0,162},	{0,0,168},	{0,0,174},	{0,0,180},
    {0,0,186},	{0,0,192},	{0,0,198},	{0,0,204},	{0,0,210},	{0,0,216},	{0,0,222},	{0,0,228},	{0,0,234},	{0,0,240},
    {0,0,246},	{0,0,252},
    {246,6,0},	{240,12,0},	{234,18,0},	{228,24,0},	{222,30,0},	{216,36,0},	{210,42,0},	{204,48,0},	{198,54,0},	{192,60,0},
    {186,66,0},	{180,72,0},	{174,78,0},	{168,84,0},	{162,90,0},	{156,96,0},	{150,102,0},{144,108,0},{138,114,0},{132,120,0},
    {126,126,0},{120,132,0},{114,138,0},{108,144,0},{102,150,0},{96,156,0},	{90,162,0},	{84,168,0},	{78,174,0},	{72,180,0},
    {66,186,0},	{60,192,0},	{54,198,0},	{48,204,0},	{42,210,0},	{36,216,0},	{30,222,0},	{24,228,0},	{18,234,0},	{12,240,0},
    {6,246,0},	{0,252,0},
    {0,246,6},	{0,240,12},	{0,234,18},	{0,228,24},	{0,222,30},	{0,216,36},	{0,210,42},	{0,204,48},	{0,198,54},	{0,192,60},
    {0,186,66},	{0,180,72},	{0,174,78},	{0,168,84},	{0,162,90},	{0,156,96},	{0,150,102},{0,144,108},{0,138,114},{0,132,120},
    {0,126,126},{0,120,132},{0,114,138},{0,108,144},{0,102,150},{0,96,156}, {0,90,162},	{0,84,168},	{0,78,174},	{0,72,180},
    {0,66,186},	{0,60,192},	{0,54,198},	{0,48,204},	{0,42,210},	{0,36,216},	{0,30,222},	{0,24,228},	{0,18,234},	{0,12,240},
    {0,6,246},	{0,0,252},
    {6,0,246},	{12,0,240},	{18,0,234},	{24,0,228},	{30,0,222},	{36,0,216},	{42,0,210},	{48,0,204},	{54,0,198},	{60,0,192},
    {66,0,186},	{72,0,180},	{78,0,174},	{84,0,168},	{90,0,162},	{96,0,156},	{102,0,150},{108,0,144},{114,0,138},{120,0,132},
    {126,0,126},{132,0,120},{138,0,114},{144,0,108},{150,0,102},{156,0,96},	{162,0,90},	{168,0,84},	{174,0,78},	{180,0,72},
    {186,0,66},	{192,0,60},	{198,0,54},	{204,0,48},	{210,0,42},	{216,0,36},	{222,0,30},	{228,0,24},	{234,0,18},	{240,0,12},
    {246,0,6},	{252,0,0},
    {255,255,255},{128,128,128},{0,0,0}
};
void Renderer::cubo(int x,int y,int z,int tipo,double s, double t, double u )
{
    //     tras
    //     +---+
    //  esq+ C +dir
    //     +---+
    //     frente

    int r = 0, g = 0,b = 0;

#ifdef HEIGHTMAP
    int passo=int(255/(high-low));
    r=passo*z;
#else
    int n = tipo;
    r=colorA[n][0];
    g=colorA[n][1];
    b=colorA[n][2];
#endif

    glBegin(GL_TRIANGLES);
    {
        glColor3ub(r,g,b);
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

        //cima
        glNormal3f(0.0,0.0,1.0);
        glVertex3f(x	, y		, z+u);
        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x+s	, y		, z+u);

        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x+s	, y+t	, z+u);
        glVertex3f(x+s	, y		, z+u);

        //baixo
        glNormal3f(0.0,0.0,-1.0);
        glVertex3f(x	, y		, z);
        glVertex3f(x+s	, y		, z);
        glVertex3f(x	, y+t	, z);

        glVertex3f(x	, y+t	, z);
        glVertex3f(x+s	, y		, z);
        glVertex3f(x+s	, y+t	, z);

        //tras
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(x	, y+t	, z);
        glVertex3f(x+s	, y+t	, z);
        glVertex3f(x	, y+t	, z+u);

        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x+s	, y+t	, z);
        glVertex3f(x+s	, y+t	, z+u);

        //frente
        glNormal3f(0.0,-1.0,0.0);
        glVertex3f(x	, y		, z);
        glVertex3f(x	, y		, z+u);
        glVertex3f(x+s	, y		, z);

        glVertex3f(x	, y		, z+u);
        glVertex3f(x+s	, y		, z+u);
        glVertex3f(x+s	, y		, z);

        //esq
        glNormal3f(-1.0,0.0,0.0);
        glVertex3f(x	, y		, z);
        glVertex3f(x	, y+t	, z);
        glVertex3f(x	, y		, z+u);

        glVertex3f(x	, y+t	, z);
        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x	, y		, z+u);

        //dir
        glNormal3f(1.0,0.0,0.0);
        glVertex3f(x+s	, y		, z);
        glVertex3f(x+s	, y		, z+u);
        glVertex3f(x+s	, y+t	, z);

        glVertex3f(x+s	, y+t	, z);
        glVertex3f(x+s	, y		, z+u);
        glVertex3f(x+s	, y+t	, z+u);
    }
    glEnd();
}

void Renderer::cuboLines(int x,int y,int z,int r, int g, int b,double s,double t,double u)
{
    //     tras
    //     +---+
    //  esq+ C +dir
    //     +---+
    //     frente

    glBegin(GL_LINE_STRIP);
    {
        glColor3ub(r,g,b);

        //cima
        glVertex3f(x	, y		, z+u);
        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x+s	, y+t	, z+u);
        glVertex3f(x+s	, y		, z+u);
        glVertex3f(x	, y		, z+u);

        //baixo
        glVertex3f(x	, y		, z);
        glVertex3f(x	, y+t	, z);
        glVertex3f(x+s	, y+t	, z);
        glVertex3f(x+s	, y		, z);
        glVertex3f(x	, y		, z);
    }
    glEnd();

    glBegin(GL_LINES);
    {
        glColor3ub(r,g,b);
        glVertex3f(x	, y+t	, z+u);
        glVertex3f(x	, y+t	, z);
        glVertex3f(x+s	, y+t	, z+u);
        glVertex3f(x+s	, y+t	, z);
        glVertex3f(x+s	, y		, z+u);
        glVertex3f(x+s	, y		, z);
    }
    glEnd();
}

void Renderer::mesh(double x, double y, double z, double a)
{

}

void Renderer::marchingCubes()
{

}
