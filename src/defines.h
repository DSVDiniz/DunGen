#ifndef DEFINES_H_
#define DEFINES_H_

/**
int8_t, char				-> -128,127 ou 0,255
int16_t, short, char		-> -32768,32767 ou 0,65535
int32_t, int, long			->	-2147483648,-2147483647 ou 0, 4294967295

tamanhos em bytes(minimo)
char	1
short	2
int		4
long	4
float	4
double	8

int8_t, 16_t, 32_t, 64_t sao garantidos os tamanhos considerando portabilidade(8 bits, 16bits, etc)
**/

#define UFINT8				uint_fast8_t
#define UFINT16				uint_fast16_t

#define UINT8				uint8_t
#define UINT16				uint16_t

//#define HEIGHTMAP
//#define ARRAYS
//#define LINES
//#define SCALING
//#define TESTANDOMATRIZ
//#define MANUAL_SEED
//#define AGUA_PRIMEIRO
//#define WATERHEIGHT
#define SETTINGS_FILE		"json_dungen.txt"

#define PI                  3.14159265
#define RAD                 0.01745

#define WIN_WID				800.0
#define WIN_HEI				640.0

#define WIN_R_B				5
#define WIN_G_B				6
#define WIN_B_B				5
#define WIN_A_B				0
#define WIN_DPT				8
#define WIN_STN				0

#define TAMX               	128
#define TAMY                128
#define TAMZ                64
#define LIM_X				2
#define LIM_Y				2
#define LIM_Z				2

#define CUBE_SIZE			1.0

#define VOL_MAX             5000
#define VOL_MIN             4000
#define TAM_MIN				3
#define TAM_MAX				30
#define MAX_TENTATIVAS 		10000000

#define L_AMB_R				0.5
#define L_AMB_G				0.5
#define L_AMB_B				0.5
#define L_AMB_I				0.2

#define L_DIF_R				1.0
#define L_DIF_G				1.0
#define L_DIF_B				1.0
#define L_DIF_I				1.0

#define L_SPC_R				1.0
#define L_SPC_G				1.0
#define L_SPC_B				1.0
#define L_SPC_I				0.2

#define M_SPC_R				0.2
#define M_SPC_G				0.2
#define M_SPC_B				0.2
#define M_SPC_I				0.2

#define MAT_SHINE			0.1

//cores 0-41 	vermelho
//		42-84 	verde
//		85-125 	azul

#define air			0
#define cav_f       20
#define cav_w       41

#define water1		117
#define water2		118
#define water3		119
#define water4		120
#define water5		121
#define water6		122
#define water7		123
#define water8		124
#define water9		125

#define PARSE_JSON_FILE		0
#define PARSE_MAP_FILE		1

/**solucoes**/
//Matriz com valores multiplos
//-gasta mais memória(dobro)
//-no momento só vai ser usado pra ver nivel de agua...9 niveis de 255 possiveis valores
//+mais atributos para cada tile
//Mudar atribuicao de tiles e cores
//-refazer boa parte do codigo
//-+perder visualizacao com cores?
//+sem gasto extra de memoria
//-gasto extra em processamento


#include "inttypes.h"
/*#include <vector>

#ifdef TESTANDOMATRIZ
	typedef vector <vector <vector <UFINT8> > > Matriz;
#else
	typedef UFINT16 Matriz [TAMX][TAMY][TAMZ];
#endif*/



#endif /* DEFINES_H_*/
