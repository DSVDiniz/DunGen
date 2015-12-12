#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LINHA 6
#define COLUNA 11
#define MAX 1000



void preencheMatriz (int iMapaGeografico[][COLUNA]);/*Fun��o para popular Matriz com os n�meros aleat�rios*/

void imprimeMatriz(int iMapaGeografico[][COLUNA]);/*Imprimir a matriz*/

int intervaloRecursos(int iRecursos, int iIntervalo);/*Funcao para reconhecer o estado em que s encontra o lugar e os nomades*/

void cicloNomade (int iRecursos, int iIntervalo, int iPopulacao, int iCiclos); /*Funcao para acompanhar os ciclos e ver o consumo de recursos*/

int main (void)
{
    int iMapaGeografico[LINHA][COLUNA]; /*Matriz que vai agregar os valores dos recursos*/
    int iCiclos = 0; /*Vari�vel para contar a quantidade de ciclos*/
    int iIntervalo;/*Vari�vel que recebe a condi��o dos recursos*/
    int iPontox = 0;/*Vari�vel para o 'x' do ponto*/
    int iPontoy = 0;/*Vari�vel para o 'y' do ponto*/
    int iPopulacao = 0;/*Vari�vel que recebe o n�mero de nomades*/
    int iRecursos = 0;/*Vari�vel para indicar os recursos existentes no ponto da matriz*/



    srand(time(NULL));

    preencheMatriz(iMapaGeografico);

    imprimeMatriz(iMapaGeografico);

    printf("\n"); /*Para dar espa�o ao pr�ximo comando*/


    iPopulacao = rand()%21; /*Sorteio da popula��o*/

    if (iPopulacao < 3)/*IF para gerar um n�mero qualquer caso fique abaixo do m�nimo exigido no trabalho (3)*/
    {
        iPopulacao = 20 - iPopulacao;
    }


    iPontox = rand()%6;

    iPontoy = rand()%11;

    printf ("A populacao do grupo nomade e %d\n", iPopulacao);

    printf ("O coordenada da localizacao do grupo nomade e %d\n", iPontox);

    printf ("O Abscissa da localizacao do grupo nomade e %d\n", iPontoy);

    iRecursos = iMapaGeografico[iPontox][iPontoy];

    printf("\n Quantidade de recursos: %d", iRecursos);

    intervaloRecursos(iRecursos, iIntervalo);

    cicloNomade (iRecursos, iIntervalo, iPopulacao, iCiclos);



    return 0;
}



void preencheMatriz (int iMapaGeografico[][COLUNA]) /*Fun��o para popular Matriz com os n�meros aleat�rios*/

{
    int iContador1 = 0;
    int iContador2 = 0;

    for (iContador1 = 0; iContador1 < LINHA; iContador1++)/*La�o para preenchimento da matriz*/
    {
        for (iContador2 = 0; iContador2 < COLUNA; iContador2++)

        {
                iMapaGeografico[iContador1][iContador2] = rand()%MAX;
        }

    }

}

void imprimeMatriz(int iMapaGeografico[][COLUNA])/*Fun��o para imprimir Matriz*/
{
    int iContador1 = 0;
    int iContador2 = 0;

    for (iContador1 = 0; iContador1 < LINHA; iContador1++)
    {

        printf("\n\t");/*Comando para deixar uniforme a Matriz*/

        for (iContador2 = 0; iContador2 < COLUNA; iContador2++)
        {
            printf("%3d %s", iMapaGeografico[iContador1][iContador2], " ");
        }

        printf("\n\t"); /*Ao final de uma linha, salta para pr�xima*/
    }

}

int intervaloRecursos(int iRecursos, int iIntervalo)
{
    if (iRecursos > 333)
    {
        printf ("\nRecursos abundantes\n");
        iIntervalo = 1;
    }
    else if ((iRecursos < 333) && (iRecursos > 110))
    {
        printf ("\nRecursos adequados\n");
        iIntervalo = 2;
    }
    else if ((iRecursos < 110) && (iRecursos > 50))
    {
       printf ("\nRecursos criticos\n");
       iIntervalo = 3;
    }
    else if (iRecursos < 50)
    {
        printf ("\nRecursos Escassos\n");
        iIntervalo = 4;
    }

    return iIntervalo;
}

void cicloNomade (int iRecursos, int iIntervalo, int iPopulacao, int iCiclos)
{
	char cDecisao=' ';
    while ((cDecisao != 'x') || (cDecisao != 'X'))/*La�o para acompanhar os ciclos*/
    {
        printf ("\nAperte qualquer tecla para continuar\n");
        printf ("\nDigite x para encerrar\n"); /*Letra x escolhida para encerrar o ciclo*/
        scanf ("%c", &cDecisao);
        getchar();
		printf("CHAR1: %c", cDecisao);
        printf("\n Teste para saber a populacao %d\n", iPopulacao);

        if (iIntervalo = 1)/*Com o resultado da funcao, o programa vai seguir algum dos casos abaixo, conforme orientado no programa do trabalho*/
        {
            iPopulacao = iPopulacao + (iPopulacao / 6);
        }
        else if (iIntervalo = 2)
        {
            iPopulacao = iPopulacao + (iPopulacao / 18);
        }
        else if (iIntervalo = 3)
        {
            iPopulacao = iPopulacao;
        }
        else if (iIntervalo = 4)
        {
            iPopulacao = iPopulacao  / 2;
        }

        printf("CHAR2: %c", cDecisao);

        iRecursos = iRecursos - (2 * iPopulacao);

        intervaloRecursos(iRecursos, iIntervalo);

        printf("\n Teste para saber a populacao %d\n", iPopulacao);
        iCiclos++;
        printf("CHAR3: %c", cDecisao);
    }
}
